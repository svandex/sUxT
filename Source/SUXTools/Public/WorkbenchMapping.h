// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "LeftHand.h"
#include "EyeTrackerFunctionLibrary.h"
#include "EngineUtils.h"
#include "ARBlueprintLibrary.h"
#include "ARTrackableNotifyComponent.h"
#include "Common/UdpSocketReceiver.h"
#include "WorkbenchMapping.generated.h"

UCLASS()
class SUXTOOLS_API AWorkbenchMapping : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorkbenchMapping();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Delegate handler
	void Mapping(FVector& TipPosition);

private:
	// Connect to Robot
	bool ConnectToRobot();

	UFUNCTION()
	void CalculateQRCode(UARTrackedImage* TrackedImage);
	// Detect QR Code
	UFUNCTION()
	void DetectQR(UARTrackedImage* TrackedImage);

private:
	// Component for tracking geometry
	UARTrackableNotifyComponent* ARTrackableNotify;

	// Udp communication to robot
	FUdpSocketReceiver *UdpSocket;

	// Is connected to Robot
	bool bIsConnectedToRobot;

	// Is QR Code Detected
	bool bIsQRCodeDetected;

	// Is Little Tip Tapped
	bool bIsLittleTipTapped;

};

DECLARE_LOG_CATEGORY_EXTERN(LogWorkbenchMapping,Log,All);
