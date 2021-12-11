/*To make things easier for me, I use some static class that can be run from anywhere in my code,
it's very efficient to get config data or access my main class that run my code.
However it can create conflict with other mods if someone use to same name, so if you create some static function, make sure
to make the name specific as much as you can. I usually add Name of my mod in front of my function*/

/*Class that deals with my core class, where config, client and server part of my code are created*/
static ref GarageCore m_GarageCore;
static GarageCore GetGarageCore() {
	if ( !m_GarageCore ) {
		m_GarageCore = new GarageCore;
	}
	return m_GarageCore;
}

/*clas that allows me to access the client class */
static ref GarageSettings GetGarageConfig()	{
	return GetGarageCore().m_GarageSettings;
}

/*Function that allows to get the player variable from its identity => used for RPC*/
static PlayerBase GMGetPlayerByIdentity(PlayerIdentity sender)
{
	int	low	 =	0;
	int	high =	0;
	GetGame().GetPlayerNetworkIDByIdentityID( sender.GetPlayerId(), low, high );
	return PlayerBase.Cast( GetGame().GetObjectByNetworkId(low, high ));
}

class GarageHelper
{
	static int GetLowSteamID(string SteamID64)
	{
		string temp_ID="";
		for(int j = 8; j<17; j++)
		{
			temp_ID+=SteamID64.Get(j);
		}
		return temp_ID.ToInt();
	}

	static CarScript CheckForCarAtPos(vector position)
	{
		array<Object> objects = new array<Object>;
		array<CargoBase> proxyCargos = new array<CargoBase>;
		GetGame().GetObjectsAtPosition(position, 3, objects, proxyCargos);
		CarScript car;
		if (objects)
		{
			for (int i = 0; i < objects.Count(); i++ )
			{
				if (Class.CastTo( car, objects.Get(i) ) )
				{
						return car;
				}
			}
		}
		return NULL;
	}

	static array<EntityAI> GetAttachmentsFromEntityAI(EntityAI ent)
	{
		array<EntityAI> attachementInEntity = new array<EntityAI>;

		if(!ent.GetInventory())return attachementInEntity;

		GameInventory inv = ent.GetInventory();
		int attachmentCount = inv.AttachmentCount();
		for(int i = 0; i < attachmentCount; i++)
		{
			attachementInEntity.Insert(inv.GetAttachmentFromIndex(i));
		}
		return attachementInEntity;
	}

	static array<EntityAI> GetItemsInCargoFromEntityAI(EntityAI ent)
	{
		array<EntityAI> itemsInCargos = new array<EntityAI>;

		if(!ent.GetInventory() || !ent.GetInventory().GetCargo())return itemsInCargos;

		CargoBase cargo = ent.GetInventory().GetCargo();
		for ( int i = 0; i < cargo.GetItemCount(); i++ )
		{
			 itemsInCargos.Insert(cargo.GetItem( i ));
		}
		return itemsInCargos;
	}

	static array<ref ItemsCargo> ConvertEntitiesToItemsCargo(array<EntityAI>entities, int extradata)
	{
		array<ref ItemsCargo> itemsInCargo = new array<ref ItemsCargo>;
		foreach(EntityAI ent: entities)
		{
			#ifdef MuchCarKey
				MCK_CarKey_Base key;
				if(Class.CastTo(key, ent))extradata = key.GetMCKId();
			#else
				#ifdef TRADER
				VehicleKeyBase key;
				if(Class.CastTo(key, ent))extradata = key.GetHash();
				#endif
			#endif
			itemsInCargo.Insert(new ItemsCargo(ent.GetType(), TraderPlusHelper.GetItemAmount(ItemBase.Cast(ent)), ent.GetHealth(),extradata));
		}
		return itemsInCargo;
	}

	static bool CarHasMember(CarScript car)
	{
		bool IsEmpty = false;

		Transport transport = Transport.Cast(car);
		if (!transport)return false;

		int crewSize = transport.CrewSize();
		for (int j = 0; j < crewSize; j++)
		{
			if (transport.CrewMember(j))
				IsEmpty = true;
		}

		return IsEmpty;
	}

	static bool CanParkVehicle(CarScript car)
	{
		#ifndef CARLOCKDISABLE
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			if(player)
			{
				if(car.m_CarLockOwner == player.CLSteamlowID || player.GetAdminStatus() == SZ_IS_ADMIN || player.HasPassword(car.m_CarLockPassword,car.m_CarLockOwner))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		#endif

		return true;
	}

	static bool IsParkingAvailable(vector carpos, vector carori)
	{
		vector size = "2 2 2";
		array<Object> excluded_objects = new array<Object>;
		array<Object> nearby_objects = new array<Object>;

		GetGame().IsBoxColliding( carpos, carori, size, excluded_objects, nearby_objects);
		if (nearby_objects.Count() > 0)
		{
			#ifdef GMDEBUG
			GetGMLogger().LogInfo("IsParkingAvailable"+nearby_objects.Get(0).GetType());
			#endif
			for(int i = 0;i<nearby_objects.Count();i++)
			{
				string objectName = nearby_objects.Get(i).GetType();
				if(GetGarageConfig().WhitelistedObjects.Find(objectName) == -1)
				return false;
			}
		}
		return true;
	}

	static int ConvertHealthToHealthLevel(string classname, float current_health)
	{
		float maxhealth = MiscGameplayFunctions.GetTypeMaxGlobalHealth(classname);

		float health_coeff = current_health/maxhealth;

		if(health_coeff <= 1.0 && health_coeff> 0.7) return 0;
		if(health_coeff <= 0.7 && health_coeff> 0.5) return 1;
		if(health_coeff <= 0.5 && health_coeff> 0.3) return 2;
		if(health_coeff <= 0.3 && health_coeff> 0.0) return 3;

		return 4;
	}

	static bool CreateVehicle(PlayerBase player, string classname, int id, float health, float fuel, vector position, vector orientation, array<ref ItemsCargo> items)
	{
		#ifdef GMDEBUG
		GetGMLogger().LogInfo("CreateVehicle");
		#endif
		EntityAI obj = EntityAI.Cast(GetGame().CreateObject(classname, vector.Zero));
		if (obj)
		{
			//compatibility SIB Helis
			if(obj.IsKindOf("HeliTest_SIB"))
			{
				for(int indexH = 0; indexH < 4; indexH++)
				{
					EntityAI fakeWheel = obj.GetInventory().CreateAttachment("HatchbackWheel");
				}
			}
    	for (int i = 0; i < items.Count(); i++)
    	{
    			if (items[i].ExtraData == GARAGEVEHICLEATTACHMENT)
          {
						#ifdef GMDEBUG
						GetGMLogger().LogInfo("Create attach:"+items[i].ItemName);
						#endif
            EntityAI att = obj.GetInventory().CreateAttachment(items[i].ItemName);
						if(!att)att = EntityAI.Cast( GetGame().CreateObjectEx(items[i].ItemName, vector.Zero, ECE_PLACE_ON_SURFACE) );
						if(att)
						{
							ItemBase item = ItemBase.Cast(att);
							if(item)
							{
								item = TraderPlusHelper.SetQuantity(item, items[i].Amount);
								item.SetHealth(items[i].Health);
							}
						}
          }
					else
					{
							#ifdef GMDEBUG
							GetGMLogger().LogInfo("Create item in cargo:"+items[i].ItemName);
							#endif
							EntityAI newEnt= EntityAI.Cast( GetGame().CreateObjectEx(items[i].ItemName, vector.Zero, ECE_PLACE_ON_SURFACE) );
							if(!newEnt)continue;
							if(obj.GetInventory().CanAddEntityToInventory(newEnt))
							{
								obj.GetInventory().AddEntityToInventory(newEnt);
							}
							ItemBase newItem = ItemBase.Cast(newEnt);
							if (newItem)
				      {
								newItem = TraderPlusHelper.SetQuantity(newItem, items[i].Amount);
								newItem.SetHealth(items[i].Health);
								if(items[i].ExtraData != GARAGEVEHICLECARGO)
								{
									#ifdef MuchCarKey
										MCK_CarKey_Base vehicleKey;
										if(Class.CastTo(vehicleKey, newItem)){
											vehicleKey.SetNewMCKId(items[i].ExtraData);
										}
									#else
										#ifdef TRADER
										VehicleKeyBase vehicleKey;
										if(Class.CastTo(vehicleKey, newItem)){
												vehicleKey.SetNewHash(items[i].ExtraData);
										}
										#endif
					        #endif
								}
							}
					}
    	}

			obj.SetPosition(position);
			obj.SetPosition(obj.GetPosition() + Vector(0, 0.3, 0));
			obj.SetOrientation(orientation);
			vector roll = obj.GetOrientation();
			roll[2] = roll[2] - 1;
			obj.SetOrientation(roll);
			roll[2] = roll[2] + 1;
			obj.SetOrientation(roll);
			obj.SetDirection(obj.GetDirection());

			CarScript vehicle = CarScript.Cast(obj);
      if(vehicle)
      {
				if(GetGarageConfig().SaveVehicleHealth){
					#ifdef GMDEBUG
					GetGMLogger().LogInfo("Set Health:"+health);
					#endif
					vehicle.SetHealth(health);
				}

				float fuelReq = vehicle.GetFluidCapacity(CarFluid.FUEL);
    		float oilReq = vehicle.GetFluidCapacity(CarFluid.OIL);
    		float coolantReq = vehicle.GetFluidCapacity(CarFluid.COOLANT);
    		float brakeReq = vehicle.GetFluidCapacity(CarFluid.BRAKE);

				if(GetGarageConfig().SaveVehicleFuel){
					#ifdef GMDEBUG
					GetGMLogger().LogInfo("Set Fuel:"+fuel);
					#endif
					fuelReq = fuel;
				}
    		vehicle.Fill(CarFluid.FUEL, fuelReq);
    		vehicle.Fill(CarFluid.OIL, oilReq);
    		vehicle.Fill(CarFluid.COOLANT, coolantReq);
    		vehicle.Fill(CarFluid.BRAKE, brakeReq);

        //LOCK SCRIPT
				if(GetGarageConfig().VehicleMustHaveLock)
				{
					#ifdef GMDEBUG
					GetGMLogger().LogInfo("Set Lock:");
					#endif
					#ifndef CARLOCKDISABLE
	        	vehicle.SetCarLockOwner(player.CLSteamlowID);
						if(id != -1 || id != 0){
							vehicle.SetCarLockPassword(id);
						}
	        	vehicle.SetCarLock(true);
					#else
						#ifdef MuchCarKey
							if(id != 0){
								vehicle.m_HasCKAssigned = true;
								vehicle.m_CarKeyId = id;
								vehicle.SynchronizeValues();
							}
						#else
						 #ifdef TRADER
							 if(id != 0)
							 {
								 vehicle.m_Trader_HasKey = true;
								 vehicle.m_Trader_VehicleKeyHash = id;
								 vehicle.SynchronizeValues();
							 }
						 #endif
						#endif
	        #endif
				}
				#ifdef GMDEBUG
				GetGMLogger().LogInfo("return true");
				#endif
        return true;
      }
    }
		#ifdef GMDEBUG
		GetGMLogger().LogInfo("return false");
		#endif
    return false;
	}

	static bool CheckifPlayerHasEnoughMoney(PlayerBase player, int amount)
	{
		int playerMoneyAmount = GetPlayerMoney(player);
		if(playerMoneyAmount >= amount)
		{
			return true;
		}

		return false;
	}

	static bool RemoveMoneyFromPlayer(PlayerBase player, int amount)
	{
		if(GetGarageConfig().PayWithBankAccount)
    {
			int BankAmount = player.m_BankAccount.MoneyAmount;
			int newAmount = BankAmount - amount;
			TraderPlusBankHelpers.SetAmountBankAccount(player, newAmount);
			return true;
		}
		else
		{
			return TraderPlusBankHelpers.RemoveMoneyFromPlayer(player, amount);
		}
	}

	static int GetPlayerMoney(PlayerBase player)
	{
		if(GetGarageConfig().PayWithBankAccount)
    {
			if(!player.m_BankAccount)
			{
				TraderPlusBankingData m_tempdata = TraderPlusBankingData.Load(player.GetIdentity().GetPlainId(), GetTraderPlusBankConfigServer().DefaultMaxCurrency,GetTraderPlusBankConfigServer().DefaultStartCurrency,player.GetIdentity().GetName());
	      if(player.m_BankAccount)
	      {
	        player.m_BankAccount = m_tempdata;
	      }
			}

			return player.m_BankAccount.MoneyAmount;
    }
    else
    {
			return TraderPlusBankHelpers.GetPlayerMoney(player);
    }
	}
}
