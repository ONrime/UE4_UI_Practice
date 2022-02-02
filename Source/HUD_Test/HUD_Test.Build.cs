// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HUD_Test : ModuleRules
{
	public HUD_Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });

		// Public, Private 경로 설정
		PrivateIncludePaths.Add("HUD_Test/Private");
		PublicIncludePaths.Add("HUD_Test/Public");
	}
}
