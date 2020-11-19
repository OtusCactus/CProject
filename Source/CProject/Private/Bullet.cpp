// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	//sphereCollider->SetSphereRadius(15.0f);
	//RootComponent = sphereCollider;
	//sphereCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBeginOverlap);
	//sphereCollider->bHiddenInGame = false;

	sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("BulletTrigger"));
	RootComponent = sphereCollider;

	sphereCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABullet::OverlapBegins);

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OverlapBegins(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin 1"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	}
}

void ABullet::SpawnDecal(FVector spawnLocation)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	ADecalActor* decal = GetWorld()->SpawnActor<ADecalActor>(spawnLocation, FRotator(0, 0, 0));
	if (decal)
	{
		decal->SetDecalMaterial(decalToSpawn);
		decal->SetLifeSpan(60.0f);
		decal->GetDecal()->DecalSize = FVector(32.0f, 64.0f, 64.0f);
		//m_previousActionDecal = decal;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No decal spawned"));
	}
}

