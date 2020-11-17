// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnPOint.h"
#include "D:\IIM\A4\Unreal\Projet\CProject\Source\CProject\CProjectGameMode.h"

// Sets default values for this component's properties
URespawnPOint::URespawnPOint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URespawnPOint::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GM = GetWorld()->GetAuthGameMode();
	ACProjectGameMode* GameMode = Cast<ACProjectGameMode>(GM);
	GameMode->SetRespawnPoint(this->GetOwner());

	// ...
	
}


// Called every frame
void URespawnPOint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

