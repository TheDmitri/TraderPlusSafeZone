modded class MissionServer extends MissionBase
{
	void ~MissionServer() {
	}

	void MissionServer()
	{
		Print("TraderPlusSafeZone mod has started !");
		GetTraderPlusSafeZoneLogger().LogDebug("TraderPlusSafeZone mod has started!");
	}
};
