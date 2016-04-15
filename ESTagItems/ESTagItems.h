#pragma once
#include <Windows.h>
#include "EuroScopePlugIn.h"

using namespace EuroScopePlugIn;

class CESTagItems :
	public EuroScopePlugIn::CPlugIn
{
public:
	CESTagItems();
	virtual ~CESTagItems();

	void OnGetTagItem(CFlightPlan FlightPlan, CRadarTarget RadarTarget, int ItemCode, int TagData, char sItemString[16], int * pColorCode, COLORREF * pRGB, double * pFontSize);

private:
	void RegisterTagItems();

	void GetVerticalSpeed(CRadarTarget & RadarTarget, char * result);
};

