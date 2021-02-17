// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    //Welcoming the player
    Super::BeginPlay();
    
    GameStart();
    //EndGame();

    PrintLine(TEXT("The number of possible words is: %i."), Words.Num());
    PrintLine(TEXT("The number of valid words is: %i."), GetValidWords(Words).Num());
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
    //Declare and Initialize integers here
    //int32 Index = 0;
    //int32 Comparison = Index + 1;

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
    TArray<FString> ValidWords;

    for (int32 Index = 0; Index < Words.Num(); Index++) //If you loop through multiple times and you use !=, it will cause problems
    {
        if (Words[Index].Len() >= 4 && Words[Index].Len() <= 8)
        {
            ValidWords.Emplace(Words[Index]);
            
        }
    }
    return ValidWords;
}
//     for (int32 Index = 0; Index < ValidWords.Num(); Index++)
//     {
//         PrintLine(TEXT("%s."), *ValidWords[Index]);
//     }