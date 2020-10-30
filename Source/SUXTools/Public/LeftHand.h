// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HoloLensARSystem.h"
#include "GameFramework/Actor.h"
#include "Input/UxtHandInteractionActor.h"
#include "Behaviors/UxtPalmUpConstraintComponent.h"
#include "HandTracking/UxtHandTrackingFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "LeftHand.generated.h"

/*
 * Delegate for tip-tap action
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMiddleTipTapped, FVector&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRingTipTapped, FVector&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLittleTipTapped, FVector&);

/**
 * Hand Interaction Actor with debug features
 *
 * Temporarily used for testing
 */
UCLASS()
class SUXTOOLS_API ALeftHand : public AUxtHandInteractionActor
{
	GENERATED_BODY()
public:
	ALeftHand(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tip Tap", meta = (ClampMin = "0.0", ClampMax = "5.0"))
	float MinTipDistance= 3.5f;

	//delegates
	FOnMiddleTipTapped OnMiddleTipTapped;
	FOnRingTipTapped OnRingTipTapped;
	FOnLittleTipTapped OnLittleTipTapped;

private:
	//PalmUp Component
	UPROPERTY(VisibleAnywhere)
	UUxtPalmUpConstraintComponent* PalmUpConstraint;

	//Used as delegate handler
	UFUNCTION()
	void IsPalmUpTrue();

	UFUNCTION()
	void IsPalmUpFalse();

	//If Two Tips Taped together
	bool IsTwoTipTapped(EUxtHandJoint FirstTipOnLeftHand, EUxtHandJoint SecondTipOnRightHand, FVector& TipPosition);

private:
	//Hand Menu Postion and Rotation
	FVector HandMenuPosition;
	FRotator HandMenuRotation;

	//each tick boolean
	bool bIsMiddleTipMenuActivated = false;
	bool bWasMiddleTipMenuActivated = false;
	bool bIsRingTipMenuActivated = false;
	bool bWasRingTipMenuActivated = false;
	bool bIsLittleTipMenuActivated = false;
	bool bWasLittleTipMenuActivated = false;

	bool bPalmUp = false;
};

DECLARE_LOG_CATEGORY_EXTERN(LogLeftHand,Log,All);
