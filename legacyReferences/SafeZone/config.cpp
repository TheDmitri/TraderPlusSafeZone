////////////////////////////////////////////////////////////////////
//DeRap: SafeZone\config.bin
//Produced from mikero's Dos Tools Dll version 8.57
//https://mikero.bytex.digital/Downloads
//'now' is Mon May 29 15:45:30 2023 : 'file' last modified on Thu Jan 01 01:00:01 1970
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class SafeZone_Script
	{
		units[] = {"HideOutObject"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgMods
{
	class SafeZone
	{
		dir = "SafeZone";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "SafeZone";
		credits = "TheDmitri";
		author = "TheDmitri";
		authorID = "0";
		version = "1.1";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"SafeZone/scripts/Common","SafeZone/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"SafeZone/scripts/Common","SafeZone/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"SafeZone/scripts/Common","SafeZone/scripts/5_Mission"};
			};
		};
	};
};
class CfgVehicles
{
	class Armband_Yellow;
	class HideOutObject: Armband_Yellow
	{
		scope = 2;
		displayName = "HideOutObject";
		descriptionShort = "This is a personnal stash cargo. Its content is personnal to you and can't be seen by other people.";
		weight = 980;
		storageCategory = 1;
		itemSize[] = {3,4};
		itemsCargoSize[] = {10,15};
		attachments[] = {"Truck_01_WoodenCrate1","Truck_01_WoodenCrate2","Truck_01_WoodenCrate3","Truck_01_WoodenCrate4","Shoulder"};
	};
};
