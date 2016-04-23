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
	*pColorCode = TAG_COLOR_DEFAULT;
	switch (ItemCode)
	{
	case 1:
	{
		GetVerticalSpeed(RadarTarget, sItemString);
		break;
	}
	default:
		break;
	}
}

void CESTagItems::RegisterTagItems()
{
	RegisterTagItemType("Vertical Speed", 1);
}

void CESTagItems::GetVerticalSpeed(const CRadarTarget & RadarTarget, char * sItemString)
{
	static std::stringstream stream;
	stream.clear();

	int vs = RadarTarget.GetVerticalSpeed() / VerticalSpeedFactor;
	if (vs < 0)
		vs *= -1;

	if (RadarTarget.GetVerticalSpeed() % VerticalSpeedFactor >= VerticalSpeedFactor2)
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
		stream >> sItemString;
		return;
	}
}
