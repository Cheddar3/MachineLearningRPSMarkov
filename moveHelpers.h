#pragma once

#ifndef MOVEHELPERS_H
#define MOVEHELPERS_H

#include <random>

class moveHelpers{
    public:
    char getRandomMove(){
        float randomNumber;
        srand(time(NULL));
        randomNumber = rand() % 100 + 1;

        randomNumber = randomNumber / 100.0;

        if(randomNumber < 0.33)
                return 'r';

        if(randomNumber >= 0.33 && randomNumber < 0.66)
                return 'p';

        if(randomNumber >= 0.66)
            return 's';

        return 'n';
    }

    char getCounterMove(char plannedMove){
        switch(plannedMove){
            case 'r':
                return 'p';
                break;

            case 'p':
                return 's';
                break;

            case 's':
                return 'r';
                break;
        }
        return 'n';
    }

} moveHelpers;



#endif