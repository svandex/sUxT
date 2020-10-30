// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkbenchMapping.h"
#include "HoloLensARFunctionLibrary.h"

// Sets default values
AWorkbenchMapping::AWorkbenchMapping()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ARTrackableNotify=CreateDefaultSubobject<UARTrackableNotifyComponent>(TEXT("ARTrackableNotify"));
	AddOwnedComponent(ARTrackableNotify);

	bIsQRCodeDetected = false;

	bIsLittleTipTapped = false;
}

// Called when the game starts or when spawned
void AWorkbenchMapping::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogWorkbenchMapping, Log, TEXT("Workbench Mapping Created!"));	
	// Delegate
	ARTrackableNotify->OnAddTrackedImage.AddDynamic(this,&AWorkbenchMapping::DetectQR);
	ARTrackableNotify->OnUpdateTrackedImage.AddDynamic(this,&AWorkbenchMapping::CalculateQRCode);

	// Only one ALeftHand object exist
	Cast<ALeftHand>(UGameplayStatics::GetActorOfClass(GetWorld(), ALeftHand::StaticClass()))->OnLittleTipTapped.AddUObject(this,&AWorkbenchMapping::Mapping);
}

// Called every frame
void AWorkbenchMapping::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Connect to Robot
bool AWorkbenchMapping::ConnectToRobot()
{
	return true;
}

// Detect QR Code
void AWorkbenchMapping::DetectQR(UARTrackedImage* TrackedImage)
{
	UE_LOG(LogWorkbenchMapping, Log, TEXT("Image Detected!"));	
}

void AWorkbenchMapping::CalculateQRCode(UARTrackedImage* TrackedImage)
{
	UARTrackedQRCode* TrackedQR = Cast<UARTrackedQRCode>(TrackedImage);

	if(TrackedQR->Version)
	{
		bIsQRCodeDetected = true;
		UE_LOG(LogWorkbenchMapping, Log, TEXT("QR Code string is %s."), *(TrackedQR->QRCode));	

		/*
		UHoloLensARFunctionLibrary::StopCameraCapture();
		UARBlueprintLibrary::StopARSession();
		bIsLittleTipTapped = false;
		*/
	}
}

void AWorkbenchMapping::Mapping(FVector& TipPosition)
{
	bIsLittleTipTapped = !bIsLittleTipTapped;
	UE_LOG(LogWorkbenchMapping, Log, TEXT("bool value is %d."), bIsLittleTipTapped);	


	if(bIsLittleTipTapped && ConnectToRobot())
	{
		try
		{
			// Start detecting QR Code
			UARBlueprintLibrary::StartARSession(UARBlueprintLibrary::GetSessionConfig());

			UE_LOG(LogWorkbenchMapping, Log, TEXT("Start Camera Capture."));

			UHoloLensARFunctionLibrary::StartCameraCapture();

			UE_LOG(LogWorkbenchMapping, Log, TEXT("Camera Capture Started."));

			//UHoloLensARFunctionLibrary::SetEnabledMixedRealityCamera(true);
			/*
			// 30 seconds for detecting
			if(bIsQRCodeDetected)
			{

			}else{
			//Show a window that tells no QR Code detected

			// Stop detecting
			}
			*/
		}
		catch (std::exception& e)
		{
			UE_LOG(LogWorkbenchMapping, Log, TEXT("Exception: %s"), e.what());
		}
 }else
	{
		UE_LOG(LogWorkbenchMapping, Log, TEXT("Close Camera!"));	
		bIsQRCodeDetected = false;
		UHoloLensARFunctionLibrary::StopCameraCapture();
		UARBlueprintLibrary::StopARSession();
	}
}

DEFINE_LOG_CATEGORY(LogWorkbenchMapping);
