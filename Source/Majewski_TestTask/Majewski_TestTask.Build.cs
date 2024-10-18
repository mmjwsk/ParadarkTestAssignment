// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Majewski_TestTask : ModuleRules
{
	public Majewski_TestTask(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
