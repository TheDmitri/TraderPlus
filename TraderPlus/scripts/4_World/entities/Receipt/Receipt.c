class ReceiptBase extends ItemBase
{
	int CarID=0;
	int CarAttachments=0;

	void ReceiptBase()
	{
		RegisterNetSyncVariableInt("CarID");
		RegisterNetSyncVariableInt("CarAttachments");
	}

	void SetCarID(int id)
	{
		CarID = id;
		SetSynchDirty();
	}

	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionDeployVehicle);
	}

	override void OnPlacementComplete( Man player, vector position = "0 0 0", vector orientation = "0 0 0" )
	{
			super.OnPlacementComplete( player );
			PlayerBase pb = PlayerBase.Cast( player );
			if ( GetGame().IsServer() )
			{
					PlayerBase player_base = PlayerBase.Cast( player );
					vector pposition = player_base.GetLocalProjectionPosition();
					pposition[1]=pposition[1]+GetTraderPlusVehiculeConfig().VehiclesParts.Get(CarID).Height;
					vector oorientation = player_base.GetLocalProjectionOrientation();

					TraderPlusHelper.CreateVehicle(player_base,TraderPlusHelper.GetVehicleClassNameBasedOnID(CarID),pposition,oorientation);

					pb.DropItem(this);
					GetTraderPlusLogger().LogInfo("I'm not here");
					this.Delete();
			}
			SetIsDeploySound( true );
	}

	override void OnStoreSave( ParamsWriteContext ctx )
	 {
			super.OnStoreSave(ctx);
			Param2<int,int> data = new Param2<int,int>(CarID,CarAttachments);
			ctx.Write(data);
	 }

	override bool OnStoreLoad( ParamsReadContext ctx, int version )
		{
			if ( !super.OnStoreLoad( ctx, version ) )
				return false;

					Param2<int,int> data = new Param2<int,int>(-1,-1);
					if (ctx.Read(data))
					{
							CarID = data.param1;
							CarAttachments = data.param2;
					}
					return true;
			}
};

class Receipt extends ReceiptBase
{

}
