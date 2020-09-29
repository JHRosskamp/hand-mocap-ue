// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "OptiTracking.h"
#include "IPluginManager.h"
#include "Modules/ModuleManager.h"
#include "Paths.h"
#include "IOptiTracking.h"
#include "PlatformProcess.h"
#include "MessageDialog.h"

#define LOCTEXT_NAMESPACE "OptiTracking"

//typedef IKlass* (*iklass_factory)();

void OptiTrackingImpl::StartupModule()
{

	//Get Base Directory
	FString BaseDir = IPluginManager::Get().FindPlugin("OptiTracking")->GetBaseDir();
	//UE_LOG(LogTemp, Warning, TEXT("Base Directory: %s"), *BaseDir);
	FString LibraryPath;
	FString LibraryPathTorch;
	//FString MathDir = "ThirdParty/MathLib";
	//LibraryPath = FPaths::Combine(*BaseDir, *MathDir, TEXT("MathLibrary.dll"));
	//UE_LOG(LogTemp, Warning, TEXT("Directory: %s"), *LibraryPath);
	FString MathDir = "ThirdParty/Tracking";
	LibraryPath = FPaths::Combine(*BaseDir, *MathDir, TEXT("TrackingLib.dll"));
	LibraryPathTorch = FPaths::Combine(*BaseDir, *MathDir, TEXT("torch_cuda.dll"));
	m_dllHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (!m_dllHandle)
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("OptiTracking", "Failed to load DLL Tracking in OptiTracking"));

	m_dllHandleTorch = !LibraryPathTorch.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPathTorch) : nullptr;

	if (!m_dllHandleTorch)
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("OptiTracking", "Failed to load DLL torch_cuda in OptiTracking"));

	factory_func = reinterpret_cast<iue_interface_factory>(FPlatformProcess::GetDllExport(m_dllHandle, TEXT("createTrackingObject")));
	if (!factory_func) {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("OptiTracking", "Failed to load create_tracking function"));
	}
	//ICalibration* instance = factory_func();
	//int32 data = instance->do_stuff(3);
	//UE_LOG(LogTemp, Warning, TEXT("Data value: %d"), data);
	//instance->Destroy();
}

void OptiTrackingImpl::ShutdownModule()
{
	// Free the dll handle
	FPlatformProcess::FreeDllHandle(m_dllHandle);
	m_dllHandle = nullptr;
}

bool OptiTrackingImpl::IsThisNumber42(int32 num)
{
	return num == 42;
}

iue_interface* OptiTrackingImpl::GetTestClass()
{
	return factory_func();
}

int32 OptiTrackingImpl::GetNumber()
{
	add();
	return testNumber;
}

void OptiTrackingImpl::SetNumber(int32 num)
{
	testNumber = num;
}

void OptiTrackingImpl::add()
{
	testNumber += 3;//;GetInt();
}

IMPLEMENT_MODULE(OptiTrackingImpl, OptiTracking)



