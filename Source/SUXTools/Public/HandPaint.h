// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LeftHand.h"
#include "Kismet/GameplayStatics.h"
#include "HandTracking/UxtHandTrackingFunctionLibrary.h"
#include "Components/LineBatchComponent.h"
#include "Math/Color.h"
#include "HandPaint.generated.h"

UCLASS()
class SUXTOOLS_API AHandPaint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandPaint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// OnRingTipTapped handler
	UFUNCTION()
	void PaintVisibility(FVector& TipPosition);

private:
	// Is enabled
	bool bIsEnabled;

	// Is first point
	bool bIsFirstPoint;

	// Index Tip position
	FVector IndexTipPosition;

	// Line batch component
	ULineBatchComponent* LineBatchComponent;

	// Last Draw Point
	FVector LastDrawPoint;

	// Last Draw Point
	FVector LeftLastDrawPoint;

	//Line color
	FLinearColor DefaultLineColor;
};
