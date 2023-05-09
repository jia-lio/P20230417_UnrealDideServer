// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class P20230412 : ModuleRules
{
	public P20230412(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //20230417 HTTP
        //20230419 Networking
        //20230424 UMG
        //20230504 Add Plugins, Voice
        PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", "CoreUObject", "Engine", "InputCore", 
			"HeadMountedDisplay", "EnhancedInput", "HTTP",
            "Sockets", "Networking", "UMG" , "Json","JsonUtilities"
            ,"UniversalVoiceChatPro", "Voice"
        });

        //20230424
        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "Slate", "SlateCore"
        });

        
        
    }
}
