class TraderPlusSafeZoneLoggingSettings 
{
    int logLevel = 0;
    int refreshRateInSeconds = 60;

    void MakeDirectoryIfNotExists()
    {
        if(!FileExist( TraderPlusSafeZone_ROOT_FOLDER))
            MakeDirectory( TraderPlusSafeZone_ROOT_FOLDER);

        if(!FileExist( TraderPlusSafeZone_LOG_FOLDER))
            MakeDirectory( TraderPlusSafeZone_LOG_FOLDER);

        if(!FileExist( TraderPlusSafeZone_LOGGER_CONFIG_DIR))
            MakeDirectory( TraderPlusSafeZone_LOGGER_CONFIG_DIR);
        
        if(!FileExist( TraderPlusSafeZone_LOGGER_LOG_DIR))
            MakeDirectory( TraderPlusSafeZone_LOGGER_LOG_DIR);
    }

    void Save()
    {
        JsonFileLoader<TraderPlusSafeZoneLoggingSettings>.JsonSaveFile( TraderPlusSafeZone_LOGGER_CONFIG_FILE, this);
    }

    static ref TraderPlusSafeZoneLoggingSettings Load()
    {
        TraderPlusSafeZoneLoggingSettings settings = new TraderPlusSafeZoneLoggingSettings();

        settings.MakeDirectoryIfNotExists();

        if(FileExist( TraderPlusSafeZone_LOGGER_CONFIG_FILE))
        {
            JsonFileLoader<TraderPlusSafeZoneLoggingSettings>.JsonLoadFile( TraderPlusSafeZone_LOGGER_CONFIG_FILE, settings);
            return settings;
        }

        settings.Save();
        return settings;
    }

}