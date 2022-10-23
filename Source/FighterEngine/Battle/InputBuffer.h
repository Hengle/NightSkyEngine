﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "InputBuffer.generated.h"
#pragma pack (push, 1)

/**
 * 
 */
USTRUCT()
struct FInputBuffer
{
	GENERATED_BODY()
protected:
	int32 InputSequence[20] = { -1 };
	int32 Lenience = 10; //how much time is allowed between inputs
	int32 ImpreciseInputCount = 0; //how much time is allowed between inputs
public:
	int32 InputBufferInternal[90] = { 16 };
	bool InputDisabled[90] = { false };
	
	void Tick(int32 Input);
	bool CheckInputCondition(EInputCondition InputCondition);
	bool CheckInputSequence();
	bool CheckInputSequenceStrict(); //directional inputs must be exact
	bool CheckInputSequenceOnce();
	void ResetInputSequence();
	void FlipInputsInBuffer();
};
#pragma pack(pop)

