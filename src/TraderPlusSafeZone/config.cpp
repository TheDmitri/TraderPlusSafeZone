class CfgPatches
{
	class TraderPlusSafeZone_Script
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={};
	};
};
class CfgMods
{
	class TraderPlusSafeZone
	{
		dir="TraderPlusSafeZone";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="TraderPlusSafeZone";
		credits="TheDmitri";
		author="TheDmitri";
		authorID="0";
		version="1.1";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"TraderPlusSafeZone/scripts/Common",
					"TraderPlusSafeZone/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"TraderPlusSafeZone/scripts/Common",
					"TraderPlusSafeZone/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"TraderPlusSafeZone/scripts/Common",
					"TraderPlusSafeZone/scripts/5_Mission"
				};
			};
		};
	};
};
class CfgVehicles
{

};
