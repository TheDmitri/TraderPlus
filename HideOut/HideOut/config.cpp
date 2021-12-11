class CfgPatches
{
	class HideOut_Script
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};
class CfgMods
{
	class HideOut
	{
		dir="HideOut";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="HideOut";
		credits="TheDmitri";
		author="TheDmitri";
		authorID="0";
		version="1.0";
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
					"HideOut/HideOut/scripts/Common",
					"HideOut/HideOut/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"HideOut/HideOut/scripts/Common",
					"HideOut/HideOut/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"HideOut/HideOut/scripts/Common",
					"HideOut/HideOut/scripts/5_Mission"
				};
			};
		};
	};
};
class CfgSlots
{
	class Slot_HideOut
	{
		name="HideOut";
		displayName="HideOut";
		selection="slot_hideout";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
};
