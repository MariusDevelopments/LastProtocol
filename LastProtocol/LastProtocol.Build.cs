// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LastProtocol : ModuleRules
{
	public LastProtocol(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"LastProtocol",
			"LastProtocol/Variant_Platforming",
			"LastProtocol/Variant_Platforming/Animation",
			"LastProtocol/Variant_Combat",
			"LastProtocol/Variant_Combat/AI",
			"LastProtocol/Variant_Combat/Animation",
			"LastProtocol/Variant_Combat/Gameplay",
			"LastProtocol/Variant_Combat/Interfaces",
			"LastProtocol/Variant_Combat/UI",
			"LastProtocol/Variant_SideScrolling",
			"LastProtocol/Variant_SideScrolling/AI",
			"LastProtocol/Variant_SideScrolling/Gameplay",
			"LastProtocol/Variant_SideScrolling/Interfaces",
			"LastProtocol/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
