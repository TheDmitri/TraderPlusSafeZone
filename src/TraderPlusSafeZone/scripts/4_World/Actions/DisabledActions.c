modded class ActionRestrainTarget
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
    {
        if(player.IsInSafeZone())
            return false;

        return super.ActionCondition(player, target, item);
    }
}

modded class ActionRestrainSelf
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
    {
        if(player.IsInSafeZone())
            return false;

        return super.ActionCondition(player, target, item);
    }
}

modded class ActionDeployObject
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
    {
        if(player.IsInSafeZone())
            return false;

        return super.ActionCondition(player, target, item);
    }
}

modded class ActionLockDoors
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
    {
        if(player.IsInSafeZone())
            return false;

        return super.ActionCondition(player, target, item);
    }
}

modded class ActionUnpin
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
    {
        if(player.IsInSafeZone())
            return false;

        return super.ActionCondition(player, target, item);
    }
}


