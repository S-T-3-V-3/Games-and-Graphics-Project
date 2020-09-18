// Fill out your copyright notice in the Description page of Project Settings.

#include "JumpCharacterMovementComponent.h"
#include "JumpCharacter.h"
#include "GameFramework/Controller.h"

void UJumpCharacterMovementComponent::TeleportTo(const FTransform& newTransform, const FRotator& newCameraRotation, const FRotator& portalRotationDifference, AJumpCharacter* player)
{
	FVector newVelocity = portalRotationDifference.RotateVector(Velocity);

	player->SetActorTransform(newTransform, false, NULL, ETeleportType::None);
	Velocity = newVelocity;

	player->GetController()->SetControlRotation(newCameraRotation);

	Server_DoTeleport(newTransform, newVelocity, player);
}

bool UJumpCharacterMovementComponent::Server_DoTeleport_Validate(const FTransform& newTransform, const FVector& newVelocity, AJumpCharacter* player)
{
	return true;
}

void UJumpCharacterMovementComponent::Server_DoTeleport_Implementation(const FTransform& newTransform, const FVector& newVelocity, AJumpCharacter* player)
{
	player->SetActorTransform(newTransform, false, NULL, ETeleportType::None);
	Velocity = newVelocity;
}