#pragma once


#include "ModuleManager.h"



class FCoordinateSystemExModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
