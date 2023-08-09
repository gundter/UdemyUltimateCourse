// Copyright Serico Games

using UnrealBuildTool;
using System.Collections.Generic;

public class UdemyUltimateCourseEditorTarget : TargetRules
{
	public UdemyUltimateCourseEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "UdemyUltimateCourse" } );
	}
}
