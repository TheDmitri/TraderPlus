modded class DayZPlayerImplementFallDamage
{
	override void HandleFallDamage(float pHeight)
	{
		if (GetGame().IsServer()) {

			PlayerBase player = PlayerBase.Cast(m_Player);
			if (player && player.IsInsideSZ.SZStatut) {
				return;
			}
		}

		super.HandleFallDamage(pHeight);
	}
}
