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

	FStringAssetReference itemRef = "Blueprint'/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter'";
	UObject* itemObj = itemRef.ResolveObject();
	PlayerToSpawn = Cast<UBlueprint>(itemObj);

}

void ACProjectGameMode::RewpawnPlayer()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Respawn"));

    if (PlayerToSpawn == nullptr) return;

    APlayerController* player = GetWorld()->GetFirstPlayerController();
    FVector playerLocation;
    FRotator quat;
    if (player != nullptr)
    {
        quat = player->GetPawn()->GetActorRotation();
        playerLocation = player->GetPawn()->GetActorLocation();
        player->GetPawn()->Destroy();
    }

    const FActorSpawnParameters spawnParameters;


    const FVector respawnLocation = respawnPosition->GetDefaultAttachComponent()->GetComponentLocation();
    const FRotator respawnRotation = respawnPosition->GetDefaultAttachComponent()->GetComponentRotation();
    //spawn new player, doesn't work in build ?? but works in editor

    AActor* newPlayer = GetWorld()->SpawnActor<AActor>(PlayerToSpawn->GeneratedClass, respawnLocation, respawnRotation, spawnParameters);

    APawn* newPlayerPawn = Cast<APawn>(newPlayer);

    player->Possess(newPlayerPawn);
    DefaultPawnClass = newPlayerPawn->GetClass();

}

void ACProjectGameMode::SetRespawnPoint(AActor* respawnPoint)
{
    respawnPosition = respawnPoint;
}
