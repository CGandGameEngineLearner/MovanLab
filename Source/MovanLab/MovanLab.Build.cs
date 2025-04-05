// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MovanLab : ModuleRules
{
	public MovanLab(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject", 
			"Engine",
			"InputCore",
			"EnhancedInput",
			"PhysicsCore",
		});
	}
}
