class SafeZoneHandler
{
    PlayerBase player;

    private bool isInZone = false;
    private bool hasStarted = false;

    ref SafeZoneSettings settings;
    ref SafeZoneLocation selectedLocation;

    bool IsPlayerInside()
    {
        return isInZone;
    }

    PlayerBase GetPlayer()
    {
        if(!player)
            player = PlayerBase.Cast(GetGame().GetPlayer());

        return player;
    }

    bool HasStarted()
    {
        return hasStarted;
    }

    void Setup(SafeZoneSettings settings)
    {
        this.settings = settings;

        hasStarted = true;

        player = GetPlayer();

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Update, 1000, true);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RemoveUnwantedEntities, 5000, true);
    }

    void Update()
    {
        CheckSafeZoneLocation();
    }

    void CheckSafeZoneLocation()
    {
        foreach(SafeZoneLocation location: settings.locations)
        if(location.isActive)// Only Check Active Locations
        {
            CheckSafeZoneLocation(location);
        }
    }

    void OnEnterSafeZone()
    {
        isInZone = true;
        NotificationSystem.AddNotificationExtended( settings.notificationTimer, settings.notificationTitle, settings.msgOnEnteringZone, "TraderPlusSafeZone/datasets/shield.paa" );
        GetRPCManager().SendRPC("TraderPlusSafeZone", "GetSafeZoneStatus", new Param1<bool>(isInZone), true, null);
    }

    void OnExitSafeZone()
    {
        isInZone = false;
        selectedLocation = null;
        NotificationSystem.AddNotificationExtended( settings.notificationTimer, settings.notificationTitle, settings.msgOnLeavingZone, "TraderPlusSafeZone/datasets/shield.paa" );
        GetRPCManager().SendRPC("TraderPlusSafeZone", "GetSafeZoneStatus", new Param1<bool>(isInZone), true, null);
    }

    void CheckSafeZoneLocation(SafeZoneLocation location)
    {
        bool IsCurrentlyInZone = IsInRadius(location.position, location.radius);

        if(!isInZone && IsCurrentlyInZone)
        {
            selectedLocation = location;
            OnEnterSafeZone();
        }
        else if(isInZone && !IsCurrentlyInZone && selectedLocation == location)
        {
            OnExitSafeZone();
        }
    }

    bool IsInRadius(vector position, int radius)
    {
        vector playerPos = Vector(GetPlayer().GetPosition()[0], 0, GetPlayer().GetPosition()[2]);
        vector safeZonePos = Vector(position[0], 0, position[2]);
        float distance = vector.Distance(playerPos, safeZonePos);
        return distance <= radius;
    }   

    void RemoveUnwantedEntities() // This is to clean up the entities in the safezone.
    {
        if (!selectedLocation || !selectedLocation.isEntitiesCleanActive) // If the location is not active or the clean up is not active, return.
            return;

        array<Object> safeZoneCleanUpList = new array<Object>();
        GetGame().GetObjectsAtPosition(selectedLocation.position, selectedLocation.radius, safeZoneCleanUpList,null);

        foreach (Object obj : safeZoneCleanUpList)
        {
            if (obj.IsInherited(ZombieBase) || (obj.IsInherited(AnimalBase) && !IsAllowedAnimal(obj, selectedLocation)))
            {
                // Notify the server of entities to kill in the location. The server will have to check again using a similar method and kill them accordingly.
                // (use RPC)
                GetRPCManager().SendRPC("TraderPlusSafeZone", "RemoveEntity", new Param1<Object>(obj), true, null); // This is to remove the entity from the safezone RPC call.
            }
        }
    }

    bool IsAllowedAnimal(Object animal, SafeZoneLocation location) // This is to check if the animal is allowed in the safezone.
    {
        foreach(string allowedAnimal : location.allowedAnimals)
        {
            if(CF_String.EqualsIgnoreCase(allowedAnimal, animal.GetType()))
                return true;
        }
        return false;
    }
}