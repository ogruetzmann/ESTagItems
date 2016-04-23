#pragma once
#include <Windows.h>
#include <sstream>
#include <iomanip>
#include "EuroScopePlugIn.h"

using namespace EuroScopePlugIn;

namespace ESTagItems
{
	const int TAG_ITEM_TYPE_VERTICAL_SPEED = 101;
};

class CESTagItems :
	public EuroScopePlugIn::CPlugIn
{
private:
	const int VerticalSpeedFactor = 200;

public:
	CESTagItems();
	virtual ~CESTagItems();

	void OnGetTagItem(CFlightPlan FlightPlan, CRadarTarget RadarTarget, int ItemCode, int TagData, char sItemString[16], int * pColorCode, COLORREF * pRGB, double * pFontSize);
	

private:
	void RegisterTagItems();

	void GetVerticalSpeed(const CRadarTarget & RadarTarget, char * result);
};

