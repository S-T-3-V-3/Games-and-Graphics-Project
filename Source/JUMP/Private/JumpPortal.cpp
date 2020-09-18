#include "JumpPortal.h"
#include "JUMPFunctionLibrary.h"
#include "GameFramework/PlayerController.h"
#include "UObject/UObjectIterator.h"
#include "JumpCharacter.h"
#include "Camera/CameraComponent.h"
#include "JUMPGameMode.h"
#include "Engine/World.h"
#include "JUMPLog.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AJumpPortal::AJumpPortal(const FObjectInitializer& ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = false;
}

void AJumpPortal::BeginPlay()
{
    OnBegin();
}

void AJumpPortal::Update(AJumpCharacter* player, float dist, float DeltaTime)
{
    if (otherPortal != nullptr)
    {
        if (isPortalActive != true)
            SetActiveState(true);

        lowPrioDelta = 0;
        OnUpdate();
        OtherCamera->CaptureScene();
    }
}

void AJumpPortal::Init()
{
    ThisCamera->bCaptureEveryFrame = false;
    ThisCamera->bCaptureOnMovement = false;
    ThisCamera->LODDistanceFactor = 3; //Force bigger LODs for faster computations
    ThisCamera->bEnableClipPlane = true;
    ThisCamera->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;

    //Setup Post-Process of SceneCapture
    FPostProcessSettings CaptureSettings;

    CaptureSettings.bOverride_AmbientOcclusionQuality = true;
    CaptureSettings.bOverride_MotionBlurAmount = true;
    CaptureSettings.bOverride_SceneFringeIntensity = true;
    CaptureSettings.bOverride_GrainIntensity = true;
    CaptureSettings.bOverride_ScreenSpaceReflectionQuality = true;

    CaptureSettings.AmbientOcclusionQuality = 0.0f; //0=lowest quality..100=maximum quality
    CaptureSettings.MotionBlurAmount = 0.0f; //0 = disabled
    CaptureSettings.SceneFringeIntensity = 0.0f; //0 = disabled
    CaptureSettings.GrainIntensity = 0.0f; //0 = disabled
    CaptureSettings.ScreenSpaceReflectionQuality = 0.0f; //0 = disabled

    CaptureSettings.bOverride_ScreenPercentage = true;
    CaptureSettings.ScreenPercentage = 100.0f;
    ThisCamera->PostProcessSettings = CaptureSettings;

    Server_AddPortal();
}

void AJumpPortal::SetActiveState(bool isActive)
{
    isPortalActive = isActive;
    OnActiveStateChanged(isActive);
}

void AJumpPortal::OnUpdate_Implementation()
{

}

void AJumpPortal::OnBegin_Implementation()
{

}

void AJumpPortal::OnActiveStateChanged_Implementation(bool isActive)
{

}

void AJumpPortal::Server_AddPortal_Implementation() {
    GetWorld()->GetAuthGameMode<AJUMPGameMode>()->AddPortal(this);
}

bool AJumpPortal::Server_AddPortal_Validate() {
    return true;
}