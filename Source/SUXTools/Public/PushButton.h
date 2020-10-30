// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonBase.h"
//#include "MeshChangeTest.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/StaticMeshActor.h"
#include "Controls/UxtPressableButtonComponent.h"
#include "Controls/UxtBackPlateComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ARSharedWorldGameMode.h"
#include "EngineUtils.h"
#include "Math/Vector.h"
#include "Input/UxtPointerComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Kismet/GameplayStatics.h"
#include "PushButton.generated.h"

UCLASS()
class SUXTOOLS_API APushButton : public AButtonBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APushButton();

	//Front Plate
	UPROPERTY(VisibleAnywhere)
	USceneComponent* FrontPlate;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FrontPlateStaticMesh;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* Label;

	//Back Plate
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BackPlate;

	UPROPERTY(VisibleAnywhere)
	UUxtBackPlateComponent* UxtBackPlate;

	UPROPERTY(VisibleAnywhere)
	UUxtPressableButtonComponent* UxtPressableButton;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

DECLARE_LOG_CATEGORY_EXTERN(LogPushButton,Log,All);
