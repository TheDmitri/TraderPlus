modded class VicinityItemManager
{
	override void AddVicinityItems(Object object)
	{
		if ( StashShouldShowInVicinity(object) )
			super.AddVicinityItems(object);
	}
	bool StashShouldShowInVicinity(Object filtered_object)
	{
		Print("StashShouldShowInVicinity");
		if (HideOutObject.Cast(filtered_object) && ( !GetGame().IsServer() || !GetGame().IsMultiplayer() ))
		{
			int shortId = GetGame().GetUserManager().GetTitleInitiator().GetUid().Substring(8, 9).ToInt();
			HideOutObject stash = HideOutObject.Cast(filtered_object);
			if (stash.GetOwner() != shortId)
				return false;
		}
		return true;
	};
}
