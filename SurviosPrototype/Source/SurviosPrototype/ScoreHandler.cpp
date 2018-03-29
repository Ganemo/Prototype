// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreHandler.h"

UScoreContainer* UScoreHandler::Scores = nullptr;


void UScoreHandler::CreateScores()
{
	if (Scores != nullptr)
		delete Scores;

	Scores = new UScoreContainer();
}

UScoreContainer* UScoreHandler::GetScores()
{
	if (Scores != nullptr)
		return Scores;
	else
	{
		CreateScores();
		return Scores;
	}
}

int UScoreHandler::AddPlayer()
{
	return GetScores()->AddPlayer();
}

int UScoreHandler::GetScore(const int Player)
{
	return GetScores()->GetScore(Player);
}

void UScoreHandler::AddScore(const int Player, const int Score)
{
	GetScores()->AddScore(Player, Score);
}