// Fill out your copyright notice in the Description page of Project Settings.


#include "HandPaint.h"

// Sets default values
AHandPaint::AHandPaint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LineBatchComponent = CreateDefaultSubobject<ULineBatchComponent>(TEXT("LineBatch"));
	SetRootComponent(LineBatchComponent);
	LineBatchComponent->DefaultLifeTime = 2.0f;

	//DefaultLineColor = FLinearColor(138,43,226,1.0f);
	DefaultLineColor = FLinearColor(0,255,255,0.5f);
	bIsEnabled = false;
	bIsFirstPoint = true;
}

// Called when the game starts or when spawned
void AHandPaint::BeginPlay()
{
	Super::BeginPlay();
	
	//Only one ALeftHand object exist
	Cast<ALeftHand>(UGameplayStatics::GetActorOfClass(GetWorld(), ALeftHand::StaticClass()))->OnRingTipTapped.AddUObject(this,&AHandPaint::PaintVisibility);
}

// Called every frame
void AHandPaint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Index Tip Position Update
	FQuat IndexTipOrientation;
	float IndexTipJointRadius;
	
	//
	FVector LeftTipPosition;

	if(bIsEnabled
			&&
		UUxtHandTrackingFunctionLibrary::GetHandJointState(EControllerHand::Right, EUxtHandJoint::IndexTip, IndexTipOrientation, IndexTipPosition, IndexTipJointRadius)
		&&
		UUxtHandTrackingFunctionLibrary::GetHandJointState(EControllerHand::Left, EUxtHandJoint::IndexTip, IndexTipOrientation, LeftTipPosition, IndexTipJointRadius)
			)
	{
		if(!bIsFirstPoint)
		{
//			LineBatchComponent->DrawPoint(IndexTipPosition,DefaultLineColor, 2.0f,1,1.0f);
			LineBatchComponent->DrawLine(IndexTipPosition, LastDrawPoint, DefaultLineColor, 1, 0.5f,10.0f);
			LineBatchComponent->DrawLine(LeftTipPosition, LeftLastDrawPoint, DefaultLineColor, 1, 0.5f,10.0f);
		}else
		{
			bIsFirstPoint =false;
		}

		LastDrawPoint = IndexTipPosition;
		LeftLastDrawPoint = LeftTipPosition;
	}else
	{
		// If Lost hand tracking then restart drawing
		bIsFirstPoint = true;	
	}
}


void AHandPaint::PaintVisibility(FVector&)
{
	bIsEnabled=!bIsEnabled;
	if(!bIsEnabled)
	{
		bIsFirstPoint = true;
	}
}

