// Copyright Serico Games

using UnrealBuildTool;
using System.Collections.Generic;

public class UdemyUltimateCourseTarget : TargetRules
{
	public UdemyUltimateCourseTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "UdemyUltimateCourse" } );
	}
}
