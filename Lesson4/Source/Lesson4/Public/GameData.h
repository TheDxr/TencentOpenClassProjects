// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Score;
};

UCLASS()
class LESSON4_API AGameData : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameData();

	UFUNCTION(BlueprintCallable)
    void AddPlayer(const FPlayerInfo& NewPlayer);

    UFUNCTION(BlueprintCallable)
    void EditPlayerName(int32 PlayerIndex, const FString& NewName);
	
	UFUNCTION(BlueprintCallable)
	int32 GetPlayerBoardIndex(const FString& Name);

	UFUNCTION(BlueprintCallable)
	FString GetPlayerBoardName(int32 Index);

	UFUNCTION(BlueprintCallable)
	void SaveBoardToFile(const FString& FileName = "GameData.json");

	UFUNCTION(BlueprintCallable)
	void UpdatePlayer(const FPlayerInfo& PlayerInfo,const FString& FileName = "GameData.json");
	UFUNCTION(BlueprintCallable)
	void LoadBoardFromFile(const FString& FileName = "GameData.json");

	UFUNCTION(BlueprintCallable)
	TArray<FPlayerInfo>& GetPlayers();
private:
	TArray<FPlayerInfo> Players;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
