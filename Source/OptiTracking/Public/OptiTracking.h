#pragma once

#include "IOptiTracking.h"
#include "iue_interface.h"

typedef iue_interface* (*iue_interface_factory)();

class OptiTrackingImpl : public IOptiTracking
{
public:
	/** IModuleInterface implementation */
	void StartupModule();
	void ShutdownModule();

	bool IsThisNumber42(int32 num);
	int32 GetNumber();
	void SetNumber(int32 num);
	void add();
	iue_interface* GetTestClass();

	int32 testNumber;

private:
	void* m_dllHandle;
	void* m_dllHandleTorch;
	iue_interface_factory factory_func;
};