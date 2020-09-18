// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JumpCharacterMovementComponent.generated.h"

class AJumpCharacter;

/**
 * 
 */
UCLASS()
class JUMP_API UJumpCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "JUMP/Portal")
		void TeleportTo(const FTransform& newTransform, const FRotator& newCameraRotation, const FRotator& portalRotationDifference, AJumpCharacter* player);

	UFUNCTION(Unreliable, Server, WithValidation)
		void Server_DoTeleport(const FTransform& newTransform, const FVector& newVelocity, AJumpCharacter* player);
};
