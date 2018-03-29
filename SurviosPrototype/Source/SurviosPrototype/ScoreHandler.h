// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ScoreHandler.generated.h"


class SURVIOSPROTOTYPE_API UScoreContainer
{
private:
	TArray<int> Scores;
public:
	UFUNCTION(BlueprintCallable, Category = ScoreHandling)
	int GetScore(const int Player)
	{
		if (Player < Scores.Num())
			return Scores[Player];
		else
			return -1;
	};

	UFUNCTION(BlueprintCallable, Category = ScoreHandling)
	void AddScore(const int Player, const int Score)
	{
		if (Player < Scores.Num())
			Scores[Player] += Score;
	};

	UFUNCTION(BlueprintCallable, Category = ScoreHandling)
	int AddPlayer()
	{
		return Scores.Add(0);
	};
};

UCLASS()
class SURVIOSPROTOTYPE_API UScoreHandler : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	static UScoreContainer* Scores;
public:
	static UScoreContainer* GetScores();

	UFUNCTION(BlueprintCallable, Category = ScoreHandling)
	static void CreateScores();

	UFUNCTION(BlueprintCallable, Category = ScoreHandling)
	static int AddPlayer();
	UFUNCTION(BlueprintCallable, Category = ScoreHandling)
	static int GetScore(const int Player);
	UFUNCTION(BlueprintCallable, Category = ScoreHandling)
	static void AddScore(const int Player, const int Score);
	
};

