#pragma once

#ifndef AI_H
#define AI_H

#include <fstream>
#include <vector>
#include <iomanip>

#include "machineLearningMarkovChain.h"
#include "moveHelpers.h"
#include "stringHelpers.h"


class AI{
    private:
    std::string playerMoveLog;
    markovChain* markovChain1;

    // Current game stats for the AI.
    float curAiGamesPlayed;
    float aiWins;

    public:
    AI(){
        markovChain1 = new markovChain;
        curAiGamesPlayed = 0;
        aiWins = 0;
    }

    ~AI(){
        delete markovChain1;
    }

    void logPlayerMove(char playerMove){
        playerMoveLog.insert(0, 1, playerMove);

        if(playerMoveLog.length() > 10){
            markovChain1->updateMap(playerMoveLog);
            cleanupPlayerMoveLog();
        }
    }

    // Reduces the size of the player move log to 15
    void cleanupPlayerMoveLog(){
        if(playerMoveLog.length() > 20)
            playerMoveLog.erase(15, playerMoveLog.length());
    }

    void incrementAIGamesPlayed(){
        curAiGamesPlayed++;
    }

    void incrementAIWins(){
        aiWins++;
    }

    void printAIStats(){
        if(curAiGamesPlayed > 0 && aiWins > 0)
            std::cout << "AI Wins: " << std::setprecision(0) << aiWins << " " << std::fixed << std::setprecision(2) << 100 * (aiWins / curAiGamesPlayed) << "%" << std::endl;
        else
            std::cout << "AI Wins: 0 0% \n";
    }

    char generateMove(){
        if(curAiGamesPlayed > 10){
                // Grab the move the player will most likely make next, and counter it.
            return moveHelpers.getCounterMove(markovChain1->getMaxMove(playerMoveLog));
        }

        return moveHelpers.getRandomMove();
    }

};

#endif