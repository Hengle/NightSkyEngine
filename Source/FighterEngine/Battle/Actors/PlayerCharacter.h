// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleActor.h"
#include "FighterEngine/Battle/InputBuffer.h"
#include "FighterEngine/Battle/NightSkyBinary.h"
#include "FighterEngine/DataAssets/SequenceData.h"
#include "FighterEngine/DataAssets/SoundData.h"
#include "FighterEngine/DataAssets/StateDataAsset.h"
#include "FighterEngine/DataAssets/ParticleData.h"
#include "FighterEngine/DataAssets/LinkMeshData.h"
#include "FighterEngine/Battle/StateMachine.h"
#include "FighterEngine/Battle/Subroutine.h"
#include "FighterEngine/Battle/ScriptAnalyzer.h"
#include "FighterEngine/DataAssets/SubroutineData.h"
#include "PlayerCharacter.generated.h"
#pragma pack (push, 1)

constexpr int CancelArraySize = 50;
constexpr int MaxComponentCount = 80;

UENUM()
enum EPlayerStats //player stats list
{
	PLY_FWalkSpeed,
	PLY_BWalkSpeed,
	PLY_FDashInitSpeed,
	PLY_FDashAccel,
	PLY_FDashMaxSpeed,
	PLY_FDashFriction,
	PLY_BDashSpeed,
	PLY_BDashHeight,
	PLY_BDashGravity,
	PLY_JumpHeight,
	PLY_FJumpSpeed,
	PLY_BJumpSpeed,
	PLY_JumpGravity,
	PLY_SuperJumpHeight,
	PLY_FSuperJumpSpeed,
	PLY_BSuperJumpSpeed,
	PLY_SuperJumpGravity,
	PLY_FAirDashSpeed,
	PLY_BAirDashSpeed,
};

USTRUCT()
struct FSavedInputCondition
{
	GENERATED_BODY()
	
	FInputBitmask Sequence[32];
	int Lenience = 8;
	int ImpreciseInputCount = 0;
	bool bInputAllowDisable = true;
	EInputMethod Method = EInputMethod::Normal;
};

/**
 * 
 */
UCLASS()
class FIGHTERENGINE_API APlayerCharacter : public ABattleActor
{
	GENERATED_BODY()
public:
	APlayerCharacter();

	//starting from this until PlayerSyncEnd, everything is saved/loaded for rollback
	unsigned char PlayerSync;
	int32 EnableFlags;
	int32 CurrentHealth;
protected:
	//internal variables	
	int32 CurrentAirJumpCount;
	int32 CurrentAirDashCount;
	int32 AirDashTimerMax;
	int32 UltraFactor;
	int32 ThrowRange;
	uint32 CancelFlags;
	
public:
	FWallBounceEffect WallBounceEffect;
	FGroundBounceEffect GroundBounceEffect;
	uint32 PlayerFlags;
	UPROPERTY(BlueprintReadWrite)
	bool FlipInputs;
	int32 TeamIndex;
	int32 Inputs;
	int32 ActionFlags;
	int32 AirDashTimer;
	int32 AirDashNoAttackTime;
	UPROPERTY(BlueprintReadOnly)
	int32 PlayerIndex;
	int32 Hitstun = -1;
	int32 Blockstun = -1;
	int32 Untech = -1;
	int32 KnockdownTime = -1;
	int32 InstantBlockTimer = -1;
	int32 ParryTimer = -1;
	int32 TotalProration = 10000;
	int32 ComboCounter = 0;
	int32 ComboTimer = 0;
	int32 LoopCounter = 0;
	int32 ThrowTechTimer;
	int32 HasBeenOTG;
	int32 WallTouchTimer;
	uint32 InvulnFlags;
	int32 StrikeInvulnerableForTime;
	int32 ThrowInvulnerableForTime;
	int RoundWinTimer = 300;
	int MeterCooldownTimer = 0;
	
	//movement values
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FDashInitSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FDashAccel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FDashMaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FDashFriction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BDashSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BDashHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BDashGravity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 JumpHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FJumpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BJumpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 JumpGravity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SuperJumpHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FSuperJumpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BSuperJumpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SuperJumpGravity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AirDashMinimumHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FAirDashSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BAirDashSpeed;
	//how long until gravity kicks in
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FAirDashTime;
	//how long until gravity kicks in
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BAirDashTime;
	//how long until airdash cancellable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FAirDashNoAttackTime;
	//how long until airdash cancellable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BAirDashNoAttackTime; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AirJumpCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AirDashCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StandPushWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StandPushHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CrouchPushWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CrouchPushHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AirPushWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AirPushHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AirPushHeightLow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CloseNormalRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ComboRate = 60;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 OtgProration = 80;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ForwardWalkMeterGain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ForwardJumpMeterGain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ForwardDashMeterGain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ForwardAirDashMeterGain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MeterPercentOnHit = 72;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MeterPercentOnHitGuard = 18;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MeterPercentOnReceiveHitGuard = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MeterPercentOnReceiveHit = 40;
	UPROPERTY(EditAnywhere)
	TArray<FString> ThrowLockCels;

	//custom player values, reset at end of round. use to keep track of values (timers, toggles, counters, etc) that are specific to the character.
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerVal1 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerVal2 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerVal3 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerVal4 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerVal5 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerVal6 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerVal7 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerVal8 = 0;
	
	//state machine
	UPROPERTY()
	FStateMachine StateMachine;
	//input buffer
	FInputBuffer InputBuffer; 

	//chain cancels (copied from TArray to static array)
	int32 ChainCancelOptionsInternal[CancelArraySize];
	//whiff cancels (copied from TArray to static array)
    int32 WhiffCancelOptionsInternal[CancelArraySize]; 
	CString<64> BufferedStateName;
	CString<64> StateName;
	CString<64> ExeStateName;

	//last received hit action. clear after read
	EHitAction ReceivedHitAction = HACT_None;
	//last received attack level. clear after read
	int ReceivedAttackLevel = -1; 

	//pointer to active enemy.
	UPROPERTY(BlueprintReadOnly)
	APlayerCharacter* Enemy; 

	UPROPERTY()
	ABattleActor* ChildBattleActors[32];

	UPROPERTY()
	ABattleActor* StoredBattleActors[16];

	bool ComponentVisible[MaxComponentCount];
	FSavedInputCondition SavedInputCondition;
	
	//anything past here isn't saved or loaded for rollback	
	int32 PlayerSyncEnd; 

	UPROPERTY()
	TArray<USubroutine*> Subroutines;
	TArray<FString> SubroutineNames;
	UPROPERTY()
	TArray<USubroutine*> CommonSubroutines;
	TArray<FString> CommonSubroutineNames;

	UPROPERTY(EditAnywhere)
	UNightSkyScript* CharaScript;
	FScriptAnalyzer CharaAnalyzer;
	UPROPERTY(EditAnywhere)
	UNightSkyScript* ObjScript;
	FScriptAnalyzer ObjAnalyzer;
	UPROPERTY(EditAnywhere)
	UNightSkyScript* CommonScript;
	FScriptAnalyzer CommonAnalyzer;
	UPROPERTY(EditAnywhere)
	UNightSkyScript* CommonObjScript;
	FScriptAnalyzer CommonObjAnalyzer;

	//list of common subroutines
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USubroutineData* CommonSubroutineData;
	//list of chara/object subroutines
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USubroutineData* CharaSubroutineData;
	//state container
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStateDataAsset* StateDataAsset;
	//common object state container
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStateDataAsset* CommonObjectStateDataAsset;
	//object state container
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStateDataAsset* ObjectStateDataAsset;
	//list of common states, for use with script
	UPROPERTY()
	TArray<UState*> CommonStates;
	//list of common object states, for use with script
	UPROPERTY()
	TArray<UState*> CommonObjectStates;
	//list of common object state names, for use with script
	UPROPERTY()
	TArray<FString> CommonObjectStateNames; 
	//list of object states
	UPROPERTY(BlueprintReadWrite)
	TArray<UState*> ObjectStates;
	//list of object state names
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> ObjectStateNames; 

	//chain cancels (only set via blueprints)
	TArray<FString> ChainCancelOptions;
	//whiff cancels (only set via blueprints)
	TArray<FString> WhiffCancelOptions; 

	//common particle data asset. only set in the base bp
	UPROPERTY(EditAnywhere)
	UParticleData* CommonParticleData; 
	//character specific particle data asset
	UPROPERTY(EditAnywhere)
	UParticleData* ParticleData;
	//character specific particle data asset
	UPROPERTY(EditAnywhere)
	ULinkMeshData* LinkMeshData;
	//holds all common sound effects
	UPROPERTY(EditAnywhere)
	USoundData* CommonSoundData;
	//character sounds
	UPROPERTY(EditAnywhere)
	USoundData* SoundData;
	//voices
	UPROPERTY(EditAnywhere)
	USoundData* VoiceData; 
	//common level sequences
	UPROPERTY(EditAnywhere)
	USequenceData* CommonSequenceData;
	//character level sequences
	UPROPERTY(EditAnywhere)
	USequenceData* SequenceData;
	UPROPERTY(BlueprintReadOnly)
	int32 ColorIndex = 1;
	UPROPERTY()
	TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
	
private:
	//internal functions
	virtual void BeginPlay() override;
	//inits states for script
	void InitStates();
	//update state
	void HandleStateMachine(bool Buffer);
	//buffer state
	void HandleBufferedState();
	//check state conditions
	bool HandleStateCondition(EStateCondition StateCondition);
	//check if chain cancel option exists
	bool FindChainCancelOption(FString Name);
	//check if whiff cancel option exists
	bool FindWhiffCancelOption(FString Name); 
	//sets visibility of components
	void SetComponentVisibility();
	//calculates ultra factor and adds to ultra gauge
	void CalculateUltra();
	//constructs all link meshes on begin play to save for later
	void ConstructLinkMeshes();
	
public:
	virtual void Tick(float DeltaTime) override;
	//initialize player for match/round start
	void InitPlayer();
	//based on received hit action, choose state
	void HandleHitAction();
	//check attack against block stance
	bool IsCorrectBlock(EBlockType BlockType);
	//check attack against parry stance
	bool IsCorrectParry(EBlockType BlockType);
	//check missed instant block
	void CheckMissedInstantBlock();
	//check missed parry
	void CheckMissedParry();
	//jump to correct block state
	void HandleBlockAction(EBlockType BlockType);
	//called whenever state changes
	void OnStateChange(); 
	virtual void Update() override;
	void SaveForRollbackPlayer(unsigned char* Buffer);
	void LoadForRollbackPlayer(unsigned char* Buffer);
	virtual void LogForSyncTest() override;
	virtual void LogForSyncTestFile(FILE* file) override;
	//upon successful throw, jump to state
	void ThrowExe();
	//handles throwing objects
	void HandleThrowCollision();
	//checks kara cancel
	bool CheckKaraCancel(EStateType InStateType);
	//checks if a child object with a corresponding object id exists. if so, do not enter state 
	bool CheckObjectPreventingState(int InObjectID);
	//resets object for next round
	void ResetForRound();
	//handles wall bounce
	void HandleWallBounce();
	//handles ground bounce
	void HandleGroundBounce();
	
	//bp callable functions
	//add state to state machine
	UFUNCTION(BlueprintCallable)
	void AddState(FString Name, UState* State); 
	//add subroutine to state machine
	UFUNCTION(BlueprintCallable)
	void AddSubroutine(FString Name, USubroutine* Subroutine);
	//calls subroutine
	UFUNCTION(BlueprintCallable)
	void CallSubroutine(FString Name);
	//use meter
	UFUNCTION(BlueprintCallable)
	void UseMeter(int Use);
	//use universal gauge
	UFUNCTION(BlueprintCallable)
	void UseUniversalGauge(int Use);
	//add meter
	UFUNCTION(BlueprintCallable)
	void AddMeter(int Meter);
	//add universal gauge
	UFUNCTION(BlueprintCallable)
	void AddUniversalGauge(int Gauge);
	//add ultra factor
	UFUNCTION(BlueprintCallable)
	void AddUltraFactor(int Factor);
	//sets meter gain cooldoown timer
	UFUNCTION(BlueprintCallable)
	void SetMeterCooldownTimer(int Timer);
	//set opponent burst locked
	UFUNCTION(BlueprintCallable)
	void SetLockOpponentBurst(bool Locked);
	//set standing/crouching/jumping
	UFUNCTION(BlueprintCallable)
	void SetActionFlags(EActionFlags ActionFlag);
	//force set state
	UFUNCTION(BlueprintCallable, CallInEditor)
	void JumpToState(FString NewName);
	//gets current state name
	UFUNCTION(BlueprintPure)
	FString GetCurrentStateName();
	//gets loop counter
	UFUNCTION(BlueprintPure)
	int32 GetLoopCount();
	//gets loop counter
	UFUNCTION(BlueprintCallable)
	void IncrementLoopCount();
	//check if state can be entered
	UFUNCTION(BlueprintPure)
	bool CheckStateEnabled(EStateType StateType);
	//enable state type
	UFUNCTION(BlueprintCallable)
	void EnableState(EEnableFlags NewEnableFlags);
	//enable all attacks only
	UFUNCTION(BlueprintCallable)
	void EnableAttacks();
	//enable cancelling into same state
	UFUNCTION(BlueprintCallable)
	void EnableCancelIntoSelf(bool Enable);
	//disable state type
	UFUNCTION(BlueprintCallable)
	void DisableState(EEnableFlags NewEnableFlags);
	//disable ground movement only
	UFUNCTION(BlueprintCallable)
	void DisableGroundMovement();
	//enable all states (besides tech)
	UFUNCTION(BlueprintCallable)
	void EnableAll(); 
	//disable all states (besides tech)
	UFUNCTION(BlueprintCallable)
	void DisableAll();
	//checks raw inputs (after side switching)
	UFUNCTION(BlueprintPure)
	bool CheckInputRaw(EInputFlags Input);
	//checks input condition
	UFUNCTION(BlueprintPure)
	bool CheckInput(FInputCondition Input); 
	UFUNCTION(BlueprintPure)
	bool CheckIsStunned();
	UFUNCTION(BlueprintCallable)
	void RemoveStun();
	//temporarily adds air jump
	UFUNCTION(BlueprintCallable)
	void AddAirJump(int32 NewAirJump);
	//temporarily adds air dash
	UFUNCTION(BlueprintCallable)
	void AddAirDash(int32 NewAirDash);
	//set air dash timer (set is forward for forward airdashes)
	UFUNCTION(BlueprintCallable)
	void SetAirDashTimer(bool IsForward);
	//set air dash timer (set is forward for forward airdashes)
	UFUNCTION(BlueprintCallable)
	void SetAirDashNoAttackTimer(bool IsForward);
	//add chain cancel option, use this in OnEntry
	UFUNCTION(BlueprintCallable)
	void AddChainCancelOption(FString Option);
	//add whiff cancel option, use this in OnEntry
	UFUNCTION(BlueprintCallable)
	void AddWhiffCancelOption(FString Option);
	//sets jump cancel on hit enabled
	UFUNCTION(BlueprintCallable)
	void EnableJumpCancel(bool Enable);
	//sets forward air dash cancel on hit enabled
	UFUNCTION(BlueprintCallable)
	void EnableFAirDashCancel(bool Enable);
	//sets back air dash cancel on hit enabled
	UFUNCTION(BlueprintCallable)
	void EnableBAirDashCancel(bool Enable);
	//sets chain cancel options enabled. on by default 
	UFUNCTION(BlueprintCallable)
	void EnableChainCancel(bool Enable);
	//sets whiff cancel options enabled. off by default
	UFUNCTION(BlueprintCallable)
	void EnableWhiffCancel(bool Enable);
	//sets special cancel enabled. off by default
	UFUNCTION(BlueprintCallable)
	void EnableSpecialCancel(bool Enable);
	//sets super cancel enabled. off by default
	UFUNCTION(BlueprintCallable)
	void EnableSuperCancel(bool Enable);
	//toggles default landing action. if true, landing will go to JumpLanding state. if false, define your own landing.
	UFUNCTION(BlueprintCallable)
	void SetDefaultLandingAction(bool Enable);
	//sets strike invulnerable enabled
	UFUNCTION(BlueprintCallable)
	void SetStrikeInvulnerable(bool Invulnerable);
	//sets throw invulnerable enabled
	UFUNCTION(BlueprintCallable)
	void SetThrowInvulnerable(bool Invulnerable);
	//sets strike invulnerable enabled for time
	UFUNCTION(BlueprintCallable)
	void SetStrikeInvulnerableForTime(int32 Timer);
	//sets throw invulnerable enabled for time
	UFUNCTION(BlueprintCallable)
	void SetThrowInvulnerableForTime(int32 Timer);
	//sets projectile invulnerable enabled
	UFUNCTION(BlueprintCallable)
	void SetProjectileInvulnerable(bool Invulnerable);
	//sets head attribute invulnerable enabled
	UFUNCTION(BlueprintCallable)
	void SetHeadInvulnerable(bool Invulnerable);
	//force enables far proximity normals
	UFUNCTION(BlueprintCallable)
	void ForceEnableFarNormal(bool Enable);
	//initiate throw
	UFUNCTION(BlueprintCallable)
	void SetThrowActive(bool Active);
	//end throw
	UFUNCTION(BlueprintCallable)
	void ThrowEnd(); 
	//initiate throw range
	UFUNCTION(BlueprintCallable)
	void SetThrowRange(int32 InThrowRange);
	//sets throw execution state
	UFUNCTION(BlueprintCallable)
	void SetThrowExeState(FString ExeState);
	//sets grip position for throw
	UFUNCTION(BlueprintCallable)
	void SetThrowPosition(int32 ThrowPosX, int32 ThrowPosY);
	//sets grip position for throw
	UFUNCTION(BlueprintCallable)
	void SetThrowLockCel(int32 Index);
	//plays voice line
	UFUNCTION(BlueprintCallable)
	void PlayVoice(FString Name);
	//plays common level sequence
	UFUNCTION(BlueprintCallable)
    void PlayCommonLevelSequence(FString Name);
	//plays character level sequence
	UFUNCTION(BlueprintCallable)
    void PlayLevelSequence(FString Name);
	//starts super freeze
	UFUNCTION(BlueprintCallable)
	void StartSuperFreeze(int Duration);
	//toggles hud visibility
	UFUNCTION(BlueprintCallable)
	void BattleHudVisibility(bool Visible);
	//disables last input
	UFUNCTION(BlueprintCallable)
	void DisableLastInput();
	//creates object
	UFUNCTION(BlueprintCallable)
	ABattleActor* AddBattleActor(FString InStateName, int32 PosXOffset, int32 PosYOffset, EPosType PosType);
	//creates object. for use with script
	ABattleActor* AddCommonBattleActor(FString InStateName, int32 PosXOffset, int32 PosYOffset, EPosType PosType);
	//stores battle actor in slot
	UFUNCTION(BlueprintCallable)
	void AddBattleActorToStorage(ABattleActor* InActor, int Index);
	//toggles visibility of component
	UFUNCTION(BlueprintCallable)
	void ToggleComponentVisibility(FString ComponentName, bool Visible);
	//sets default component visibility
	UFUNCTION(BlueprintImplementableEvent)
	void SetDefaultComponentVisibility();
	
	//ONLY CALL WHEN INITIALIZING MATCH! OTHERWISE THE GAME WILL CRASH
	UFUNCTION(BlueprintImplementableEvent)
	void InitBP();
	//ONLY CALL AT THE START OF InitStateMachine! OTHERWISE THE GAME WILL CRASH
	UFUNCTION(BlueprintCallable)
	void EmptyStateMachine();

	//cpu helper functions
	//check for enemy hitbox within range
	UFUNCTION(BlueprintPure)
	bool IsEnemyHitboxWithinRange(int32 Range);

#if WITH_EDITOR
	//updates the state machine for the editor
	UFUNCTION(BlueprintCallable)
	void EditorUpdate();
#endif
};

#define SIZEOF_PLAYERCHARACTER offsetof(APlayerCharacter, PlayerSyncEnd) - offsetof(APlayerCharacter, PlayerSync)
#pragma pack(pop)
