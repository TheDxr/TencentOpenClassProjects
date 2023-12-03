// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData.h"

#include "JsonObjectConverter.h"

// Sets default values
AGameData::AGameData()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGameData::AddPlayer(const FPlayerInfo& NewPlayer)
{
	Players.Add(NewPlayer);
}

void AGameData::EditPlayerName(int32 PlayerIndex, const FString& NewName)
{
	// 确保索引是有效的
	if (Players.IsValidIndex(PlayerIndex))
	{
		// 更新玩家的名称
		Players[PlayerIndex].PlayerName = NewName;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player index is out of range."));
	}
}

int32 AGameData::GetPlayerBoardIndex(const FString& Name)
{
	for (int i = 0; i < Players.Num(); i++)
	{
		if (Players[i].PlayerName == Name)
			return i;
	}
	return -1;
}

FString AGameData::GetPlayerBoardName(int32 Index)
{
	if (Index >= 0 && Index < Players.Num())
	{
		return Players[Index].PlayerName;
	}
	return TEXT("INVALID");
}

void AGameData::SaveBoardToFile(const FString& FileName)
{
	const auto AbsoluteFileName = FPaths::ProjectDir() + FileName;
	// 创建JSON数组
	TArray<TSharedPtr<FJsonValue>> JsonArray;

	// 遍历玩家数组，将每个玩家信息添加到JSON数组
	for (const FPlayerInfo& Player : Players)
	{
		// 创建用于存储玩家信息的JSON对象
		TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		JsonObject->SetStringField(TEXT("PlayerName"), Player.PlayerName);
		JsonObject->SetNumberField(TEXT("Score"), Player.Score);

		// 将JSON对象添加到数组
		JsonArray.Add(MakeShared<FJsonValueObject>(JsonObject));
	}

	// 将JSON数组转换为字符串
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonArray, Writer);

	// 保存JSON字符串到文件
	FFileHelper::SaveStringToFile(OutputString, *AbsoluteFileName);
}

void AGameData::UpdatePlayer(const FPlayerInfo& PlayerInfo, const FString& FileName)
{
	for(auto& player:Players)
	{
		if(player.PlayerName == PlayerInfo.PlayerName)
		{
			player.Score = PlayerInfo.Score;
			Players.Sort([](const FPlayerInfo& A, const FPlayerInfo& B) {
				return A.Score > B.Score; });
			SaveBoardToFile(FileName);
			return;
		}
	}
	AddPlayer(PlayerInfo);
	Players.Sort([](const FPlayerInfo& A, const FPlayerInfo& B) {
		return A.Score > B.Score; });
	SaveBoardToFile(FileName);
}

void AGameData::LoadBoardFromFile(const FString& FileName)
{
	FString LoadedData;
	const auto AbsoluteFileName = FPaths::ProjectDir() + FileName;
	
	if (FFileHelper::LoadFileToString(LoadedData, *AbsoluteFileName))
	{
		// 将字符串解析为JSON对象
		TArray<TSharedPtr<FJsonValue>> JsonArray;
		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(LoadedData);
		
		if (FJsonSerializer::Deserialize(Reader, JsonArray))
		{
			// 清除当前玩家信息
			Players.Empty();

			// 遍历JSON数组
			for (const TSharedPtr<FJsonValue>& Value : JsonArray)
			{
				TSharedPtr<FJsonObject> PlayerObject = Value->AsObject();

				// 创建新的玩家信息结构体
				FPlayerInfo PlayerInfo;
				PlayerInfo.PlayerName = PlayerObject->GetStringField(TEXT("PlayerName"));
				PlayerInfo.Score = PlayerObject->GetIntegerField(TEXT("Score"));

				// 添加到玩家信息数组
				Players.Add(PlayerInfo);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to parse JSON from file: %s"), *AbsoluteFileName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load file: %s"), *AbsoluteFileName);
	}
}

TArray<FPlayerInfo>& AGameData::GetPlayers()
{
	LoadBoardFromFile();
	return Players;
}

// Called when the game starts or when spawned
void AGameData::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGameData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
