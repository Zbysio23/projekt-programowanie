// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include "TeacherAI.generated.h"

UENUM(BlueprintType)
enum class ETeacherState : uint8
{
	Idle        UMETA(DisplayName = "Zajety"),
	Suspicious  UMETA(DisplayName = "Podejrzliwy"),
	Looking     UMETA(DisplayName = "Patrzacy")
};

UCLASS()
class MYPROJECT_API ATeacherAI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeacherAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Teacher AI")
	ETeacherState CurrentState;

	float StateTimer;
	std::vector<float> IdleIntervals; // Kontener STL
	void ChangeState(ETeacherState NewState);

	class AStudentPawn* PlayerRef;

public:
	// To zdarzenie odbierzemy w Blueprincie do pokazania ikonek
	UFUNCTION(BlueprintImplementableEvent, Category = "Teacher AI")
	void OnStateChanged(ETeacherState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "Teacher AI")
	void OnPlayerCaught();
};
