// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Lesson4 : ModuleRules
{
	public Lesson4(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" ,"Json"});
	}
}
