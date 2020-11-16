// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CProjectGameMode.generated.h"

UCLASS(minimalapi)
class ACProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACProjectGameMode();

UFUNCTION(BlueprintCallable, Category = "Respawn")
void RewpawnPlayer();

UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
TSubclassOf<AActor> PlayerToSpawn;

UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
FVector spawnPosition;

UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
FRotator spawnRotation;

UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
TSubclassOf<AActor> explosion;
	
};



