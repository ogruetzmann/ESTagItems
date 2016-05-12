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

void CESTagItems::OnGetTagItem(CFlightPlan FlightPlan,
							   CRadarTarget RadarTarget,
							   int ItemCode,
							   int TagData, char
							   sItemString[16],
							   int * pColorCode,
							   COLORREF * pRGB,
							   double * pFontSize)
{
	if (ItemCode == ESTagItems::TAG_ITEM_TYPE_VERTICAL_SPEED)
	{
		GetVerticalSpeed(RadarTarget, sItemString);
	}
}

void CESTagItems::RegisterTagItems()
{
	RegisterTagItemType("Vertical Speed", ESTagItems::TAG_ITEM_TYPE_VERTICAL_SPEED);
}

void CESTagItems::GetVerticalSpeed(const CRadarTarget & RadarTarget, char * sItemString)
{
	static std::stringstream stream;
	stream.clear();

	auto es_vs = RadarTarget.GetVerticalSpeed();
	if (es_vs < 0)
		es_vs *= -1;

	auto vs = es_vs / VerticalSpeedFactor;

	if (es_vs % VerticalSpeedFactor >= VerticalSpeedFactor / 2)
		vs++;

	if (vs >= 100)
	{
		stream.str("**\0");
		stream >> sItemString;
		return;
	}

	if (vs != 0)
	{
		stream.str("");
		stream << std::setw(2) << std::setfill('0') << vs << '\0';

		if (stream.str().length() <= 15)
			stream >> sItemString;

		return;
	}
}
