// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class OptiTracking : ModuleRules
	{
        private string ModulePath
        {
            get { return ModuleDirectory; }
        }

        private string PluginPath
        {
            get { return System.IO.Path.GetFullPath(System.IO.Path.Combine(ModulePath, "../../ThirdParty/Tracking")); }
        }

        public OptiTracking(ReadOnlyTargetRules Target) : base(Target)
		{

            PublicIncludePaths.AddRange(
                new string[] {
					// ... add public include paths required here ...
                    "OptiTracking/Public"
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					// ... add other private include paths required here ...
                    "OptiTracking/Private"
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
                    "CoreUObject",
                    "Projects",
                    "Engine"
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);

            //string MathDir = "../../ThirdParty/MathLib";
			PublicDelayLoadDLLs.Add("torch_cuda.dll");
            PublicDelayLoadDLLs.Add("TrackingLib.dll");
		    PublicAdditionalLibraries.Add(System.IO.Path.Combine(PluginPath, "TrackingLib.lib"));
        }
	}
}
