#pragma once

#ifndef RPS_H
#define RPS_H

#include "ai.h"
#include <iomanip>

class rpsGame{
    private:
    AI *rpsAI;
    float playerGamesPlayed;
    float playerWins;
    float ties;
    
    public:
    rpsGame(){
        rpsAI = new AI;
        
        playerGamesPlayed = 0;
        playerWins = 0;
        ties = 0;
    }

    ~rpsGame(){
        delete rpsAI;
    }

    void printGameStats(){
        if(playerWins > 0 && playerGamesPlayed > 0)
            std::cout << "Player Wins: " << playerWins << " " << std::fixed << std::setprecision(2) << 100 * (playerWins / playerGamesPlayed) << "%" << "\n";
        else
            std::cout << "Player Wins: 0 0% \n";

        rpsAI->printAIStats();
    }

    // Returns 0 if the AI won.
    // Returns 1 if the player won.
    // Returns 2 if it was a tie.
    int whoWon(char playerMove, char AiMove){
            // Check if there was a tie.
        if(playerMove == AiMove)
            return 2;
        
            // Determine if the player won.
        switch(playerMove){
            case 'r':
                if(AiMove != 'p')
                    return 1;
                break;

            case 'p':
                if(AiMove != 's')
                    return 1;
                break;

            case 's':
                if(AiMove != 'r')
                    return 1;
                break;
        }

            // AI Won
        return 0;
    }

    bool isValidInput(char move){
        switch(move){
            case 'r':
                break;
            case 'p':
                break;
            case 's':
                break;
            case 'n': // Player wants to quit
                break;

            default:
                return false;
        }

        return true;
    }

    // Returns true if the player wants to continue playing.
    // If they wish to stop playing it returns false.
    bool playGame(){
        std::cout << "\nGame #" << std::setprecision(0) << playerGamesPlayed << "\n";

        printGameStats();

        std:: cout << "Your move options are r, p, or s.\n"
        << "If you wish to stop playing, Please input n.\n"
        << "Input your move: ";
        char playerMove;
        
        // Take the players input, and perform input validation.
        bool playerMoveIsValid = 0;
        do{
            std::cin.clear();
            std::cin >> playerMove;

            playerMoveIsValid = isValidInput(playerMove);
            if(playerMoveIsValid == 0){
                std::cout << "Invalid Input\n"
                << "Please input either r, p, or s.\n"
                << "If you wish to stop playing, Input n.\n";
            }
        }while(playerMoveIsValid == 0);

            // Quit back to main menu.
        if(playerMove == 'n')
            return false;

            // Generate AI move and determine who won.
        char aiMove = rpsAI->generateMove();
        int matchResult = whoWon(playerMove, aiMove);

        rpsAI->incrementAIGamesPlayed();
        rpsAI->logPlayerMove(playerMove);

            // Output the appropriate message according to who won.
        switch(matchResult){
            case 0:
                playerGamesPlayed++;
                rpsAI->incrementAIWins();
                std::cout << "You Lost!\n";
                break;

            case 1:
                playerGamesPlayed++;
                playerWins++;
                std::cout << "Congrats, You Won!\n";
                break;

            case 2:
                playerGamesPlayed++;
                ties++;
                std::cout << "Tie! None of you won.\n";
                break;

            default:
                std::cout << "Error: Unknown Move!\n";
        }

        std::cout << "Your Move: " << playerMove
        << "\nAI Move: " << aiMove << std::endl;

            // Keep Playing
        return true;
    }
};

#endif