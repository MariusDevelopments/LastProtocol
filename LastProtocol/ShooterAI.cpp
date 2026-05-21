// Fill out your copyright notice in the Description page of Project Settings.
#include "ShooterAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAI::BeginPlay()
{
	Super::BeginPlay();

	// AI Blueprint'inde Behavior Tree secildiyse kontrolcu onu calistirir.
	if (EnemeyAIBehaviorTree) {
		UE_LOG(LogTemp, Warning, TEXT("BeginPlay: Behavior Tree baslatiliyor."));
		RunBehaviorTree(EnemeyAIBehaviorTree);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("BeginPlay: EnemeyAIBehaviorTree atanmamis! Lutfen AI Blueprint'inin icinden Behavior Tree'yi sec."));
	}
}

void AShooterAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooterAI::StartBehaviorTree(ALastProtocolCharacter* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("StartBehaviorTree cagirildi!"));

	if (EnemeyAIBehaviorTree) {
		// Controller'in kontrol ettigi pawn, bizim dusman karakterimizdir.
		MyCharacter = Cast<ALastProtocolCharacter>(GetPawn());

		if (!MyCharacter) {
			UE_LOG(LogTemp, Error, TEXT("StartBehaviorTree: AI bir Pawn'u kontrol etmiyor (GetPawn null veya LastProtocolCharacter degil)"));
		}

		if (Player) {
			// GameMode'dan gelen oyuncu referansi BT task'lari tarafindan kullanilir.
			PlayerCharacter = Player;
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("StartBehaviorTree: Iceri gonderilen 'Player' parametresi bos (NULL)!"));
		}

		RunBehaviorTree(EnemeyAIBehaviorTree);

		UBlackboardComponent* MyBlackboard = GetBlackboardComponent();

		if (MyBlackboard && PlayerCharacter && MyCharacter) {
			//MyBlackboard->SetValueAsVector("PlayerLocation", PlayerCharacter->GetActorLocation());
			// AI geri donus/devriye icin kendi baslangic konumunu blackboard'a yazar.
			MyBlackboard->SetValueAsVector("StartLocation", MyCharacter->GetActorLocation());

			UE_LOG(LogTemp, Warning, TEXT("Blackboard basariyla ayarlandi! AI'nin gitmesi gereken hedef: %s"), *PlayerCharacter->GetActorLocation().ToString());
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Blackboard degerleri ATANAMADI! Blackboard Var mi: %d, Player Var mi: %d, MyCharacter Var mi: %d"),
				MyBlackboard != nullptr, PlayerCharacter != nullptr, MyCharacter != nullptr);
		}
	}
}
