class CfgPatches
{
	class SafeZone_Script
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={};
	};
};
class CfgMods
{
	class SafeZone
	{
		dir="SafeZone";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="SafeZone";
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
					"SafeZone/scripts/Common",
					"SafeZone/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"SafeZone/scripts/Common",
					"SafeZone/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"SafeZone/scripts/Common",
					"SafeZone/scripts/5_Mission"
				};
			};
		};
	};
};
