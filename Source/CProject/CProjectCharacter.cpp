// Copyright Epic Games, Inc. All Rights Reserved.

#include "CProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "CProjectGameMode.h"
//////////////////////////////////////////////////////////////////////////
// ACProjectCharacter

ACProjectCharacter::ACProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACProjectCharacter::OnBeginOverlap);

	DeactivateSrafe();
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

//////////////////////////////////////////////////////////////////////////
// Input

void ACProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &ACProjectCharacter::TurnCharacter);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACProjectCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ACProjectCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ACProjectCharacter::OnResetVR);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACProjectCharacter::ToggleCrouch);

	PlayerInputComponent->BindAction("Strafe", IE_Pressed, this, &ACProjectCharacter::ActivateStrafe);
	PlayerInputComponent->BindAction("Strafe", IE_Released, this, &ACProjectCharacter::DeactivateSrafe);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ACProjectCharacter::Shoot);

	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &ACProjectCharacter::PickUp);
	PlayerInputComponent->BindAction("PickUp", IE_Released, this, &ACProjectCharacter::Drop);
}

void ACProjectCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ACProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ACProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ACProjectCharacter::TurnAtRate(float Rate)
{

	float turnRate = Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds();

	// calculate delta for this frame from the rate information
	AddControllerYawInput(turnRate);
	//AddActorLocalRotation(FRotator(0, turnRate * GetWorld()->GetDeltaSeconds(), 0));
}

void ACProjectCharacter::TurnCharacter(float Value)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Value);
	//AddActorLocalRotation(FRotator(0, Value * 180 * GetWorld()->GetDeltaSeconds(), 0));
}

void ACProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACProjectCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		directionValue = Value;
		isGoingSide = false;

		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACProjectCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		directionValue = Value;
		isGoingSide = true;

		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ACProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isInteracting)
	{
		LineTracePickUp();
	}
	else
	{
		LineTraceDrop();
	}
}

void ACProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

}

void ACProjectCharacter::ToggleCrouch()
{
	if (GetCharacterMovement()->IsCrouching())
	{
		UnCrouch();
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Crouch"));
		Crouch();

	}
}

void ACProjectCharacter::ActivateStrafe()
{
	isStrafing = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ACProjectCharacter::DeactivateSrafe()
{
	isStrafing = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACProjectCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Lava"))
	{
		const FVector Location = GetActorLocation();
		const FRotator Rotation = GetActorRotation();
		
		GetWorld()->SpawnActor<AActor>(deathEffect, Location, Rotation);

		ACProjectGameMode* gameMode = (ACProjectGameMode*)GetWorld()->GetAuthGameMode();
		gameMode->RewpawnPlayer();
	}
}

void ACProjectCharacter::Shoot()
{
	if (canShoot) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Shoot"));
		const FVector Location = HeldObjectsPositionActor->GetComponentLocation();
		const FRotator Rotation = HeldObjectsPositionActor->GetComponentRotation();

		AActor* bulletSpawnSpot = Cast<AActor>(bulletSpawn);

		GetWorld()->SpawnActor<AActor>(bullet, Location, Rotation);
	}
}

void ACProjectCharacter::PickUp()
{
	isInteracting = true;
}

void ACProjectCharacter::Drop()
{
	isInteracting = false;
}

void ACProjectCharacter::LineTracePickUp()
{
	FVector lastPosition = GetCharacterMovement()->GetLastUpdateLocation();

	FVector worldPosition = HeldObjectsPositionActor->GetComponentLocation();
	FVector forwardVector = HeldObjectsPositionActor->GetForwardVector();

	FVector endVector = forwardVector * LineTraceDistance + worldPosition;

	if (!isHoldingObject)
	{
		const FName TraceTag("MyTraceTag");
		GetWorld()->DebugDrawTraceTag = TraceTag;
		FCollisionQueryParams CollisionParams;
		CollisionParams.TraceTag = TraceTag;


		FHitResult ObjectHitByLineTrace;


		bool hasHitSomething = GetWorld()->LineTraceSingleByChannel(ObjectHitByLineTrace, lastPosition, endVector, ECollisionChannel::ECC_Visibility, TraceTag);


		if (hasHitSomething && ObjectHitByLineTrace.GetComponent()->Mobility == EComponentMobility::Movable)
		{
			currentObjectHeld = ObjectHitByLineTrace.GetComponent();
			currentObjectHeld->SetSimulatePhysics(false);
			AActor* objectHeldOwner = currentObjectHeld->GetOwner();
			objectHeldOwner->AttachToComponent(HeldObjectsPositionActor, FAttachmentTransformRules::SnapToTargetIncludingScale);
			isHoldingObject = true;
		}
		canShoot = true;
	}
	else
	{
		AActor* objectHeldOwner = currentObjectHeld->GetOwner();
		objectHeldOwner->AttachToComponent(HeldObjectsPositionActor, FAttachmentTransformRules::SnapToTargetIncludingScale);
		canShoot = false;
	}

}

void ACProjectCharacter::LineTraceDrop()
{
	if (IsValid(currentObjectHeld))
	{
		currentObjectHeld->SetSimulatePhysics(true);
		AActor* objectHeldOwner = currentObjectHeld->GetOwner();
		objectHeldOwner->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		currentObjectHeld = nullptr;
		isHoldingObject = false;
	}
}