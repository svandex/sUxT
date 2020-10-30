// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PushButton.h"
#include "Engine/StaticMeshActor.h"
#include "Input/UxtPointerComponent.h"
#include "Controls/UxtPressableButtonComponent.h"
#include "MeshChangeTest.generated.h"

/**
 * 
 */
UCLASS()
class SUXTOOLS_API AMeshChangeTest : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AMeshChangeTest();

	/** Overridable native event for when play begins for this actor. */
	virtual void BeginPlay();

	UFUNCTION()
	void ChangeOnTipTapped(FVector& TipPosition);

	UFUNCTION()
	void Change(UUxtPressableButtonComponent* Button, UUxtPointerComponent* Pointer);
	
private:
	UStaticMesh* PtrCube;
	UStaticMesh* PtrSphere;
	bool bChange; 
};
