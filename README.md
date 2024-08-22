# Description
The purpose of this module is to create area where player have restriction. It can be a full godmode safezone or a simply no fire safezone or a zone with simple messages when entering and leaving.

For all Safezones, it will be necessary to :
1. Block different all kind of actions.
2. Disable FallDamage.
3. Define a cleanup entities (needs to have exception with authorizedAnimals).
4. Set a notification on entering and leaving the safezone.
5. Create a custom ui for showing a leaving the Safezone in X seconds .

Then for each safezone, we can define the following features:

1. Ability to set the safezone in full god mode or not (damage or no damage)
2. Ability to set to no fire or not 
3. Ability to have a custom leaving counter that will make the player leave the safezone only after the counter is done
4. Ability to specify a list of animals that won't be clean up in the area like HunterZ dogs or horses ;)


# Settings 

## General settings for the safezone system

- version - string : useful for versioning (start at 0.0.1)
- msgOnEnteringZone - string : message that appear in the notification when entering
- msgOnLeavingZone - string : message that appear after countdown is down when leaving
- safezones - array<TraderPlusSafezone> : list of safeZone object

## SafeZone settings for one instance

- fullGodMode - bool : if set to 1, the user cannot take damage
- noFire - bool : if set to 1, the user won't be able to shoot on other people
- leavingCounter - int : define the counter value before the player actually leave the safezone
- authorizedAnimals - array<string>: specify the list of animals that won't be clean up in the area
