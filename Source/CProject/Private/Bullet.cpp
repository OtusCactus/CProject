// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Engine/DecalActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapVolume = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapVolume"));
	RootComponent = OverlapVolume;

	

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	OverlapVolume->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBeginOverlap);
	OverlapVolume->OnComponentEndOverlap.AddDynamic(this, &ABullet::OnEndOverlap);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Ignore player (should chenge to ignore player that has shot) & ignore level streamer
	if (OtherActor->ActorHasTag("Player") || OtherActor->ActorHasTag("LevelStreamer")) {
		return;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));

	//If bullet overlaps something, should spawn the paint decal
	SpawnDecal(SweepResult.Location, SweepResult.Normal.Rotation());
	Destroy();
}

void ABullet::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ABullet::SpawnDecal(FVector spawnLocation, FRotator rotation)
{
	ADecalActor* decal = GetWorld()->SpawnActor<ADecalActor>(spawnLocation, rotation);
	if (decal)
	{
		decal->SetDecalMaterial(decalToSpawn);
		decal->SetLifeSpan(30.0f);
		decal->GetDecal()->DecalSize = FVector(32.0f, 64.0f, 64.0f);
		decal->SetActorRotation(rotation);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No decal spawned"));
	}
}

