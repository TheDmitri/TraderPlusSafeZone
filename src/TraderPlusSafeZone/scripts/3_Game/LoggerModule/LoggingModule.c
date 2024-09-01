
static ref TraderPlusSafeZoneLoggingModule GetTraderPlusSafeZoneLogger()
{
    return TraderPlusSafeZoneLoggingModule.Cast(CF_ModuleCoreManager.Get(TraderPlusSafeZoneLoggingModule));
}

[CF_RegisterModule(TraderPlusSafeZoneLoggingModule)]
class TraderPlusSafeZoneLoggingModule : CF_ModuleGame
{
    private int networkSync_LogLevel;

    ref TraderPlusSafeZoneLoggingSettings settings;

    FileHandle fileHandle;

    float dtime = 0;


    override void OnInit()
    {
        super.OnInit();
        
        EnableUpdate();
        EnableMissionStart();
    }

    override void OnMissionStart(Class sender, CF_EventArgs args)
    {
        super.OnMissionStart(sender, args);

        fileHandle = CreateNewLogFile();

        if(GetGame().IsServer())
        {
            settings = TraderPlusSafeZoneLoggingSettings.Load();

            networkSync_LogLevel = settings.logLevel;
            SynchLogLevel();       
        }
        else
        {
            AddLegacyRPC("GetLogLevelResponse", SingleplayerExecutionType.Client);
        }
    }

    void GetLogLevelResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		 if (type != CallType.Client)
			 return;

		 Param1<int> data;
		 if (!ctx.Read(data))
            return;

		 networkSync_LogLevel = data.param1;
	}

    void SynchLogLevel()
    {
        GetRPCManager().SendRPC(ClassName(), "GetLogLevelResponse",  new Param1<int>(networkSync_LogLevel), true, NULL);
    }

    override void OnUpdate(Class sender, CF_EventArgs args)
    {
        auto update = CF_EventUpdateArgs.Cast(args);

        if(!GetGame().IsServer())
            return;

        if(!settings)
            return;

        dtime += update.DeltaTime;
        if(dtime >= settings.refreshRateInSeconds)
        {
            dtime = 0;

            settings = TraderPlusSafeZoneLoggingSettings.Load();

            networkSync_LogLevel = settings.logLevel;
            SynchLogLevel();
        }
    }


    void MakeDirectoryIfNotExists()
    {
        if(!FileExist(TraderPlusSafeZone_ROOT_FOLDER))
            MakeDirectory(TraderPlusSafeZone_ROOT_FOLDER);

        if(!FileExist(TraderPlusSafeZone_LOG_FOLDER))
            MakeDirectory(TraderPlusSafeZone_LOG_FOLDER);

        if(!FileExist(TraderPlusSafeZone_LOGGER_CONFIG_DIR))
            MakeDirectory(TraderPlusSafeZone_LOGGER_CONFIG_DIR);
        
        if(!FileExist(TraderPlusSafeZone_LOGGER_LOG_DIR))
            MakeDirectory(TraderPlusSafeZone_LOGGER_LOG_DIR);
    }
    
    string GenerateShortDateString()
    {
        int year, month, day;
        GetYearMonthDay(year, month, day);
        return "" + year + "_" + month + "_" + day;
    }

    string GenerateShortTimeString()
    {
        int hour, minute, second;
        GetHourMinuteSecond(hour, minute, second);
        return "" + hour + "_" + minute + "_" + second;
    }

    string GenerateFullTimestamp()
    {
        string dateStr = GenerateShortDateString();
        string timeStr = GenerateShortTimeString();

        return dateStr + "-" + timeStr;
    }

    FileHandle CreateNewLogFile()
    {
        MakeDirectoryIfNotExists();

        string filePath = string.Format(TraderPlusSafeZone_LOGGER_LOG_FILE, GenerateFullTimestamp());

        fileHandle = OpenFile(filePath, FileMode.WRITE);

        if(fileHandle != 0)
        {
            FPrintln(fileHandle, "Creation Time: " + GenerateFullTimestamp());
            return fileHandle;
        }

        return null;
    }

    void Log(string content, TraderPlusSafeZoneLogLevel logLevel)
    {
        if(logLevel < networkSync_LogLevel)
            return;
        
        string timestamp = GenerateShortTimeString();
        FPrintln(fileHandle, timestamp + " | " + GetLogLevelString(logLevel) + " | " + content);
    }

    void LogInfo(string content)
    {
        Log(content, TraderPlusSafeZoneLogLevel.Info);
    }

    void LogWarning(string content)
    {
        Log(content, TraderPlusSafeZoneLogLevel.Warn);
    }

    void LogError(string content)
    {
        Log(content, TraderPlusSafeZoneLogLevel.Error);
    }

    void LogDebug(string content)
    {
        Log(content, TraderPlusSafeZoneLogLevel.Debug);
    }

    string GetLogLevelString(TraderPlusSafeZoneLogLevel logLevel)
    {
        switch(logLevel)
        {
             case TraderPlusSafeZoneLogLevel.Debug:
                return "DEBUG";
            case TraderPlusSafeZoneLogLevel.Info:
                return "INFO";
            case TraderPlusSafeZoneLogLevel.Warn:
                return "WARNING";
            case TraderPlusSafeZoneLogLevel.Error:
                return "ERROR";
            default:
                return "";
        }

        return "";
    }

}