#include "ESTagItems.h"

CESTagItems *pMyPlugIn = NULL;

void __declspec (dllexport) EuroScopePlugInInit(EuroScopePlugIn::CPlugIn **pPlugInInstance)
{
	*pPlugInInstance = pMyPlugIn = new CESTagItems;
}

void    __declspec (dllexport)    EuroScopePlugInExit(void)
{
	delete pMyPlugIn;
}