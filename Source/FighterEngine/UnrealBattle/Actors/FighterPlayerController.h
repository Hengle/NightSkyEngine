// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputDevice.h"
#include "FighterPlayerController.generated.h"

class ANetworkPawn;

class UnrealInputDevice : public InputDevice
{
public:
	int32 Inputs = 0;
	virtual int GetInputs() override
	{
		return Inputs;	
	}
};

/**
 * 
 */
UCLASS()
class FIGHTERENGINE_API AFighterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AFighterPlayerController();
	
	TSharedPtr<UnrealInputDevice> CurInputDevice;
	
	void TrySettingFighterCameraToViewport();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupInputComponent() override;
	
	int Inputs;
	int Frame;

	void PressUp();
	void ReleaseUp();
	void PressDown();
	void ReleaseDown();
	void PressLeft();
	void ReleaseLeft();
	void PressRight();
	void ReleaseRight();
	void PressL();
	void ReleaseL();
	void PressM();
	void ReleaseM();
	void PressH();
	void ReleaseH();
	void PressS();
	void ReleaseS();

	void UpdateInput();
	void SendGgpo(ANetworkPawn* InNetworkPawn, bool Client);
	
	UFUNCTION(BlueprintCallable)
	void SendCharaData();

	UPROPERTY(BlueprintReadOnly)
	ANetworkPawn* NetworkPawn;
	ACameraActor* CurrentView=nullptr;
};	

