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
        ProcessGuess(Input);       
    }

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

    //const TCHAR HW[] = TEXT("Life");
    //PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0]);
}
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try again! \nYou have %i lives remaining"), Lives); 
        return;
    }
    
     //check if isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("There are no repeating letters, guess again!"));
        return;
    }

    //remove life
    PrintLine(TEXT("Lost a life!"));
    --Lives;

    if (Lives <= 0)
        {
            ClearScreen();
            PrintLine(TEXT("You have no lives left!"));
            PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);

            EndGame();
            return; 
        }

    //Show the player bulls and cows
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}
bool UBullCowCartridge::IsIsogram(FString Word) const
{
    // For each Letter.
    // Start at element[0].
    // Compare against the next letter.
    // Until we reach[Guess.Len() - 1].
    // If any letters are the same return false.

    return true;
}