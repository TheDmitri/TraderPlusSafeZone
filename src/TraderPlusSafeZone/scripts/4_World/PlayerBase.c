modded class PlayerBase
{
    private bool netSync_IsInSafeZone = false;

    override void Init()
    {
        super.Init();
        RegisterNetSyncVariableBool("netSync_IsInSafeZone");
    }

    void SetSafeZoneStatus(bool status)
    {
        netSync_IsInSafeZone = status;
        SetSynchDirty();
    }

    bool IsInSafeZone()
    {
        return netSync_IsInSafeZone;
    }
}