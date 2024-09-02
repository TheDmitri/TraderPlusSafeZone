class SafeZoneSettings //Basic settings for .json configg file.
{
    int notificationTimer = 10; 
    string notificationTitle = "SafeZone";
    string msgOnEnteringZone = "You entered the safezone!";
    string msgOnLeavingZone = "You have left the safezone!";
    ref array<ref SafeZoneLocation> locations;    
    void SafeZoneSettings() // Default constructor location class variable. 
    {
        locations = new array<ref SafeZoneLocation>();
    }

    void DefaultSettings() // Basic default config input as place holder to make sure the mod works.
    {
          locations.Insert(new SafeZoneLocation(true, 1, "Kamenka", Vector(1755.869995, 5.822320, 2204.840088), 100, true, new array<string>));
          locations.Insert(new SafeZoneLocation(true, 2, "Ostrog", Vector(2645.508057, 121.447723, 2202.255127), 100, true, new array<string>));
          locations.Insert(new SafeZoneLocation(true, 3, "Mys Krutoy", Vector(13646.174805, 25.352015, 3890.636475), 100, true, new array<string>));
          SaveSettings();
    }

    void SaveSettings()
    {
        JsonFileLoader<SafeZoneSettings>.JsonSaveFile(Safe_Zone_Config_Filename, this);
    }

    static void CheckDirectories()  // Makes directory check for root folders to be created if need be.
    {
        if(!FileExist(Safe_Zone_Root_Server))
        {
            MakeDirectory(Safe_Zone_Root_Server);
        }

        if(!FileExist(Safe_Zone_Config_Dir_Server))
        {
            MakeDirectory(Safe_Zone_Config_Dir_Server);
        }
    }

    static SafeZoneSettings Load() // Loads the config file.
    {
        SafeZoneSettings settings = new SafeZoneSettings();
        
        CheckDirectories();

        if(FileExist(Safe_Zone_Config_Filename))
        {
            JsonFileLoader<SafeZoneSettings>.JsonLoadFile(Safe_Zone_Config_Filename, settings);
            return settings;
        }

        settings.DefaultSettings();
        return settings;
    }
}