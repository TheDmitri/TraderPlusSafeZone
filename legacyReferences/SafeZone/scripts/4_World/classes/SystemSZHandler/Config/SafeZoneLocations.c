class SafeZoneLocations
{
  string MsgEnterZone;
  string MsgExitZone;
  string MsgOnLeavingZone;
  bool   EnableAfkDisconnect;
  int    KickAfterDelay;
  ref array<string> Statut;
  ref array<float> X;
  ref array<float> Y;
  ref array<float> Radius;
  ref array<int> Countdowns;

    void SafeZoneLocations(SafeAreaSettings safeAreaSettings)
	  {
      EnableAfkDisconnect = safeAreaSettings.EnableAfkDisconnect;
      KickAfterDelay = safeAreaSettings.KickAfterDelay;
      MsgEnterZone = safeAreaSettings.MsgEnterZone;
      MsgExitZone = safeAreaSettings.MsgExitZone;
      MsgOnLeavingZone = safeAreaSettings.MsgOnLeavingZone;
      Statut = new array<string>;
      X = new array<float>;
      Y = new array<float>;
      Radius = new array<float>;
      Countdowns = new array<int>;

      TransferSafeConfig(safeAreaSettings);
    }

    void TransferSafeConfig(SafeAreaSettings safeAreaSettings)
    {
      int cpt = -1 + safeAreaSettings.SafeAreaLocation.Count();
      for(int i = 0; i<=cpt ; i++)
      {
        Statut.Insert(safeAreaSettings.SafeAreaLocation.Get(i).SafeZoneStatut);
        X.Insert(safeAreaSettings.SafeAreaLocation.Get(i).X);
        Y.Insert(safeAreaSettings.SafeAreaLocation.Get(i).Y);
        Radius.Insert(safeAreaSettings.SafeAreaLocation.Get(i).Radius);
        Countdowns.Insert(safeAreaSettings.SafeAreaLocation.Get(i).Countdown);
      }
    }
}
