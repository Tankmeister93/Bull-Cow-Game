// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
//#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    //Welcoming the player
    Super::BeginPlay();

    Isograms = GetValidWords(Words);

    GameStart();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        GameStart();
    }
    else //check PlayerGuess
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::GameStart()
{
    PrintLine(TEXT("Welcome to Bull Cows game!"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() -1)];
    Lives = HiddenWord.Len(); //Setting the lives to word length
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord); //This is a debug line
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue...")); //Prompt player for guess
}
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
    int32 Bulls, Cows;//declaring variables
    GetBullCows(Guess, Bulls, Cows);//declaring two variables, but not initializing, and then immediantly using them in a function. This is a sign of out parameters
    PrintLine(TEXT("You have %i bulls and %i cows"), Bulls, Cows);
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}
bool UBullCowCartridge::IsIsogram(const FString& Word) const
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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word: WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);   
        }
    }
    return ValidWords;
}
void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    BullCount = 0;
    CowCount = 0;

    //for every index Guess is same as index Hidden, BullCount++
    //if not a bull was it a cow? if yes CowCount++
    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            BullCount++;
            continue;
        }
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                CowCount++;
            }            
        }
    }
}