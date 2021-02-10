// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    //Welcoming the player
    Super::BeginPlay();

    GameStart();
    //EndGame();

    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord); //This is a debug line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        GameStart();
    }
    else //check PlayerGuess
    {
        if (Input == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
        EndGame();
    }
    else
    {
        PrintLine(TEXT("Lost a life!"));
        PrintLine(TEXT("%i"), --Lives);
        
        if (Lives > 0)
        {
            if (Input.Len() != HiddenWord.Len())
            {
            PrintLine(TEXT("Sorry, try again! \nYou have %i lives remaining"), Lives);
            }  
        }
        else
        {
            PrintLine(TEXT("You have no lives left!"));
            EndGame();
        }         
    }
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
    PrintLine(TEXT("Welcome to Bull Cows game!"));

    HiddenWord = TEXT("Life");
    Lives = HiddenWord.Len(); //Setting the lives to word length
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue...")); //Prompt player for guess
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}