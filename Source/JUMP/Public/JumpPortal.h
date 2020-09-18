#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "JumpPortal.generated.h"

class AJumpCharacter;

UCLASS()
class JUMP_API AJumpPortal : public AActor
{
	GENERATED_BODY()

public:
	AJumpPortal(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	// Vars
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PortalVars")
		AJumpPortal* otherPortal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PortalVars")
		float maxRenderDistance = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PortalVars")
		float lowPriorityRenderDistance = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PortalVars")
		float lowPriorityUpdateTime = 0.1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PortalVars")
		bool isInitialized = false;

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Portal")
		void Update(AJumpCharacter* player, float dist, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Portal")
		void Init();

	UFUNCTION(BlueprintCallable, Category = "Portal")
		void SetActiveState(bool isActive);

	UFUNCTION(BlueprintCallable, Category = "Portal")
		FORCEINLINE bool GetActiveState() { return isPortalActive; }

	// Events
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PortalEvents")
		void OnUpdate();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PortalEvents")
		void OnBegin();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PortalEvents")
		void OnActiveStateChanged(bool isActive);

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USceneCaptureComponent2D* ThisCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USceneCaptureComponent2D* OtherCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UTextureRenderTarget2D* CameraRenderTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* TeleportLocationComponent;

private:
	bool isPortalActive = true;
	float lowPrioDelta = 0;

	UFUNCTION(Server, unreliable, WithValidation)
		void Server_AddPortal();
};
