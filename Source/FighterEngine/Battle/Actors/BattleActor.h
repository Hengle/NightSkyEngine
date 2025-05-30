// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FighterEngine/Battle/Bitflags.h"
#include "FighterEngine/Battle/CollisionBoxInternal.h"
#include "FighterEngine/DataAssets/CollisionData.h"
#include "FighterEngine/Miscellaneous/CString.h"
#include "BattleActor.generated.h"

#pragma pack (push, 1)

class UFXSystemComponent;
class UState;
class APlayerCharacter;
class AFighterGameState;

constexpr int CollisionArraySize = 50;

UENUM()
enum EDistanceType
{
	DIST_Distance,
	DIST_DistanceX,
	DIST_DistanceY,
	DIST_FrontDistanceX,
};

UENUM()
enum EHomingType
{
	HOMING_DistanceAccel,
	HOMING_FixAccel,
	HOMING_ToSpeed,
};

UENUM()
enum EPosType
{
	POS_Player,
	POS_Self,
	POS_Center,
	POS_Enemy,
	POS_Hit,
};

UENUM()
enum EObjType
{
	OBJ_Self,
	OBJ_Enemy,
	OBJ_Parent,
	OBJ_Child0,
	OBJ_Child1,
	OBJ_Child2,
	OBJ_Child3,
	OBJ_Child4,
	OBJ_Child5,
	OBJ_Child6,
	OBJ_Child7,
	OBJ_Child8,
	OBJ_Child9,
	OBJ_Child10,
	OBJ_Child11,
	OBJ_Child12,
	OBJ_Child13,
	OBJ_Child14,
	OBJ_Child15,
	OBJ_Null,
};

UENUM()
enum class EHitSFXType : uint8
{
	SFX_Punch,
	SFX_Kick,
	SFX_Slash,
};

UENUM()
enum class EHitVFXType : uint8
{
	VFX_Strike,
	VFX_Slash,
};

UENUM() 
enum EInternalValue //internal values list
{
	VAL_StoredRegister,
	VAL_Angle,
	VAL_ActionFlag,
	VAL_StateVal0,
	VAL_StateVal1,
	VAL_StateVal2,
	VAL_StateVal3,
	VAL_StateVal4,
	VAL_StateVal5,
	VAL_StateVal6,
	VAL_StateVal7,
	VAL_PlayerVal0,
	VAL_PlayerVal1,
	VAL_PlayerVal2,
	VAL_PlayerVal3,
	VAL_PlayerVal4,
	VAL_PlayerVal5,
	VAL_PlayerVal6,
	VAL_PlayerVal7,
	VAL_SpeedX, 
	VAL_SpeedY,
	VAL_ActionTime,
	VAL_AnimTime,
	VAL_PosX,
	VAL_PosY,
	VAL_Inertia,
	VAL_FacingRight,
	VAL_DistanceToFrontWall,
	VAL_DistanceToBackWall,
	VAL_IsAir,
	VAL_IsLand,
	VAL_IsStunned,
	VAL_IsKnockedDown,
	VAL_HasHit,
	VAL_IsAttacking,
	VAL_Health,
	VAL_Meter,
	VAL_DefaultCommonAction,
};

UENUM()
enum EHitAction
{
	HACT_None,
	HACT_GroundNormal,
	HACT_AirNormal,
	HACT_Crumple,
	HACT_ForceCrouch,
	HACT_ForceStand,
	HACT_GuardBreakStand,
	HACT_GuardBreakCrouch,
	HACT_AirFaceUp,
	HACT_AirVertical,
	HACT_AirFaceDown,
	HACT_Blowback,
};

UENUM()
enum EBlockType
{
	BLK_Mid,
	BLK_High,
	BLK_Low,
	BLK_None,
};

USTRUCT(BlueprintType)
struct FWallBounceEffect
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int WallBounceCount = 0;
	UPROPERTY(BlueprintReadWrite)
	int WallBounceUntech = 0;
	UPROPERTY(BlueprintReadWrite)
	int WallBounceXSpeed;
	UPROPERTY(BlueprintReadWrite)
	int WallBounceYSpeed;
	UPROPERTY(BlueprintReadWrite)
	int WallBounceGravity = 1900;
	UPROPERTY(BlueprintReadWrite)
	bool WallBounceInCornerOnly = false;
};

USTRUCT(BlueprintType)
struct FGroundBounceEffect
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int GroundBounceCount = 0;
	UPROPERTY(BlueprintReadWrite)
	int GroundBounceUntech = 0;
	UPROPERTY(BlueprintReadWrite)
	int GroundBounceXSpeed;
	UPROPERTY(BlueprintReadWrite)
	int GroundBounceYSpeed;
	UPROPERTY(BlueprintReadWrite)
	int GroundBounceGravity = 1900;
};

USTRUCT(BlueprintType)
struct FHitEffect
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int AttackLevel; //in this engine, it's only used to define effects on hit or block
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EBlockType> BlockType;
	UPROPERTY(BlueprintReadWrite)
	int Hitstun;
	UPROPERTY(BlueprintReadWrite)
	int Blockstun;
	UPROPERTY(BlueprintReadWrite)
	int Untech;
	UPROPERTY(BlueprintReadWrite)
	int Hitstop;
	UPROPERTY(BlueprintReadWrite)
	int BlockstopModifier;
	UPROPERTY(BlueprintReadWrite)
	int HitDamage;
	UPROPERTY(BlueprintReadWrite)
	int MinimumDamagePercent;
	UPROPERTY(BlueprintReadWrite)
	int ChipDamagePercent;
	UPROPERTY(BlueprintReadWrite)
	int InitialProration = 100;
	UPROPERTY(BlueprintReadWrite)
	int ForcedProration = 100;
	UPROPERTY(BlueprintReadWrite)
	int HitPushbackX;
	UPROPERTY(BlueprintReadWrite)
	int AirHitPushbackX;
	UPROPERTY(BlueprintReadWrite)
	int AirHitPushbackY;
	UPROPERTY(BlueprintReadWrite)
	int HitGravity = 1900;
	UPROPERTY(BlueprintReadWrite)
	int HitAngle;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EHitAction> GroundHitAction;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EHitAction> AirHitAction;
	UPROPERTY(BlueprintReadWrite)
	int KnockdownTime = 25;
	UPROPERTY(BlueprintReadWrite)
	FGroundBounceEffect GroundBounceEffect;
	UPROPERTY(BlueprintReadWrite)
	FWallBounceEffect WallBounceEffect;
	UPROPERTY(BlueprintReadWrite)
	EHitSFXType SFXType = EHitSFXType::SFX_Punch;
	UPROPERTY(BlueprintReadWrite)
	EHitVFXType VFXType = EHitVFXType::VFX_Strike;
	UPROPERTY(BlueprintReadWrite)
	bool DeathCamOverride;
};

USTRUCT()
struct FHomingParams
{
	GENERATED_BODY()

	EHomingType Type;
	EObjType Target = OBJ_Null;
	EPosType Pos;
	int32 OffsetX;
	int32 OffsetY;
	int32 ParamA;
	int32 ParamB;
};

UCLASS()
class FIGHTERENGINE_API ABattleActor : public APawn
{
	GENERATED_BODY()
public:
	ABattleActor();
	
	unsigned char ObjSync; //starting from this until ObjSyncEnd, everything is saved/loaded for rollback
	bool IsActive = false;
protected:
	//internal values
	int PosX;
	int PosY;
	int PrevPosX;
	int PrevPosY;
	int SpeedX;
	int SpeedY;
	int Gravity = 1900;
	int Inertia;
	int ActionTime = 0;
	int PushHeight;
	int PushHeightLow;
	int PushWidth;
	int PushWidthExpand;
	int Hitstop;
	int L;
	int R;
	int T;
	int B;
	uint32 AttackFlags = ATK_AttackProjectileAttribute;
	bool RoundStart = true;
	int32 SpeedXPercent = 100;
	bool SpeedXPercentPerFrame;
	int32 SpeedYPercent = 100;
	bool SpeedYPercentPerFrame;
    int32 GroundHeight;

public:	
	FHitEffect HitEffect;
	FHitEffect CounterHitEffect;
	FHomingParams HomingParams;
	
	//this value stores the last script value.
	int StoredRegister;
	
	//these values reset upon state change/object deactivation.
	UPROPERTY(BlueprintReadWrite)
	int StateVal1;
	UPROPERTY(BlueprintReadWrite)
	int StateVal2;
	UPROPERTY(BlueprintReadWrite)
	int StateVal3;
	UPROPERTY(BlueprintReadWrite)
	int StateVal4;
	UPROPERTY(BlueprintReadWrite)
	int StateVal5;
	UPROPERTY(BlueprintReadWrite)
	int StateVal6;
	UPROPERTY(BlueprintReadWrite)
	int StateVal7;
	UPROPERTY(BlueprintReadWrite)
	int StateVal8;

	//material parameters
	UPROPERTY(BlueprintReadWrite)
	FLinearColor MulColor = FLinearColor(1,1,1,1);
	UPROPERTY(BlueprintReadWrite)
	FLinearColor AddColor = FLinearColor(0,0,0,1);
	UPROPERTY(BlueprintReadWrite)
	int32 MulFadeSpeed;
	UPROPERTY(BlueprintReadWrite)
	int32 MulRFadeSpeed;
	UPROPERTY(BlueprintReadWrite)
	int32 MulGFadeSpeed;
	UPROPERTY(BlueprintReadWrite)
	int32 MulBFadeSpeed;
	UPROPERTY(BlueprintReadWrite)
	int32 AddFadeSpeed;
	UPROPERTY(BlueprintReadWrite)
	int32 AddRFadeSpeed;
	UPROPERTY(BlueprintReadWrite)
	int32 AddGFadeSpeed;
	UPROPERTY(BlueprintReadWrite)
	int32 AddBFadeSpeed;
	
	bool FacingRight = true;
	int MiscFlags;
	//disabled if not player
	bool IsPlayer = false;
	int SuperFreezeTime = -1;
	
	//cel name for internal use. copied from CelName FString
	CString<64> CelNameInternal;
	//for hit effect overrides
	CString<64> HitEffectName; 
	//for socket attachment
	CString<64> SocketName; 
	EObjType SocketObj = OBJ_Self;
	FVector SocketOffset = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	FVector ScaleForLink = FVector::One();
	
	//current animation time
	UPROPERTY(BlueprintReadWrite)
	int AnimTime = 0;

	//animbp time
	UPROPERTY(BlueprintReadWrite)
	int AnimBPTime = 0;

	//for spawning hit particles
	int HitPosX;
	int HitPosY;

	//for common actions: does it inherit default values?
	UPROPERTY(BlueprintReadWrite)
	bool DefaultCommonAction = true;

	FCollisionBoxInternal CollisionBoxesInternal[CollisionArraySize];
	
	CString<64> ObjectStateName;
	uint32 ObjectID;

	//pointer to player. if this is not a player, it will point to the owning player.
	UPROPERTY(BlueprintReadOnly)
	APlayerCharacter* Player; 

	//anything past here isn't saved or loaded for rollback
	int ObjSyncEnd;

	int ObjNumber;
	
	UPROPERTY()
	AFighterGameState* GameState;

	//for use with non-character objects only. sets the state for it to use
	UPROPERTY()
	UState* ObjectState; 

	//only used for rendering collision
	UPROPERTY(EditAnywhere)
	UMaterial* BoxMaterial; 
	
	//cel name. used for animation and collision data calls.
	UPROPERTY(BlueprintReadOnly)
	FString CelName; 

	//grabbed collision boxes from collision data
	UPROPERTY()
	TArray<FCollisionBoxInternal> CollisionBoxes; 
	
	//common collision data asset
	UPROPERTY(EditAnywhere)
	UCollisionData* CommonCollisionData; 
	//collision data asset
	UPROPERTY(EditAnywhere)
	UCollisionData* CollisionData; 

	//non-player objects only. particle that moves with the object.
	UPROPERTY()
	UFXSystemComponent* LinkedParticle;
	//non-player objects only. particle that moves with the object.
	UPROPERTY()
	USkeletalMeshComponent* LinkedMesh;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//move object based on speed and inertia
	void Move();
	//calculates homing speed based on params
	void CalculateHoming();
	//get boxes based on cel name
	void GetBoxes(); 
	void UpdateVisualLocation();
	
public:
	void SaveForRollback(unsigned char* Buffer);
	void LoadForRollback(unsigned char* Buffer);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//internal functions
	//handles pushing objects
	void HandlePushCollision(ABattleActor* OtherObj);
	//handles hitting objects
	void HandleHitCollision(APlayerCharacter* OtherChar);
	//handles appling hit effect
	void HandleHitEffect(APlayerCharacter* OtherChar, FHitEffect InHitEffect);
	//handles object clashes
	void HandleClashCollision(ABattleActor* OtherObj);
	//handles flip
	void HandleFlip();
	//gets position from pos type
	void PosTypeToPosition(EPosType Type, int32* OutPosX, int32* OutPosY);
	
	//sets internal value for script
	UFUNCTION(BlueprintCallable)
	void SetInternalValue(EInternalValue InternalValue, int32 NewValue, EObjType ObjType = OBJ_Self);
	
	virtual void LogForSyncTest();
	virtual void LogForSyncTestFile(FILE* file);

	//initializes the object. not for use with players.
	void InitObject();
	//updates the object. called every frame
	virtual void Update();

	//static helpers
	static int32 Vec2Angle_x1000(int32 x, int32 y);
	static int32 Cos_x1000(int32 Deg_x10);
	static int32 Sin_x1000(int32 Deg_x10);
	
	//bp callable functions
	//gets internal value for bp
	UFUNCTION(BlueprintPure)
	int GetInternalValue(EInternalValue InternalValue, EObjType ObjType = OBJ_Self);
	//checks if on frame
	UFUNCTION(BlueprintPure)
	bool IsOnFrame(int Frame);
	//check if hitstop, super freeze, or throw lock is active
	UFUNCTION(BlueprintPure)
	bool IsStopped();
	//sets cel name
	UFUNCTION(BlueprintCallable)
	void SetCelName(FString InCelName);
	//sets custom hit effect name
	UFUNCTION(BlueprintCallable)
	void SetHitEffectName(FString InHitEffectName);
	//sets x position
	UFUNCTION(BlueprintCallable)
	void SetPosX(int InPosX);
	//sets y position
	UFUNCTION(BlueprintCallable)
	void SetPosY(int InPosY);
	//adds x position depending on direction
	UFUNCTION(BlueprintCallable)
	void AddPosX(int InPosX);
	//adds x position with no regard for direction
	UFUNCTION(BlueprintCallable)
	void AddPosXRaw(int InPosX);
	//adds y position
	UFUNCTION(BlueprintCallable)
	void AddPosY(int InPosY);
	//sets x speed
	UFUNCTION(BlueprintCallable)
	void SetSpeedX(int InSpeedX);
	//sets x speed with no regard for direction
	UFUNCTION(BlueprintCallable)
	void SetSpeedXRaw(int InSpeedX);
	//sets y speed
	UFUNCTION(BlueprintCallable)
	void SetSpeedY(int InSpeedY);
	//adds x speed
	UFUNCTION(BlueprintCallable)
	void AddSpeedX(int InSpeedX);
	//adds x speed with no regard for direction
	UFUNCTION(BlueprintCallable)
	void AddSpeedXRaw(int InSpeedX);
	//adds y speed
	UFUNCTION(BlueprintCallable)
	void AddSpeedY(int InSpeedY);
	//the current x speed will be set to this percent.
	UFUNCTION(BlueprintCallable)
	void SetSpeedXPercent(int32 Percent);
	//the current x speed will be set to this percent every frame.
	UFUNCTION(BlueprintCallable)
	void SetSpeedXPercentPerFrame(int32 Percent);
	//the current y speed will be set to this percent.
	UFUNCTION(BlueprintCallable)
	void SetSpeedYPercent(int32 Percent);
	//the current y speed will be set to this percent every frame.
	UFUNCTION(BlueprintCallable)
	void SetSpeedYPercentPerFrame(int32 Percent);
	//sets gravity
	UFUNCTION(BlueprintCallable)
	void SetGravity(int InGravity);
	//adds gravity
	UFUNCTION(BlueprintCallable)
	void AddGravity(int InGravity);
	//sets inertia. when inertia is enabled, inertia adds to your position every frame, but inertia decreases every frame
	UFUNCTION(BlueprintCallable)
	void SetInertia(int InInertia);
	//adds inertia
	UFUNCTION(BlueprintCallable)
	void AddInertia(int InInertia);
	//clears inertia
	UFUNCTION(BlueprintCallable)
	void ClearInertia();
	//enables inertia
	UFUNCTION(BlueprintCallable)
	void EnableInertia();
	//disables inertia
	UFUNCTION(BlueprintCallable)
	void DisableInertia();
	//halts momentum
	UFUNCTION(BlueprintCallable)
	void HaltMomentum();
	//sets homing parameters
	UFUNCTION(BlueprintCallable)
	void SetHomingParam(EHomingType Type, EObjType Target, EPosType Pos, int32 OffsetX, int32 OffsetY, int32 ParamA, int32 ParamB);
	//clears homing parameters
	UFUNCTION(BlueprintCallable)
	void ClearHomingParam();
	//calculates distance between points
	UFUNCTION(BlueprintCallable)
	int32 CalculateDistanceBetweenPoints(EDistanceType Type, EObjType Obj1, EPosType Pos1, EObjType Obj2, EPosType Pos2);
	//sets x position by percent of screen
	UFUNCTION(BlueprintCallable)
	void SetPosXByScreenPercent(int32 ScreenPercent);
	//expands pushbox width temporarily
	UFUNCTION(BlueprintCallable)
	void SetPushWidthExpand(int Expand);
	//sets direction
	UFUNCTION(BlueprintCallable)
	void SetFacing(bool NewFacingRight);
	//flips character
	UFUNCTION(BlueprintCallable)
	void FlipCharacter();
	//enables auto flip
	UFUNCTION(BlueprintCallable)
	void EnableFlip(bool Enabled);
	//sets ground height
	UFUNCTION(BlueprintCallable)
	void SetGroundHeight(int32 NewGroundHeight);
	//enables hit
	UFUNCTION(BlueprintCallable)
	void EnableHit(bool Enabled);
	//enables prorate once
	UFUNCTION(BlueprintCallable)
	void EnableProrateOnce(bool Enabled);
	//toggles push collision
	UFUNCTION(BlueprintCallable)
	void SetPushCollisionActive(bool Active);
	//sets attacking. while this is true, you can be counter hit, but you can hit the opponent and chain cancel.
	UFUNCTION(BlueprintCallable)
	void SetAttacking(bool Attacking);
	//gives the current move the head attribute. for use with air attacks
	UFUNCTION(BlueprintCallable)
	void SetHeadAttribute(bool HeadAttribute);
	//gives the current move the projectile attribute. for use with projectile attacks
	UFUNCTION(BlueprintCallable)
	void SetProjectileAttribute(bool ProjectileAttribute);
	//sets hit effect on normal hit
	UFUNCTION(BlueprintCallable)
	void SetHitEffect(FHitEffect InHitEffect);
	//sets hit effect on counter hit
	UFUNCTION(BlueprintCallable)
	void SetCounterHitEffect(FHitEffect InHitEffect);
	//creates common particle
	UFUNCTION(BlueprintCallable)
	void CreateCommonParticle(FString Name, EPosType PosType, FVector Offset = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator);
	//creates character particle
	UFUNCTION(BlueprintCallable)
	void CreateCharaParticle(FString Name, EPosType PosType, FVector Offset = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator);
	//creates common particle and attaches it to the object. only use with non-player objects.
	UFUNCTION(BlueprintCallable)
	void LinkCommonParticle(FString Name);
	//creates character particle and attaches it to the object. only use with non-player objects.
	UFUNCTION(BlueprintCallable)
	void LinkCharaParticle(FString Name);
	//creates character mesh and attaches it. only use with non-player objects.
	UFUNCTION(BlueprintCallable)
	void LinkCharaMesh(FString Name);
	//plays common sound
	UFUNCTION(BlueprintCallable)
	void PlayCommonSound(FString Name);
	//plays chara sound
	UFUNCTION(BlueprintCallable)
	void PlayCharaSound(FString Name);
	//attaches object to skeletal socket
	UFUNCTION(BlueprintCallable)
	void AttachToSocketOfObject(FString InSocketName, FVector Offset, EObjType ObjType);
	//detaches object from skeletal socket
	UFUNCTION(BlueprintCallable)
	void DetachFromSocket();
	//pauses round timer
	UFUNCTION(BlueprintCallable)
	void PauseRoundTimer(bool Pause);
	//sets object id
	UFUNCTION(BlueprintCallable)
	void SetObjectID(int InObjectID);
	//gets object by type
	UFUNCTION(BlueprintPure)
	ABattleActor* GetBattleActor(EObjType Type);
	//if object goes beyond screen bounds, deactivate
	UFUNCTION(BlueprintCallable)
	void DeactivateIfBeyondBounds();
	//if player changes state, deactivate
	UFUNCTION(BlueprintCallable)
	void EnableDeactivateOnStateChange(bool Enable);
	//if player receives hit, deactivate
	UFUNCTION(BlueprintCallable)
	void EnableDeactivateOnReceiveHit(bool Enable);
	//sets the object to deactivate next frame.
	UFUNCTION(BlueprintCallable)
	void DeactivateObject();
	//resets object for next use
	void ResetObject();
	//views collision. only usable in development or debug builds
	UFUNCTION(BlueprintCallable)
	void CollisionView();
};
#pragma pack(pop)

#define SIZEOF_BATTLEACTOR offsetof(ABattleActor, ObjSyncEnd) - offsetof(ABattleActor, ObjSync)