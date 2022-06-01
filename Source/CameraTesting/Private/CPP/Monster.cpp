// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP/Monster.h"
#include "Components/TimelineComponent.h"

// Sets default values
AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline");
	if(SplineComponent) { SetRootComponent(SplineComponent); }
}

void AMonster::OnConstruction(const FTransform& Transform)
{
	if(!Mesh) { return;	}
		
	MonsterBody = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	MonsterBody->SetStaticMesh(Mesh);
	MonsterBody->SetMobility(EComponentMobility::Movable);
	MonsterBody->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MonsterBody->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	MonsterBody->RegisterComponentWithWorld(GetWorld());
	MonsterBody->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::MoveObject(float DeltaTime)
{
	//FString Timeline = FString::SanitizeFloat(FakeTimeline);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *Timeline);
	float SplineLength = SplineComponent->GetSplineLength();
	float Distance = FMath::Lerp(0, SplineLength, FakeTimeline);
	if(bIsMoveForward)
	{
		FakeTimeline += DeltaTime * (MovementSpeed / 1000);
	}
	else
	{
		FakeTimeline -= DeltaTime * (MovementSpeed / 1000);
	}
	if(FakeTimeline >= 1) { bIsMoveForward = false; }
	if(FakeTimeline <= 0) { bIsMoveForward = true; }
	
	FVector NewLocation = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FRotator NewRotation = SplineComponent->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
	if(!bIsMoveForward) NewRotation = NewRotation.Add(0.0, 180.0, 0.0f);
	MonsterBody->SetWorldLocationAndRotation(NewLocation, NewRotation);
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveObject(DeltaTime);
}