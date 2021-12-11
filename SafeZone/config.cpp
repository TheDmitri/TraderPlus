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
class CfgVehicles
{
	class Container_Base;
	class HideOutObject: Container_Base
	{
		scope=2;
		displayName="HideOutObject";
		descriptionShort="";
		inventorySlot="Armband";
		attachments[] = {"Armband"};
		weight=980;
		itemSize[]={4,3};
		itemsCargoSize[]={10,10};
		openable = 1;
		canBeDigged=0;
		isMeleeWeapon=0;
		allowOwnedCargoManipulation=0;
	};
};
