// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditorLibrary.h"

#include "LukasHelperLibrary.generated.h"

/**
 *  Lukas Helper Library
 */
UCLASS(meta=(ScriptName="LukasHelperLibrary"))
class LUKASHELPERMODULEEDITOR_API ULukasHelperLibrary : public UBlueprintEditorLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="LukasLibrary|Test")
	static void TestHelperPrint(USkeletalMesh* InSkeletalMesh);

	UFUNCTION(BlueprintCallable, Category="LukasLibrary|Test")
	static void GetAllActorDescriptorsInWorld(FName TargetClass, bool bAutoEnableDataLayers);
	
};
