// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StudentPawn.generated.h"

UCLASS()
class MYPROJECT_API AStudentPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStudentPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    // Aktualny postêp testu (0 - 100)
    UPROPERTY(BlueprintReadOnly, Category = "Mechanika Testu")
    float TestProgress;

    // Prêdkoœæ pisania (ile procent dodaje siê co sekundê)
    UPROPERTY(EditAnywhere, Category = "Mechanika Testu")
    float WritingSpeed;

    // Flaga sprawdzaj¹ca czy gracz trzyma przycisk
    bool bIsWriting;

public:
    // Funkcje wywo³ywane w Blueprintach pod³¹czone pod klawisze
    UFUNCTION(BlueprintCallable, Category = "Mechanika Testu")
    void StartWriting();

    UFUNCTION(BlueprintCallable, Category = "Mechanika Testu")
    void StopWriting();
    bool IsWriting() const { return bIsWriting; }

protected:
	// Poziom baterii telefonu (0 - 100)
	UPROPERTY(BlueprintReadOnly, Category = "Mechanika Telefonu")
	float PhoneBattery;

	// Flaga sprawdzaj¹ca, czy gracz aktualnie patrzy w ekran telefonu
	UPROPERTY(BlueprintReadOnly, Category = "Mechanika Telefonu")
	bool bIsLookingAtPhone;

public:
	// Funkcja do wyci¹gania i chowania telefonu podpiêta pod przycisk
	UFUNCTION(BlueprintCallable, Category = "Mechanika Telefonu")
	void TogglePhone();
};
