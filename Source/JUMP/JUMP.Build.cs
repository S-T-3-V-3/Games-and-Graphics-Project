// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class JUMP : ModuleRules
{
	public JUMP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "OnlineSubsystem", "OnlineSubsystemUtils" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
	}
}
