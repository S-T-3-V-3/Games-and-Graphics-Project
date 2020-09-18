// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JUMPFunctionLibrary.generated.h"

class AJumpCharacter;
class APlayerController;

UENUM(BlueprintType)
enum class EOnlineStatus : uint8
{
	eoLoggedIn = 0		UMETA(DisplayName = "Logged In"),
	eoNotLoggedIn = 1		UMETA(DisplayName = "Not Logged In"),
	eoLocal = 2		UMETA(DisplayName = "Local Player")
};

/**
 * 
 */
UCLASS()
class JUMP_API UJUMPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(Blueprintcallable, Category = "JUMP/Portals")
		static void RenderImmediately(USceneCaptureComponent2D* target);

	UFUNCTION(BlueprintCallable, Category = "JUMP/Portals", Meta = (WorldContext = "WorldContextObject"))
		static void ForceCameraUpdate(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "JUMP/Tools")
		static FVector ConvertLocationToActorSpace(FVector WorldLocation, AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "JUMP/Tools")
		static FRotator ConvertRotationToActorSpace(FRotator WorldRotation, AActor* Target);

	UFUNCTION(BlueprintPure, Category = "JUMP/Tools")
		static APlayerController* GetLocalPlayerController();

	UFUNCTION(BlueprintPure, Category = "JUMP/Tools")
		static AJumpCharacter* GetJumpCharacter();

	UFUNCTION(BlueprintCallable, Category = "JUMP/Steam")
		static EOnlineStatus GetOnlineStatus();

	UFUNCTION(BlueprintCallable, Category = "JUMP/Steam")
		static FString GetOnlineName();
};
