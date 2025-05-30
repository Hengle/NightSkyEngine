// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FighterLocalRunner.generated.h"

constexpr int AccumulatorBreakerMax = 3;

UCLASS()
class FIGHTERENGINE_API AFighterLocalRunner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFighterLocalRunner();

protected:
	virtual void BeginPlay() override;

public:	

	virtual void Update(float DeltaTime);
protected:
	float ElapsedTime=0;
	
	class AFighterGameState* FighterGameState;
};
