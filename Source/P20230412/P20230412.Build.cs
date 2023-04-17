// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class P20230412 : ModuleRules
{
	public P20230412(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //20230417 Sockets Networking 추가
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "HTTP" });
	}
}
