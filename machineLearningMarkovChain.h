#pragma once
#ifndef MARKOV_H
#define MARKOV_H

    // Changing this above 10 will require you to increase the size checks
    // in logPlayerMove() and cleanUpPlayerMove() in ai.h
#define PATTERNLENGTH 4

#include <map>
#include <iterator>
#include "moveHelpers.h"
#include "stringHelpers.h"

class markovData{
    public:
    unsigned int rTimes;
    unsigned int pTimes;
    unsigned int sTimes;
};

class markovChain{
    private:
    std::map<std::string, markovData> markovMap;

    public:
    markovChain(){}

        // Log the players next move within the map
    void updateMap(std::string pattern){
        std::string copiedPattern;
        copyStringToOtherString(copiedPattern, pattern, 1, PATTERNLENGTH);

        char recentMoveInPattern = pattern.at(0);

            // If the index doesnt exist, Initialize it.
        if(markovMap.find(copiedPattern) == markovMap.end()){
            markovMap[copiedPattern].rTimes = 0;
            markovMap[copiedPattern].pTimes = 0;
            markovMap[copiedPattern].sTimes = 0;

            switch(recentMoveInPattern){
                case 'r':
                    markovMap[copiedPattern].rTimes = 1;
                    break;
                case 'p':
                    markovMap[copiedPattern].pTimes = 1;
                    break;
                case 's':
                    markovMap[copiedPattern].sTimes = 1;
                    break;
            }

        }
        else{ // If the index does exist, increment the appropriate move.
            switch(recentMoveInPattern){
                case 'r':
                    markovMap[copiedPattern].rTimes++;
                    break;
                case 'p':
                    markovMap[copiedPattern].pTimes++;
                    break;
                case 's':
                    markovMap[copiedPattern].sTimes++;
                    break;
            }
        }
    }

        // Get the players most likely next move when given a pattern.
    char getMaxMove(std::string pattern){
        if(pattern.length() < PATTERNLENGTH-1){
            std::cout << "getMaxMove() : markov.h : Pattern length is too small!" << std::endl;
        }

        std::string properLengthPattern;
        if(pattern.length() >= PATTERNLENGTH-1){
            copyStringToOtherString(properLengthPattern, pattern, 0, PATTERNLENGTH-1);
        }

        if(markovMap.find(properLengthPattern) == markovMap.end()){
            return moveHelpers.getRandomMove();
        }
        
        char maxMove;
        unsigned int maxMoveValue = 0;

            // If theyre all equal to each other, Simply randomly generate a move
            // Because the AI cant predict the players next move.
        if(markovMap[properLengthPattern].rTimes == markovMap[properLengthPattern].pTimes && markovMap[properLengthPattern].rTimes == markovMap[properLengthPattern].sTimes){
            return moveHelpers.getRandomMove();
        }

        if(markovMap[properLengthPattern].rTimes > maxMoveValue){
            maxMoveValue = markovMap[properLengthPattern].rTimes;
            maxMove = 'r';
        }

        if(markovMap[properLengthPattern].pTimes > maxMoveValue){
            maxMoveValue = markovMap[properLengthPattern].pTimes;
            maxMove = 'p';
        }

        if(markovMap[properLengthPattern].sTimes > maxMoveValue){
            maxMoveValue = markovMap[properLengthPattern].sTimes;
            maxMove = 's';
        }

        return maxMove;
    }
};



#endif