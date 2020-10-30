// Fill out your copyright notice in the Description page of Project Settings.


#include "LeftHand.h"
#include "EngineUtils.h"
#include "ARSharedWorldPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Controls/UxtPressableButtonComponent.h"
#include "ARBlueprintLibrary.h"
#include "Engine/World.h"
#include "HandTracking/UxtHandTrackingFunctionLibrary.h"
#include "Utils/UxtFunctionLibrary.h"

ALeftHand::ALeftHand(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	// Add PalmUp Detection
	PalmUpConstraint=CreateDefaultSubobject<UUxtPalmUpConstraintComponent>("PalmUpConstraint");
	//AddOwnedComponent(PalmUpConstraint);
}

void ALeftHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if(bPalmUp&&AnglePalmUpToZAxis()<MaxPalmUpToZAngle)
	if(bPalmUp)
	{
		FVector MiddleTipPosition;
		FVector RingTipPosition;
		FVector LittleTipPosition;

		//Middle TipTap
		if(IsTwoTipTapped(EUxtHandJoint::MiddleTip, EUxtHandJoint::IndexTip, MiddleTipPosition))
		{
			bIsMiddleTipMenuActivated = true;
		}

		//Ring TipTap
		if(IsTwoTipTapped(EUxtHandJoint::RingTip, EUxtHandJoint::IndexTip, RingTipPosition))
		{
			bIsRingTipMenuActivated = true;
		}

		/*
		//Sometimes Middle TipTap is confused with Ring TipTap
		if(bIsMiddleTipMenuActivated&&bIsRingTipMenuActivated)
		{
			//SecondTip
			FQuat ThumbTipOrientation;
			FVector ThumbTipPosition;
			float ThumbTipJointRadius;

			if(UUxtHandTrackingFunctionLibrary::GetHandJointState(EControllerHand::Left, EUxtHandJoint::ThumbTip, ThumbTipOrientation, ThumbTipPosition, ThumbTipJointRadius))
			{
				float ThumbToMiddleTip = FVector::Distance(ThumbTipPosition, MiddleTipPosition);
				float ThumbToRingTip = FVector::Distance(ThumbTipPosition, RingTipPosition);

				if(ThumbToMiddleTip<ThumbToRingTip)
				{
					bIsRingTipMenuActivated = false;
				}
				else
				{
					bIsMiddleTipMenuActivated = false;
				}
			}
		}
		*/

		//Little TipTap
		if(IsTwoTipTapped(EUxtHandJoint::LittleTip, EUxtHandJoint::IndexTip, LittleTipPosition))
		{
			bIsLittleTipMenuActivated = true;
		}

		if(!bWasMiddleTipMenuActivated&&bIsMiddleTipMenuActivated)
		{
			OnMiddleTipTapped.Broadcast(MiddleTipPosition);
			UE_LOG(LogLeftHand, Log, TEXT("Middle Tip Activation!"));
		}

		if(!bWasRingTipMenuActivated&&bIsRingTipMenuActivated)
		{
			OnRingTipTapped.Broadcast(RingTipPosition);
			UE_LOG(LogLeftHand, Log, TEXT("Ring Tip Activation!"));
		}

		if(!bWasLittleTipMenuActivated&&bIsLittleTipMenuActivated)
		{
			OnLittleTipTapped.Broadcast(LittleTipPosition);
			UE_LOG(LogLeftHand, Log, TEXT("Little Tip Activation!"));
		}
	}

	//Next Tick
	bWasMiddleTipMenuActivated = bIsMiddleTipMenuActivated ;
	bIsMiddleTipMenuActivated = false;

	bWasRingTipMenuActivated = bIsRingTipMenuActivated ;
	bIsRingTipMenuActivated = false;

	bWasLittleTipMenuActivated = bIsLittleTipMenuActivated ;
	bIsLittleTipMenuActivated = false;
} 

void ALeftHand::BeginPlay()
{
	Super::BeginPlay();

	//Set delegate , when palm up is facing person, show hand menu
	PalmUpConstraint-> OnConstraintActivated.AddDynamic(this,&ALeftHand::IsPalmUpTrue);
	PalmUpConstraint-> OnConstraintDeactivated.AddDynamic(this,&ALeftHand::IsPalmUpFalse);
}

/*
 * When Left Hand Constraint is activated, show hand menu right up to palm-z diretion
 */
void ALeftHand::IsPalmUpTrue()
{
	bPalmUp = true;
//	UE_LOG(LogLeftHand,Log,TEXT("Show Hand Menu!"));
}

void ALeftHand::IsPalmUpFalse()
{
	bPalmUp=false;
//	UE_LOG(LogLeftHand,Log,TEXT("Hide Hand Menu!"));
}

bool ALeftHand::IsTwoTipTapped(EUxtHandJoint FirstTip, EUxtHandJoint SecondTip, FVector& TipPosition)
{
		//FirstTip in Left Hand
		FQuat FirstTipOrientation;
		FVector FirstTipPosition;
		float FirstTipJointRadius;

		//SecondTip in Right Hand
		FQuat SecondTipOrientation;
		FVector SecondTipPosition;
		float SecondTipJointRadius;

		if(
		UUxtHandTrackingFunctionLibrary::GetHandJointState(EControllerHand::Left, FirstTip, FirstTipOrientation, FirstTipPosition, FirstTipJointRadius)&&
		UUxtHandTrackingFunctionLibrary::GetHandJointState(EControllerHand::Right, SecondTip, SecondTipOrientation, SecondTipPosition, SecondTipJointRadius)&&
		//distance less then radius
		FVector::Distance(FirstTipPosition, SecondTipPosition)<MinTipDistance
		)
		{
			TipPosition = FirstTipPosition*0.5+SecondTipPosition*0.5;
			return true;
		}else
		{
			return false;
		}

}

DEFINE_LOG_CATEGORY(LogLeftHand);
