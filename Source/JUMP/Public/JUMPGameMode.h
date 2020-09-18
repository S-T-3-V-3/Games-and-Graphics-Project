// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "JUMPGameMode.generated.h"

class AJumpPortal;

/**
 * 
 */
UCLASS()
class JUMP_API AJUMPGameMode : public AGameMode
{
	GENERATED_BODY()

	AJUMPGameMode(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable, Category = "JUMP/Portal")
		void AddPortal(AJumpPortal* currentPortal);

	UFUNCTION(BlueprintCallable, Category = "JUMP/Portal")
		void RemovePortal(AJumpPortal* currentPortal);

	UFUNCTION(BlueprintCallable, Category = "JUMP/Portal")
		TArray<AJumpPortal*> GetPortals();

	UPROPERTY(VisibleAnywhere)
	TArray<AJumpPortal*> portals;
};