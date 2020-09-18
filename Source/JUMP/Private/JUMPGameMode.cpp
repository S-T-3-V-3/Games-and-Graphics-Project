// Fill out your copyright notice in the Description page of Project Settings.


#include "JUMPGameMode.h"
#include "JumpPortal.h"

AJUMPGameMode::AJUMPGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AJUMPGameMode::AddPortal(AJumpPortal* currentPortal)
{
	portals.AddUnique(currentPortal);
}

void AJUMPGameMode::RemovePortal(AJumpPortal* currentPortal)
{
	portals.Remove(currentPortal);
}

TArray<AJumpPortal*> AJUMPGameMode::GetPortals()
{
	return portals;
}
