#pragma once
#include <Windows.h>
#include <sstream>
#include <iomanip>
#include "EuroScopePlugIn.h"

using namespace EuroScopePlugIn;

class CESTagItems :
	public EuroScopePlugIn::CPlugIn
{
private:
	int VerticalSpeedFactor = 200;
	int VerticalSpeedFactor2 = VerticalSpeedFactor / 2;

public:
	CESTagItems();
	virtual ~CESTagItems();

	void OnGetTagItem(CFlightPlan FlightPlan, CRadarTarget RadarTarget, int ItemCode, int TagData, char sItemString[16], int * pColorCode, COLORREF * pRGB, double * pFontSize);
	

private:
	void RegisterTagItems();

	void GetVerticalSpeed(const CRadarTarget & RadarTarget, char * result);
};

