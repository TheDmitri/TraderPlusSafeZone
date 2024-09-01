modded class TrapBase
{
  override void StartActivate( PlayerBase player )
  {
    if(SZStartActivateHandler(player))
      return;
      
    super.StartActivate(player);
  }

  bool SZStartActivateHandler(PlayerBase player)
  {
    if(!player)
      return false;

    if (player.GetSafeZoneStatus() == SZ_IN_SAFEZONE)
      return true;

    return false;
  }
}
