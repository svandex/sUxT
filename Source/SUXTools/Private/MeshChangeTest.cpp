// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshChangeTest.h"
#include "EngineUtils.h"

AMeshChangeTest::AMeshChangeTest()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Cube(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if(SM_Sphere.Object&&SM_Cube.Object)
	{
		PtrCube=SM_Cube.Object;
		PtrSphere=SM_Sphere.Object;
	}

	GetStaticMeshComponent()-> SetStaticMesh(PtrCube);
	bChange = false;
}


void AMeshChangeTest::BeginPlay()
{
	//Delegate setting
	for(TActorIterator<APushButton> ActorItr(GetWorld());ActorItr;++ActorItr)
	{
		if(ActorItr->GetName().Contains("PushButton"))
		{
			(*ActorItr)->UxtPressableButton->OnButtonPressed.AddDynamic(this,&AMeshChangeTest::Change);
			//(*ActorItr)->UxtPressableButton->OnButtonReleased.AddDynamic(this,&AMeshChangeTest::Change);

			// Only one ALeftHand object exist
			Cast<ALeftHand>(UGameplayStatics::GetActorOfClass(GetWorld(), ALeftHand::StaticClass()))->OnLittleTipTapped.AddUObject(this, &AMeshChangeTest::ChangeOnTipTapped);
		}
	}
}


void AMeshChangeTest::Change(UUxtPressableButtonComponent* Button, UUxtPointerComponent* Pointer)
{
	bChange = !bChange;

	// Change Mesh
	if(!bChange)
	{
		GetStaticMeshComponent()-> SetStaticMesh(PtrCube);
	}
	else
	{
		GetStaticMeshComponent()-> SetStaticMesh(PtrSphere);
	}
}

void AMeshChangeTest::ChangeOnTipTapped(FVector& TipPosition)
{
	bChange = !bChange;

	// Change Mesh
	if(!bChange)
	{
		GetStaticMeshComponent()-> SetStaticMesh(PtrCube);
	}
	else
	{
		GetStaticMeshComponent()-> SetStaticMesh(PtrSphere);
	}
}
