#pragma once
#include <vector>

struct Globals
{
	struct
	{
		int Tab = 0;
		int rTab = 0;
	}Menu;

	bool isolated = false;
	bool shAllow = false;

	bool blockerOn = false;
	char eventBuffer[512];

	int currentResource = 0;
	const char* current_resource = "";
	std::vector<const char*> resources =
	{
		"AWPH",
		"BF3",
		"BusterSword",
		"CoordsSaver1",
		"Cuopxehang",
		"EasyAdmin",
		"EasyAdmin-MySQL",
		"F4mini",
		"FiveM-BanSql",
		"GunBlade",
		"IRS_esx",
		"LegacyFuel",
		"DmgCheck",
		"ESX_CommunnityService",
		"DowntownPenthouse",
		"Dev_CodersTrieuDo",
		"D2FiveM",
		"IRSskinpack",
		"InteractSound2",
		"InteractSoundS",
		"JF_SeatShuffle",
		"Jason",
		"LRPT",
		"MSR",
		"MagikSword",
		"MeleeMod",
		"antiweaponbug",
		"api",
		"async",
		"bankrobberies",
		"bob74_ipl",
		"boxing",
		"burglary",
		"cassino_props",
		"ch3_04",
		"ch3_12",
		"ch3_additions",
		"crafting",
		"cron",
		"defib",
		"delivery",
		"discord",
		"discord_perms",
		"dpclothing",
		"dpemotes",
		"egoista",
		"el_business",
		"electric-skateboard",
		"es_extended",
		"esx_addonaccount",
		"esx_addons_gcphone",
		"esx_admin",
		"esx_adminplus",
		"esx_advancedgarage",
		"esx_aircraftshop",
		"esx_ambulancejob",
		"esx_barbershop",
		"esx_basicneeds",
		"esx_billing",
		"esx_boatshop",
		"esx_burglary",
		"esx_business",
		"esx_carRental",
		"esx_carlock",
		"esx_carwash",
		"esx_contract",
		"esx_dirtyshops",
		"esx_dmvschool",
		"esx_doorlock",
		"esx_drugeffects",
		"esx_drugs"
	};

	const char* freemenu = "";
	const char* premmenu = "";

	std::vector<const char*> free_menus =
	{
		"HoaX_2.0",
		"Lynx_8.1",
		"Lynx_10.0",
		"InSec_1.0",
		"SkidMenu_1.0",
		"TiagoMenu_3.0",
		"TiagoMenu_4.0",
		"TiagoMenu_4.1",
		"Strata_1.0",
		"Lydia_Enterprise",
		"m1000"
	};

	std::vector<const char*> prem_menus =
	{
		"Absolute",
		"Lumia"
	};
};
extern Globals* globals;