// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ROBOTERRAbackstory : ModuleRules
{
	public ROBOTERRAbackstory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
