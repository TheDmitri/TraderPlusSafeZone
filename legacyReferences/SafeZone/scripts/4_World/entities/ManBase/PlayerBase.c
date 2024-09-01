//for retrocompatibility do not use for modding use instead GetSafeZoneName(), SetSafeZoneName()
//for retrocompatibility do not use for modding use instead GetSafeZoneStatus() == SZ_IN_SAFEZONE or GetSafeZoneName() == SZ_OUT_SAFEZONE
class InsideSZ{

	string SZName;
	bool   SZStatut;

	void InsideSZ(){
		SZName="";
		SZStatut=false;
	}
}

modded class PlayerBase extends ManBase
{
	private int m_SafeZoneStatus;
	private string m_SafeZoneName;

	bool m_IsStashDisable = false;

	ref InsideSZ IsInsideSZ;

	//for retrocompatibility do not use for modding use instead GetSafeZoneStatus() == SZ_IN_SAFEZONE or GetSafeZoneName() == SZ_OUT_SAFEZONE
	bool IsSZAdmin = false;

	int m_SZ_InfluenzaEnteredSafeZone;

	override void Init()
	{
		m_SafeZoneStatus = 0;
		m_SafeZoneName = "";
		super.Init();
		IsInsideSZ=new InsideSZ;
		RegisterNetSyncVariableInt("m_SafeZoneStatus");
	}

	bool IsTraderPlusAdmin()
	{
		if(GetGame().IsServer())
			return GetSZConfig().SZSteamUIDs.Find(GetIdentity().GetPlainId()) != -1;

		return false;
	}

	void SetAdminStatus()
	{
		m_SafeZoneStatus = m_SafeZoneStatus | 0x02;
		SetSynchDirty();
	}

	void SetSafeZoneStatus(bool state)
	{
		if(state)
			m_SafeZoneStatus = m_SafeZoneStatus | 0x01;
		else
			m_SafeZoneStatus = m_SafeZoneStatus & 0xFE;

		SetSynchDirty();
	}

	void SetSafeZoneName(string name)
	{
		m_SafeZoneName = name;
	}

	int GetSafeZoneStatus()
	{
		return m_SafeZoneStatus & 0x01;
	}

	int GetAdminStatus()
	{
		return m_SafeZoneStatus & 0x02;
	}

	string GetSafeZoneName()
	{
		return m_SafeZoneName;
	}

	override void SetSuicide(bool state)
	{
		super.SetSuicide(state);
		SZSetSuicideHandler(state);
	}

	//for modding ability
	void SZSetSuicideHandler(bool state)
	{
		if(!state)
			return;

		if(!GetGame().IsServer())
			return;

		if (GetSafeZoneStatus() != SZ_IN_SAFEZONE)
			return;

		SetAllowDamage(true);
		SetSafeZoneStatus(false);
	}

	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult,damageType,source,component,dmgZone,ammo,modelPos,speedCoef);
		SZEEHitByHandler(damageResult,damageType,source,component,dmgZone,ammo,modelPos,speedCoef);
	}

	//for modding ability
	void SZEEHitByHandler(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if(GetSafeZoneStatus() == SZ_IN_SAFEZONE)
		{
			if(source.IsDayZCreature() || source.IsAnimal());
				source.Delete();

			#ifdef SZDEBUG
				GetTraderPlusLogger().LogInfo(this.GetIdentity().GetName()+"the source of damage has been deleted");
			#endif
		}
	}
}
