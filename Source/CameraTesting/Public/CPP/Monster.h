// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Monster.generated.h"

class UCurveFloat;

UCLASS()
class CAMERATESTING_API AMonster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonster();
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float MovementSpeed = 100.0f;
	UPROPERTY()
	float FakeTimeline = 0.0f;
	UPROPERTY()
	bool bIsMoveForward = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Movement
	void MoveObject(float DeltaTime);

	//Movement Spline Variables
	UPROPERTY(EditAnywhere, Category="Monster")
	UStaticMeshComponent* MonsterBody;
	
	UPROPERTY(VisibleAnywhere, Category="Spline")
	USplineComponent* SplineComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline")
	UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline")
	TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
