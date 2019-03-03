// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class EscapeRoom_udemy02EditorTarget : TargetRules
{
	public EscapeRoom_udemy02EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "EscapeRoom_udemy02" } );
	}
}
