// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JumpCharacterMovementComponent.h"
#include "JumpCharacter.generated.h"

class AJumpPortal;
class AJUMPGameMode;

UCLASS()
class JUMP_API AJumpCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJumpCharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "JUMP/Movement")
		FORCEINLINE class UJumpCharacterMovementComponent* GetJumpCharacterMovementComponent() const { return JumpCharacterMovementComponent; }

	UFUNCTION(BlueprintCallable)
		FMatrix GetCameraProjectionMatrix();

	UFUNCTION(BlueprintCallable)
		void Init();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category = "Portals")
		TArray<AJumpPortal*> portals;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UJumpCharacterMovementComponent* JumpCharacterMovementComponent;

	UFUNCTION(Server, unreliable, WithValidation)
		void Server_GetPortals();

	float currentDistance;
};
