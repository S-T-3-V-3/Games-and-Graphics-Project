// Fill out your copyright notice in the Description page of Project Settings.


#include "JUMPFunctionLibrary.h"
#include "Engine/World.h"
#include "UObject/UObjectIterator.h"
#include "JumpCharacter.h"
#include "Online.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Player.h"
#include "Components/ActorComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Camera/PlayerCameraManager.h"

void UJUMPFunctionLibrary::RenderImmediately(USceneCaptureComponent2D* target)
{
	target->CaptureScene();
}

void UJUMPFunctionLibrary::ForceCameraUpdate(const UObject* WorldContextObject)
{
	APlayerController* pc = WorldContextObject->GetWorld()->GetFirstPlayerController();
	pc->PlayerCameraManager->UpdateComponentTransforms();
	pc->PlayerCameraManager->UpdateCamera(WorldContextObject->GetWorld()->GetDeltaSeconds());
	pc->PlayerCameraManager->bGameCameraCutThisFrame = true;
}

FVector UJUMPFunctionLibrary::ConvertLocationToActorSpace(FVector Location, AActor* Target)
{
    if (Target == nullptr)
    {
        return FVector::ZeroVector;
    }

    FVector Direction = Location - FVector::ZeroVector;
    FVector TargetLocation = Target->GetActorLocation();

    FVector Dots;
    Dots.X = FVector::DotProduct(Direction, FVector::ForwardVector);
    Dots.Y = FVector::DotProduct(Direction, FVector::RightVector);
    Dots.Z = FVector::DotProduct(Direction, FVector::UpVector);

    FVector NewDirection = Dots.X * Target->GetActorForwardVector()
        + Dots.Y * Target->GetActorRightVector()
        + Dots.Z * Target->GetActorUpVector();

    return TargetLocation + NewDirection;
}

FRotator UJUMPFunctionLibrary::ConvertRotationToActorSpace(FRotator Rotation, AActor* Target)
{
    if (Target == nullptr)
    {
        return FRotator::ZeroRotator;
    }

    FTransform TargetTransform = Target->GetActorTransform();
    FQuat QuatRotation = FQuat(Rotation);

    FQuat LocalQuat = QuatRotation;
    FQuat NewWorldQuat = TargetTransform.GetRotation() * LocalQuat;

    return NewWorldQuat.Rotator();
}

APlayerController* UJUMPFunctionLibrary::GetLocalPlayerController()
{
    TObjectIterator<APlayerController> pc;
    if (!pc) return nullptr;
    return *pc;
}

AJumpCharacter* UJUMPFunctionLibrary::GetJumpCharacter()
{
    APlayerController* pc = GetLocalPlayerController();
    if (pc == nullptr)
        return nullptr;

    APawn* localPawn = pc->GetPawn();
    if (localPawn == nullptr)
        return nullptr;

    return Cast<AJumpCharacter>(localPawn);
}

EOnlineStatus UJUMPFunctionLibrary::GetOnlineStatus()
{
    IOnlineSubsystem* ion = IOnlineSubsystem::Get();

    if (ion == nullptr)
    {
        return EOnlineStatus::eoNotLoggedIn;
    }

    ELoginStatus::Type l = ion->GetIdentityInterface()->GetLoginStatus(0);

    if (l == ELoginStatus::Type::LoggedIn)
        return EOnlineStatus::eoLoggedIn;
    else if (l == ELoginStatus::Type::NotLoggedIn)
        return EOnlineStatus::eoNotLoggedIn;
    else if (l == ELoginStatus::Type::UsingLocalProfile)
        return EOnlineStatus::eoLocal;

    return EOnlineStatus::eoNotLoggedIn;
}

FString UJUMPFunctionLibrary::GetOnlineName()
{
    IOnlineSubsystem* ion = IOnlineSubsystem::Get();

    if (ion == nullptr)
    {
        return FString("");
    }

    return ion->GetIdentityInterface()->GetPlayerNickname(0);
}

