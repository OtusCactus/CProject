// Copyright Epic Games, Inc. All Rights Reserved.

#include "CProjectGameMode.h"
#include "CProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ACProjectGameMode::ACProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ACProjectGameMode::RewpawnPlayer()
{
	//APlayerController* player = UGameplayStatics::GetPlayerController(this, 0);
	//AActor* playerActor = Cast<AActor>(player);
	//GetWorld()->SpawnActor<AActor>(PlayerToSpawn, spawnPosition, spawnRotation);
	//GetWorld()->SpawnActor<AActor>(explosion, spawnPosition, spawnRotation);

	//APawn* ResultPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, spawnPosition, spawnRotation);
	//player = Cast<APlayerController>(ResultPawn);
	//player->Possess(ResultPawn);


	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Respawn"));

	//GetWorld()->GetAuthGameMode()->RestartPlayer(GetWorld()->GetFirstPlayerController());
}
