modded class Hologram
{
	override string ProjectionBasedOnParent()
	{
		ItemBase item_in_hands = ItemBase.Cast( m_Player.GetHumanInventory().GetEntityInHands() );

		 if ( item_in_hands.IsInherited( Receipt ))
		{
			Receipt carBox = Receipt.Cast(item_in_hands);
			return TraderPlusHelper.GetVehicleClassNameBasedOnID(carBox.CarID);
		}

		return super.ProjectionBasedOnParent();
	}

	override EntityAI PlaceEntity( EntityAI entity_for_placing )
	{
		ItemBase item_in_hands = ItemBase.Cast( m_Player.GetHumanInventory().GetEntityInHands() );

		if ( entity_for_placing.IsKindOf("ReceiptBase") )
		{
			/*Object obj = GetGame().CreateObject(m_Projection.GetType(), m_Projection.GetPosition());
			obj.SetOrientation(m_Projection.GetOrientation());
			Class.CastTo(entity_for_placing, obj);*/
			return entity_for_placing;
		}
		else return super.PlaceEntity(entity_for_placing);
	}

	override void EvaluateCollision(ItemBase action_item = null)
	{
		ItemBase item_in_hands = ItemBase.Cast( m_Player.GetHumanInventory().GetEntityInHands() );

		if(item_in_hands)
		{
			 if ( item_in_hands.IsInherited( ReceiptBase ))
			{
				SetIsColliding(false);
				return;
			}
		}
		super.EvaluateCollision();
	}
};
