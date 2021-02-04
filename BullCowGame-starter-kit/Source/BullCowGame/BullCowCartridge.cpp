// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    //Welcoming the player
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bull Cows game!"));
    PrintLine(TEXT("Guess the 4 letter word!")); //Magic Number Remove!
    PrintLine(TEXT("Press enter..."));

    //Setting up the game
    GameStart();
    

    //Set lives

    //Prompt player for guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    //check PlayerGuess

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
    }
    else
    {
        if (Input.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("The HiddenWord is 4 characters long, Try Again!")); //Magic number
        }
        
        PrintLine(TEXT("You have lost!"));
    }
    //check if isogram
    //Prompt to guess again
    //check right number of characters
    //Prompt to guess again

    //remove life

    //check lives > 0
    //if yes GuessAgain
    //show lives left
    //if no show GameOver and HiddenWord?
    //Prompt to play again, Press enter to play again
    //Check User input
    //PlayAgain or Quit
}
void UBullCowCartridge::GameStart()
{
    HiddenWord = TEXT("Life");
    Lives = 3;
}