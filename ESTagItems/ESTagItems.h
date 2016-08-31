#pragma once
#include <Windows.h>
#include <cstdio>
#include <cmath>
#include "EuroScopePlugIn.h"

using namespace EuroScopePlugIn;

enum ItemTypes : int
{
	TAG_ITEM_TYPE_VERTICAL_SPEED = 101,
	TAG_ITEM_TYPE_VERTICAL_SPEED_INDICATOR,
	TAG_ITEM_TYPE_SQUAWK_COLOURED,
};

class CESTagItems :
	public EuroScopePlugIn::CPlugIn
{
public:
	CESTagItems();
	virtual ~CESTagItems();

	void OnGetTagItem(CFlightPlan FlightPlan,
					  CRadarTarget RadarTarget,
					  int ItemCode,
					  int TagData,
					  char sItemString[16],
					  int *pColorCode,
					  COLORREF *pRGB,
					  double *pFontSize);

private:
	COLORREF COLOR_UNCORRELATED = RGB(150, 150, 150);

	const int VerticalSpeedFactor = 200;
	void RegisterTagItems();
	int GetVerticalSpeed(const CRadarTarget &RadarTarget) const;
};
