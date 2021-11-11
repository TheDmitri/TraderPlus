class CfgPatches
{
	class TPDefine
	{
		requiredVersion = 0.1;
		requiredAddons[] = {};
	};
};

class CfgMods
{
	class TPDefine
	{
				dir="TPDefine";
        name="TP";
        type="mod";
	    	dependencies[]={ "GameLib", "Game", "World", "Mission"};
		    class defs
		    {

				class gameLibScriptModule
				{
					value = "";
					files[] = {
							"TPDefine/scripts/Common"
						};
				};
				class gameScriptModule
	            {
									value = "";
	                files[]={
										"TPDefine/scripts/Common"
									};
	            };

				class worldScriptModule
	            {
	                value="";
	                files[]={
											"TPDefine/scripts/Common"
									};
	            };

		        class missionScriptModule
	            {
	                value="";
	                files[]={
										"TPDefine/scripts/Common"
									};
	            };
	        };
	    };
};
