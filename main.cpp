#include <iostream>
#include "rpsGame.h"


using namespace std;

void mainMenu(rpsGame* game){
    char choice; 
    while(choice != '0'){
        cout << "\n\n\n\n\n"
        << "----------------------------\n"
        << "Rock, Paper, Scissors! V1.0\n"
        << "Now with Machine Learning!\n"
        << "----------------------------\n\n"
        << "(0) Quit\n"
        << "(1) Play\n"
        << "Please Choose: ";

        cin.clear();
        cin >> choice;

        if(choice == '0'){
            return; // Return to main and quit the program.
        }

        if(choice == '1'){ // Play
            bool keepPlaying;
            do{
                keepPlaying = game->playGame();
            } while(keepPlaying == true);
        }
    }
}

int main()
{
    rpsGame *game;
    game = new rpsGame;
    
    mainMenu(game);

    delete game;
    return 0;
}