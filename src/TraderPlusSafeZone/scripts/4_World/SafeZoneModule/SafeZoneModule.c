[CF_RegisterModule(SafeZoneModule)]
class SafeZoneModule: CF_ModuleWorld ///: CF_ModuleWorld derivetive created with the name of our own module.
{
    ref SafeZoneSettings settings;

    ref SafeZoneHandler safeZoneHandler;

    override void OnInit() // executiuon of the module + initialization of the module.
    {
        super.OnInit(); 
        EnableMissionStart();
        EnableInvokeConnect();
    }

    void OnMissionStartHandler() // Our costume handler for the module.
    {
        if(GetGame().IsServer())
        {
            settings = SafeZoneSettings.Load();
        }
        else
        {
            settings = new SafeZoneSettings();
            safeZoneHandler = new SafeZoneHandler();
        }

        InitializeRPCs();
    }

    override void OnMissionStart(Class sender, CF_EventArgs args) //Called when the mission starts.
    {
        super.OnMissionStart(sender, args);
        OnMissionStartHandler(); // injecting our costume handler into the event.
    }

     
    void InitializeRPCs() //Adds Basic RPCs for the module to the RPC Manager for server and client.
    {
        if(GetGame().IsServer())
        {
            GetRPCManager().AddRPC("TraderPlusSafeZone", "GetSafeZoneStatus", this, SingleplayerExecutionType.Server );

            //review: that's good
            GetRPCManager().AddRPC("TraderPlusSafeZone", "EntitiesCleanUpRequest", this, SingleplayerExecutionType.Server ); // This is for the client. => no this section register it for the client
        }
        else
        {
            GetRPCManager().AddRPC("TraderPlusSafeZone", "GetConfigFromServer", this, SingleplayerExecutionType.Client );
        }
    }

    void OnPlayerConnect(PlayerIdentity sender) //Called when a player connects to the server.
    {
        GetRPCManager().SendRPC("TraderPlusSafeZone", "GetConfigFromServer", new Param1<SafeZoneSettings>(settings), true, sender);
    }

    PlayerBase GetPlayerByIdentity(PlayerIdentity sender)
  	{
  		int	low	 =	0;
  		int	high =	0;
  		GetGame().GetPlayerNetworkIDByIdentityID( sender.GetPlayerId(), low, high );
  		return PlayerBase.Cast( GetGame().GetObjectByNetworkId(low, high ));
  	}

    void GetSafeZoneStatus(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type != CallType.Server)
            return;

        Param1<bool> data;
        if(!ctx.Read(data))
            return;
        
        bool isInZone = data.param1;

        PlayerBase player = GetPlayerByIdentity(sender);
        if(player)
            player.SetSafeZoneStatus(isInZone);

        ApplyConditionBasedOnStatus(player);
    }
    
    void EntitiesCleanUpRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type != CallType.Server)
            return;

        Param1<SafeZoneLocation> data;
        if(!ctx.Read(data))
            return;

        SafeZoneLocation location = data.param1;
        if(!location)
            return;

        array<Object> safeZoneCleanUpList = new array<Object>();
        GetGame().GetObjectsAtPosition(location.position, location.radius, safeZoneCleanUpList, null);

        foreach (Object obj : safeZoneCleanUpList)
        {
            if (IsInRadius(obj, location) && (obj.IsInherited(ZombieBase) || (obj.IsInherited(AnimalBase) && !IsAllowedAnimal(obj, location))))
            {
                GetGame().ObjectDelete(obj);
            }
        }
    }
    
    bool IsInRadius(Object obj, SafeZoneLocation location)
    {
        vector objectPos = obj.GetPosition();
        vector flatObjectPos = Vector(objectPos[0], 0, objectPos[2]);
        vector flatZonePos = Vector(location.position[0], 0, location.position[2]);
        float distance = vector.Distance(flatObjectPos, flatZonePos);
        return distance <= location.radius;
    }
    
    
    bool IsAllowedAnimal(Object animal, SafeZoneLocation location)
    {
        foreach(string allowedAnimal : location.allowedAnimals)
        {
            if(CF_String.EqualsIgnoreCase(allowedAnimal, animal.GetType()))
                return true;
        }
        return false;
    }
    

    void ApplyConditionBasedOnStatus(PlayerBase player) // Applies a condition based on the player's safe zone status.
    {
        if(player.IsInSafeZone())
        {
            player.SetAllowDamage(false);
        }
        else
        {
            player.SetAllowDamage(true);
        }
    }

    void GetConfigFromServer(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type != CallType.Client)
            return;

        Param1<SafeZoneSettings> data;
        if(!ctx.Read(data))
            return;
        
        settings = data.param1;

        if(!safeZoneHandler.HasStarted()){   
            safeZoneHandler.Setup(settings);
        }
    }

    override void OnInvokeConnect(Class sender, CF_EventArgs args)
    {
        super.OnInvokeConnect(sender, args);

        CF_EventPlayerArgs cArgs = CF_EventPlayerArgs.Cast(args);

        if(!IsMissionHost())
            return;
        
        if(!cArgs.Player || !cArgs.Identity)
            return;
        
        OnPlayerConnect(cArgs.Identity);
    }
}