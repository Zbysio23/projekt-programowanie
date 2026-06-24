// Fill out your copyright notice in the Description page of Project Settings.


#include "TeacherAI.h"
#include "StudentPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATeacherAI::ATeacherAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentState = ETeacherState::Idle;
	StateTimer = 0.0f;
}

// Called when the game starts or when spawned
void ATeacherAI::BeginPlay()
{
	Super::BeginPlay();

	// STL: Wype³niamy wektor losowymi czasami fazy "spokoju"
	IdleIntervals = { 4.0f, 6.0f, 3.5f, 7.5f };

	PlayerRef = Cast<AStudentPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	ChangeState(ETeacherState::Idle);
}

void ATeacherAI::ChangeState(ETeacherState NewState)
{
	CurrentState = NewState;
	OnStateChanged(CurrentState); // Informujemy Blueprint o zmianie stanu

	switch (CurrentState)
	{
	case ETeacherState::Idle:
		if (!IdleIntervals.empty())
		{
			int32 RandomIndex = FMath::RandRange(0, IdleIntervals.size() - 1);
			StateTimer = IdleIntervals[RandomIndex];
		}
		break;

	case ETeacherState::Suspicious:
		StateTimer = 1.5f; // ¯ó³ty wykrzyknik wisi przez 1.5 sekundy
		break;

	case ETeacherState::Looking:
		StateTimer = 3.0f; // Oko wisi przez 3 sekundy (faza skanowania klasy)
		break;
	}
}

// Called every frame
void ATeacherAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StateTimer > 0.0f)
	{
		StateTimer -= DeltaTime;
		if (StateTimer <= 0.0f)
		{
			if (CurrentState == ETeacherState::Idle) ChangeState(ETeacherState::Suspicious);
			else if (CurrentState == ETeacherState::Suspicious) ChangeState(ETeacherState::Looking);
			else if (CurrentState == ETeacherState::Looking) ChangeState(ETeacherState::Idle);
		}
	}

	// Jeœli nauczyciel patrzy, a gracz pisze = przegrana
	if (CurrentState == ETeacherState::Looking && PlayerRef)
	{
		if (PlayerRef->IsWriting())
		{
			OnPlayerCaught();
			SetActorTickEnabled(false);
		}
	}
}

