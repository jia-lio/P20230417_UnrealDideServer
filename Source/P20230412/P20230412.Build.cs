// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class P20230412 : ModuleRules
{
	public P20230412(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //20230417 HTTP 추가
        //20230419 Networking
        PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", "CoreUObject", "Engine", "InputCore", 
			"HeadMountedDisplay", "EnhancedInput", "HTTP",
            "Sockets", "Networking"

        });

	}
}
