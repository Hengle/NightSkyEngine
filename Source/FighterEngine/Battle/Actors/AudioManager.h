﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"

constexpr int CommonAudioChannelCount = 50;
constexpr int CharaAudioChannelCount = 50;
constexpr int CharaVoiceChannelCount = 6;

class UAudioComponent;

UCLASS()
class FIGHTERENGINE_API AAudioManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAudioManager();

	UPROPERTY()
	UAudioComponent* CommonAudioPlayers[CommonAudioChannelCount];
	UPROPERTY()
	UAudioComponent* CharaAudioPlayers[CharaAudioChannelCount];
	UPROPERTY()
	UAudioComponent* CharaVoicePlayers[CharaVoiceChannelCount];
	UPROPERTY()
	UAudioComponent* AnnouncerVoicePlayer;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PauseAllAudio();
};
