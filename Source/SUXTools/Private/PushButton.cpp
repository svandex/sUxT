// Fill out your copyright notice in the Description page of Project Settings.
#include "PushButton.h"
#include "LeftHand.h"

// Sets default values
APushButton::APushButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	////////////
	//UxtPressableButtonComponent
	////////////
	UxtPressableButton=CreateDefaultSubobject<UUxtPressableButtonComponent>(TEXT("UxtPressableButton"));

	//Root Component
	SetRootComponent(UxtPressableButton);
	UxtPressableButton->SetRelativeLocation(FVector(0,0,20));
	UxtPressableButton->SetPushBehavior(EUxtPushBehavior::Compress);
	UxtPressableButton->SetMaxPushDistance(1.6);

	////////////
	//Front Plate
	////////////
	FrontPlate = CreateDefaultSubobject<USceneComponent>(TEXT("FrontPlate"));
	FrontPlate->SetupAttachment(RootComponent);
	FrontPlate->SetRelativeLocation(FVector(-1.6,0,0));
//	FrontPlate->SetRelativeRotation(FRotator(0,0,90));
	FrontPlate->SetRelativeScale3D(FVector(2.25,3.2,3.2));

	UxtPressableButton->SetVisuals(FrontPlate);

	////////////
	//FrontPlateStaticMesh
	////////////
	FrontPlateStaticMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontPlateStaticMesh"));
	FrontPlateStaticMesh->SetupAttachment(FrontPlate);
	//PressableButton->SetVisuals(FrontPlateStaticMesh);
	
	////////////
	//Label
	////////////
	Label=CreateDefaultSubobject<UTextRenderComponent>(TEXT("Label"));
	Label->SetupAttachment(FrontPlate);
	Label->SetText(FText::FromString(TEXT("PUSH")));
	Label->SetRelativeLocation(FVector(0.7f,0.0f,0.0f));
	Label->SetWorldSize(0.2f);
	Label->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Label->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);

	//set mesh and material
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FrontPlate(TEXT("StaticMesh'/UXTools/Models/SM_FrontPlate_PX.SM_FrontPlate_PX'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MI_FrontPlate(TEXT("MaterialInstanceConstant'/UXTools/Buttons/HoloLens2/MI_ButtonHoloLens2FrontPlate.MI_ButtonHoloLens2FrontPlate'"));
	if(SM_FrontPlate.Object&&MI_FrontPlate.Object)
	{
		FrontPlateStaticMesh->SetStaticMesh(SM_FrontPlate.Object);
		FrontPlateStaticMesh->SetMaterial(0,MI_FrontPlate.Object);

		//Transformation
		FrontPlateStaticMesh->SetRelativeLocation(FVector(0.8,0,0));
	}

	////////////
	//BackPlate
	////////////
	BackPlate=CreateDefaultSubobject<USceneComponent>(TEXT("BackPlate"));
	BackPlate->SetupAttachment(RootComponent);
	BackPlate->SetRelativeLocation(FVector(-1.6,0,0));
//	BackPlate->SetRelativeRotation(FRotator(0,0,90));

	////////////
	//UxtBackPlate
	////////////
	UxtBackPlate=CreateDefaultSubobject<UUxtBackPlateComponent>(TEXT("UxtBackPlate"));
	UxtBackPlate->SetupAttachment(BackPlate);

	//set mesh and material 
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BackPlate(TEXT("StaticMesh'/UXTools/Models/SM_BackPlateRoundedThick_4.SM_BackPlateRoundedThick_4'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MI_BackPlate(TEXT("MaterialInstanceConstant'/UXTools/Materials/MI_HoloLens2BackPlate.MI_HoloLens2BackPlate'"));
	if(SM_BackPlate.Object&&MI_BackPlate.Object)
	{
		UxtBackPlate->SetStaticMesh(SM_BackPlate.Object);
		UxtBackPlate->SetBackPlateMaterial(MI_BackPlate.Object);

		//Transformation
		UxtBackPlate->SetRelativeLocation(FVector(0.16,0,0));
		//UxtBackPlate->SetRelativeScale3D(FVector(3.2,3.2,1.6));
	}
}

// Called when the game starts or when spawned
void APushButton::BeginPlay()
{
	Super::BeginPlay();

	//Only one ALeftHand object exist
	Cast<ALeftHand>(UGameplayStatics::GetActorOfClass(GetWorld(), ALeftHand::StaticClass()))->OnMiddleTipTapped.AddUObject(this,&APushButton::ButtonVisibility);
}

// Called every frame
void APushButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

DEFINE_LOG_CATEGORY(LogPushButton);
