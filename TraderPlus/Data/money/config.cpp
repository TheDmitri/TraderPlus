class CfgPatches
{
	class TraderPlus_Money
	{
		units[]={};
		weapons[]={};
		requiredVersion		= 0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class TraderPlus_Wallet: Inventory_Base
	{
	  scope = 2;
	  displayName="$STR_Wallet";
	  descriptionShort="$STR_Wallet_des";
	  model = "TraderPlus\Data\Wallet\Wallet.p3d";
		weight=130;
		itemSize[]={2,2};
		itemsCargoSize[]={6,4};
		canBeDigged=0;
		allowOwnedCargoManipulation=1;
	};
	class TraderPlusMoney_Base: Inventory_Base
	{
		scope = 0;
		hiddenSelections[]=
		{
			"banknote"
		};
		overrideDrawArea="5.0";
		rotationFlags = 16;
		lootCategory = "Materials";
		lootTag[] = {"Civilian", "Work"};
		itemSize[] = {2,1};
		weight = 1;
		quantityBar=0;
		canBeSplit=1;
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 500;
		varQuantityDestroyOnMin = 1;
		destroyOnEmpty = 1;
		isMeleeWeapon=0;
		absorbency = 1;
	};

	class TraderPlus_Money_Dollar1: TraderPlusMoney_Base
	{
		scope = 2;
		displayName="$STR_1USD";
		descriptionShort = "$STR_USD_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\USD_1.paa"
		};
	};
	class TraderPlus_Money_Dollar2: TraderPlusMoney_Base
	{
		scope = 2;
		displayName="$STR_2USD";
		descriptionShort = "$STR_USD_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\USD_2.paa"
		};
	};
	class TraderPlus_Money_Dollar5: TraderPlusMoney_Base
	{
		scope = 2;
		displayName="$STR_5USD";
		descriptionShort = "$STR_USD_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\USD_5.paa"
		};
	};
	class TraderPlus_Money_Dollar10: TraderPlusMoney_Base
	{
		scope = 2;
		displayName="$STR_10USD";
		descriptionShort = "$STR_USD_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\USD_10.paa"
		};
	};
	class TraderPlus_Money_Dollar20: TraderPlusMoney_Base
	{
		scope = 2;
		displayName="$STR_20USD";
		descriptionShort = "$STR_USD_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\USD_20.paa"
		};
	};
	class TraderPlus_Money_Dollar50: TraderPlusMoney_Base
	{
		scope = 2;
		displayName="$STR_50USD";
		descriptionShort = "$STR_USD_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\USD_50.paa"
		};
	};
	class TraderPlus_Money_Dollar100: TraderPlusMoney_Base
	{
		scope = 2;
		displayName="$STR_100USD";
		descriptionShort = "$STR_USD_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\USD_100.paa"
		};
	};
	class TraderPlus_Money_Euro5: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_5EUR";
		descriptionShort = "$STR_EUR_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Euro_5.paa"
		};
	};
	class TraderPlus_Money_Euro10: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_10EUR";
		descriptionShort = "$STR_EUR_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Euro_10.paa"
		};
	};
	class TraderPlus_Money_Euro20: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_20EUR";
		descriptionShort = "$STR_EUR_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Euro_20.paa"
		};
	};
	class TraderPlus_Money_Euro50: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_50EUR";
		descriptionShort = "$STR_EUR_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Euro_50.paa"
		};
	};
	class TraderPlus_Money_Euro100: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_100EUR";
		descriptionShort = "$STR_EUR_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Euro_100.paa"
		};
	};
	class TraderPlus_Money_Euro200: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_200EUR";
		descriptionShort = "$STR_EUR_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Euro_200.paa"
		};
	};
	class TraderPlus_Money_Euro500: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_500EUR";
		descriptionShort = "$STR_EUR_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Euro_500.paa"
		};
	};

	class TraderPlus_Money_Ruble5: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_5RUB";
		descriptionShort = "$STR_RUB_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Ruble_5.paa"
		};
	};
	class TraderPlus_Money_Ruble10: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_10RUB";
		descriptionShort = "$STR_RUB_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Ruble_10.paa"
		};
	};
	class TraderPlus_Money_Ruble50: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_50RUB";
		descriptionShort = "$STR_RUB_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Ruble_50.paa"
		};
	};
	class TraderPlus_Money_Ruble100: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_100RUB";
		descriptionShort = "$STR_RUB_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Ruble_100.paa"
		};
	};
	class TraderPlus_Money_Ruble200: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_200RUB";
		descriptionShort = "$STR_RUB_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Ruble_200.paa"
		};
	};
	class TraderPlus_Money_Ruble500: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_500RUB";
		descriptionShort = "$STR_RUB_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Ruble_500.paa"
		};
	};
	class TraderPlus_Money_Ruble1000: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_1000RUB";
		descriptionShort = "$STR_RUB_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Ruble_1000.paa"
		};
	};
	class TraderPlus_Money_Ruble2000: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_2000RUB";
		descriptionShort = "$STR_RUB_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Ruble_2000.paa"
		};
	};
	class TraderPlus_Money_Ruble5000: TraderPlusMoney_Base
	{
		scope = 2;
		displayName = "$STR_5000RUB";
		descriptionShort = "$STR_RUB_des";
		model = "TraderPlus\Data\money\Bank_Note_Base.p3d";
		hiddenSelectionsTextures[]=
		{
			"TraderPlus\Data\money\data\Ruble_5000.paa"
		};
	};
	class TraderPlusCoin_Base: Inventory_Base
	{
		scope = 0;
		overrideDrawArea = "5.0";
		rotationFlags = 16;
		lootCategory = "Materials";
		lootTag[] = {"Civilian","Work"};
		itemSize[] = {1,1};
		weight = 1;
		quantityBar = 0;
		canBeSplit = 1;
		isMeleeWeapon = 0;
		absorbency = 1;
	};
	class TraderPlus_Bitcoin: TraderPlusCoin_Base
	{
		scope = 2;
		displayName = "1 BTC";
		descriptionShort = "$STR_BITCOIN_des";
		model = "TraderPlus\Data\money\Coin_Bitcoin.p3d";
		canBeSplit = 1;
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 5;
		quantityBar = 0;
	};
	class TraderPlus_Coin: TraderPlusCoin_Base
	{
		scope = 2;
		displayName = "1 Ruble Coin";
		descriptionShort = "$STR_RUB_des";
		model = "TraderPlus\Data\money\Coin_RUS_Empire.p3d";
		canBeSplit = 1;
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 5;
		quantityBar = 0;
	};
	class TraderPlus_Money_Ruble1_Coin: TraderPlusCoin_Base
	{
		scope = 2;
		displayName = "1 Ruble Coin";
		descriptionShort = "$STR_RUB_des";
		//model = "TraderPlus\Data\money\1ruble.p3d";
		model = "TraderPlus\Data\money\Coin_Ruble1.p3d";
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 100;
		varQuantityDestroyOnMin = 1;
		destroyOnEmpty = 1;
	};
	class TraderPlus_Money_Ruble2_Coin: TraderPlusCoin_Base
	{
		scope = 2;
		displayName = "2 Ruble Coin";
		descriptionShort = "$STR_RUB_des";
		model = "TraderPlus\Data\money\Coin_Ruble2.p3d";
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 100;
		varQuantityDestroyOnMin = 1;
		destroyOnEmpty = 1;
	};
	class TraderPlus_Money_Ruble5_Coin: TraderPlusCoin_Base
	{
		scope = 2;
		displayName = "5 Ruble Coin";
		descriptionShort = "$STR_RUB_des";
		model = "TraderPlus\Data\money\Russia_5_rub.p3d";
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 100;
		varQuantityDestroyOnMin = 1;
		destroyOnEmpty = 1;
	};
	class TraderPlus_Money_Euro1: TraderPlusCoin_Base
	{
		scope = 2;
		displayName = "1 Euro Coin";
		descriptionShort = "$STR_EUR_des";
		model = "TraderPlus\Data\money\Coin_Euro1.p3d";
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 100;
	};
	class TraderPlus_Money_Euro2: TraderPlusCoin_Base
	{
		scope = 2;
		displayName = "2 Euro Coin";
		descriptionShort = "$STR_EUR_des";
		model = "TraderPlus\Data\money\Coin_Euro2.p3d";
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 100;
	};
};
