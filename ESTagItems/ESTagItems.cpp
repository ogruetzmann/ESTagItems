#include <cstdio>
#include "ESTagItems.h"

#define MY_PLUGIN_NAME      "ESTagItems"
#define MY_PLUGIN_VERSION   "1.0"
#define MY_PLUGIN_DEVELOPER "Oliver Grützmann"
#define MY_PLUGIN_COPYRIGHT "Free to be distributed as source code"

CESTagItems::CESTagItems()
	: CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE,
		MY_PLUGIN_NAME,
		MY_PLUGIN_VERSION,
		MY_PLUGIN_DEVELOPER,
		MY_PLUGIN_COPYRIGHT)
{
	RegisterTagItems();
}


CESTagItems::~CESTagItems()
{
}

void CESTagItems::OnGetTagItem(CFlightPlan FlightPlan, CRadarTarget RadarTarget, int ItemCode, int TagData, char sItemString[16], int * pColorCode, COLORREF * pRGB, double * pFontSize)
{
	switch (ItemCode)
	{
	case 1:
		GetVerticalSpeed(RadarTarget, sItemString);
	default:
		return;
	}
}

void CESTagItems::RegisterTagItems()
{
	RegisterTagItemType("Vertical Speed", 1);
}

void CESTagItems::GetVerticalSpeed(CRadarTarget & RadarTarget, char * result)
{
	int vs = RadarTarget.GetVerticalSpeed() / 250;
	if (vs < 0)
		vs *= -1;
	if (RadarTarget.GetVerticalSpeed() % 250 >= 125)
		++vs;
	if (vs >= 100)
	{
		strcpy_s(result, sizeof(result), "**");
		return;
	}
	if (vs != 0)
	{
		sprintf_s(result, sizeof(result), "%02i", vs);
		return;
	}
	strcpy_s(result, sizeof(result), "");
}
