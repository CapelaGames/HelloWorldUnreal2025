// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

	Mesh->SetSimulatePhysics(true);
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Hello World"));

	MoveSpeed *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPawn::MoveRight);
	InputComponent->BindAction("Jump",IE_Pressed, this, &AMyPawn::Jump);
	InputComponent->BindAction("Create",IE_Pressed, this, &AMyPawn::SpawnActor);

}
void AMyPawn::MoveForward(float Value) 
{
	const FVector Forward = Camera->GetForwardVector() * MoveSpeed * Value;
	Mesh->AddForce(Forward);
}
void AMyPawn::MoveRight(float Value) 
{
	const FVector Right = Camera->GetRightVector() * MoveSpeed * Value;
	Mesh->AddForce(Right);
}

void AMyPawn::Jump() 
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange,
			FString::Printf(TEXT("Jump Pressed")));
}

void AMyPawn::SpawnActor()
{
	GetWorld()->SpawnActor<AActor>(actorBPToSpawn, GetActorTransform());
}


