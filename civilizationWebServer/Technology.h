#pragma once

#include "Common.h"
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"
#include "Upgrade.h"
#include "Wonder.h"
#include "Unit.h"

#define TECH_COUNT 53
	
using namespace rapidjson;

enum TECH_BENEFITS
{
	WONDER_BENEFIT = (1 << 0),
	SEMINAL_BENEFIT = (1 << 1),
	PRODUCTIVE_BENEFIT = (1 << 2),
	HAPPY_BENEFIT = (1 << 3),
	CITY_BENEFIT = (1 << 4),
	TRADE_BENEFIT = (1 << 5),
	INFANTRY_BENEFIT = (1 << 6),
	CAVALRY_BENEFIT = (1 << 7),
	ARTILLERY_BENEFIT = (1 << 8),
	FLEET_BENEFIT = (1 << 9),
	AIRCRAFT_BENEFIT = (1 << 10)
};
inline TECH_BENEFITS operator|(TECH_BENEFITS a, TECH_BENEFITS b)
{
	return static_cast<TECH_BENEFITS>(static_cast<int>(a) | static_cast<int>(b));
}


class Technology
{
private:
	char* Name;
	TECH_ERA Era;
	int Cost;
	int Owner;
	int DepCount;
	Technology** DependsOn;
	Upgrade** Upgrades;
	int UpgradeCount;
	Unit** Units;
	int UnitCount;
	Wonder** Wonders;
	int WonderCount;
	int Id;
	TECH_BENEFITS Benefits;
	char* BenefitText;
	char* EnablesText;
	Value* jsonObject;

	static Technology* TechTree[TECH_COUNT];
	static int IdCount;
	static char* TextJSON;
	

public:
	static Technology** GetTechTree();

//	Technology();
	Technology(char* name, TECH_ERA era, int cost, TECH_BENEFITS benefits);
	(const char*) GetName();
	int GetCost();
	void Purchase(int player);
	void GetJSON(Document* document, Value* array, bool minimal = false);
	void SetDependencies(int n, ...);
	void SetUpgrades(int n, ...);
	void SetUnits(int n, ...);
	void SetWonders(int n, ...);

	static void InitTech();
	static char* GetTechStatusJSON();
	static void Purchase(int tech, int player);
	static void LoadState(Document* document);
	static void SaveState(Document* document);
	static int GetVictoryPoints(int player);
	~Technology();
};

