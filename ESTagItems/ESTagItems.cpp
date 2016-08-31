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
{}

void CESTagItems::OnGetTagItem(CFlightPlan FlightPlan,
							   CRadarTarget RadarTarget,
							   int ItemCode,
							   int TagData, char
							   sItemString[16],
							   int *pColorCode,
							   COLORREF *pRGB,
							   double *pFontSize)
{
	if (ItemCode == ItemTypes::TAG_ITEM_TYPE_VERTICAL_SPEED)
	{
		auto vs = abs(GetVerticalSpeed(RadarTarget));
		if (vs)
		{
			if (vs < 100)
				snprintf(sItemString, 16, "%02i", vs);
			else
				strcpy_s(sItemString, 16, "**");
		}
	}

	else if (ItemCode == ItemTypes::TAG_ITEM_TYPE_VERTICAL_SPEED_INDICATOR)
	{
		auto vs = GetVerticalSpeed(RadarTarget);
		if (vs)
		{
			auto vsi = [vs]() -> char
			{
				if (vs > 0) return '^'; else return '|';
			};
			if (abs(vs) < 100)
				snprintf(sItemString, 16, "%c%02i", vsi(), abs(vs));
			else
				snprintf(sItemString, 16, "%c%s", vsi(), "**");
		}
	}

	else if (ItemCode == ItemTypes::TAG_ITEM_TYPE_SQUAWK_COLOURED)
	{
		*pColorCode = TAG_COLOR_RGB_DEFINED;
		*pRGB = COLOR_UNCORRELATED;
		strcpy_s(sItemString, 16, RadarTarget.GetPosition().GetSquawk());
	}
}

void CESTagItems::RegisterTagItems()
{
	RegisterTagItemType("Vertical Speed", ItemTypes::TAG_ITEM_TYPE_VERTICAL_SPEED);
	RegisterTagItemType("Vertical Speed with indicator", ItemTypes::TAG_ITEM_TYPE_VERTICAL_SPEED_INDICATOR);
	RegisterTagItemType("Squawk Coloured", ItemTypes::TAG_ITEM_TYPE_SQUAWK_COLOURED);
}

int CESTagItems::GetVerticalSpeed(const CRadarTarget &RadarTarget) const
{
	auto es_vs = RadarTarget.GetVerticalSpeed();
	auto vs = es_vs / VerticalSpeedFactor;
	if (abs(es_vs % VerticalSpeedFactor) >= VerticalSpeedFactor / 2)
	{
		if (vs > 0)
			vs++;
		else
			vs--;
	}
	return vs;
}
