modded class ActionInjectTarget
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}

		return super.ActionCondition(player, target, item);
	}
}

modded class ActionDisinfectTarget
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}

		return super.ActionCondition(player, target, item);
	}
}

modded class ActionForceConsumeSingle
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}

		return super.ActionCondition(player, target, item);
	}
}

modded class ActionForceConsume
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}

		return super.ActionCondition(player, target, item);
	}
}

modded class ActionPackTent
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}

		return super.ActionCondition(player, target, item);
	}
};

modded class ActionGiveBloodTarget
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}

		return super.ActionCondition(player, target, item);
	}
}

modded class ActionCollectBloodTarget
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}

		return super.ActionCondition(player, target, item);
	}
}

modded class ActionBurnSewTarget
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}

		return super.ActionCondition(player, target, item);
	}
}

modded class ActionDeployObject
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}

		return super.ActionCondition(player, target, item);
	}
};

modded class ActionRestrainSelf
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}

		return super.ActionCondition(player, target, item);
	}
}

modded class ActionRestrainTarget
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			PlayerBase target_player = PlayerBase.Cast(target.GetObject());
			if (target_player && target_player.IsInsideSZ.SZStatut && player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}
		return super.ActionCondition(player, target, item);
	}
}

modded class ActionForceFeedCan
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}
		return super.ActionCondition(player, target, item);
	}
}

modded class ActionLockDoors
{
    override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
		{
			if(GetGame().IsServer())
			{
				if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
		            return false;
			}
			else
			{
				if(GetSafeZoneStatut() && !player.IsSZAdmin)
						return false;
			}
			return super.ActionCondition(player, target, item);
		}
}

modded class ActionUnpin extends ActionSingleUseBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}
		return super.ActionCondition(player, target, item);
	}
}

modded class ActionDigInStash: ActionContinuousBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}
		return super.ActionCondition(player, target, item);
	}
}

modded class ActionDigOutStash: ActionContinuousBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer())
		{
			if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
	            return false;
		}
		else
		{
			if(GetSafeZoneStatut() && !player.IsSZAdmin)
					return false;
		}
		return super.ActionCondition(player, target, item);
	}
}

#ifdef MuchCarKey
modded class ActionPickLockOnCar : ActionLockUnlockCar
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
			if(GetGame().IsServer())
			{
				if (player.IsInsideSZ.SZStatut && !player.IsSZAdmin)
		            return false;
			}
			else
			{
				if(GetSafeZoneStatut() && !player.IsSZAdmin)
						return false;
			}
			return super.ActionCondition(player, target, item);
    }
};
#endif
