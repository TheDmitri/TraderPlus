class CfgPatches
{
	class Garage_Script
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"TraderPlus_Script"
		};
	};
};
class CfgMods
{
	class Garage
	{
		dir="Garage";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Garage";
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
					"Garage/scripts/Common",
					"Garage/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"Garage/scripts/Common",
					"Garage/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"Garage/scripts/Common",
					"Garage/scripts/5_Mission"
				};
			};
		};
	};
};
class CfgVehicles
{

};
