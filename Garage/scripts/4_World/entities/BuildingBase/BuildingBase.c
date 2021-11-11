modded class BuildingBase
{
	override void SetActions()
	{
		super.SetActions();
	}

	void SetupGarageNPC(GarageNPC data)
	{
		SetTraderID(-3);
		SetPosition(data.Position);
		SetOrientation(data.Orientation);
		SetAllowDamage(false);
	}
}
