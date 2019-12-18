// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class PublishingBP : ModuleRules
{
    private string ModulePath
    {
        get
        { 
            return ModuleDirectory;
        }
    }
    public PublishingBP(ReadOnlyTargetRules Target) : base(Target)
    {			
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
				"Sockets",
                "ROSIntegration",
				"Networking"
                // ... add other public dependencies that you statically link with here ...
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Sockets",
                "ROSIntegration",
				"Networking"
                // ... add private dependencies that you statically link with here ...	
            }
        );

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
    }
}
