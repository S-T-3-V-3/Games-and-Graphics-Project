

#include "JumpCharacter.h"
#include "JUMPGameMode.h"
#include "JumpPortal.h"
#include "SceneView.h"
#include "Engine/LocalPlayer.h"
#include "Net/UnrealNetwork.h"
#include "JUMPLog.h"

AJumpCharacter::AJumpCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UJumpCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
}

void AJumpCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AJumpCharacter::Init()
{
	Server_GetPortals();
}

void AJumpCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (&portals == nullptr) return;

	for (AJumpPortal* portal : portals)
	{
		if (portal != nullptr)
		{
			currentDistance = FVector::Dist(portal->GetActorLocation(), GetActorLocation());

			if (currentDistance < portal->maxRenderDistance)
			{
				portal->Update(this, currentDistance, DeltaTime);
			}
			else
			{
				if (portal->GetActiveState() != false)
					portal->SetActiveState(false);
			}
		}
	}
}

void AJumpCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AJumpCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	JumpCharacterMovementComponent = Cast<UJumpCharacterMovementComponent>(Super::GetMovementComponent());
}

FMatrix AJumpCharacter::GetCameraProjectionMatrix()
{
	FMatrix ProjectionMatrix;

	FSceneViewProjectionData PlayerProjectionData;

	ULocalPlayer* localPlayer = Cast<APlayerController>(GetController())->GetLocalPlayer();
	localPlayer->GetProjectionData(localPlayer->ViewportClient->Viewport,EStereoscopicPass::eSSP_FULL,PlayerProjectionData);
	ProjectionMatrix = PlayerProjectionData.ProjectionMatrix;

	return ProjectionMatrix;
}

void AJumpCharacter::Server_GetPortals_Implementation()
{
	for (AJumpPortal* p : GetWorld()->GetAuthGameMode<AJUMPGameMode>()->GetPortals()) {
		portals.AddUnique(p);
	}
}

bool AJumpCharacter::Server_GetPortals_Validate()
{
	return true;
}