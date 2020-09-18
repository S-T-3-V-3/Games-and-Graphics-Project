// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JUMPGameInstance.generated.h"

class AJUMPGameMode;

/**
 * 
 */
UCLASS()
class JUMP_API UJUMPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UJUMPGameInstance(const FObjectInitializer& ObjectInitializer);

};
