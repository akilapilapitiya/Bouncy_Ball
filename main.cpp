                                            // L I B R A R Y   I M P O R T S
#include <iostream> 
#include <iomanip>
#include <thread>          //For Code Sleep
#include <chrono>          //To make the code sleep
#include <cstdlib>         // For system()
using namespace std;



                                            // G L O B A L   V A R I A B L E S 
//Game Frame Dimensions
const int frameWidth = 100;
const int frameHeight = 25;

int splashScreenRefresh = 4; //Duration of the Splash Screen 


int mainMenuUserInput = 0;  //Store the users Input from thew Main Menu,


                                    // G L O B A L I Z E   A L L  F U N C T I O N S
void gameFrame();          //Draw the Game Frame
void mainMenu();           //Main Menu Configurations
void splashScreen();       //Splash Screen Design for the Game



                                                    // F U N C T I O N S 
void gameFrame(){//AKILA
    for(int i = 0; i < frameWidth; i++) cout <<"-";
    cout << endl;
    for(int j = 0;j < frameHeight; j++){
        cout <<"|";
        cout << setw(frameWidth - 1);
        cout << "|" << endl;
    }
    for(int k = 0; k < frameWidth; k++) cout <<"-";
}

void mainMenu(){//AKILA
    cout << "Game Menu";
    cout << "1 - New Game, 2 - Scores, 3 - Instructions, 4 - Credits,  5 - Exit ";
    cin >> mainMenuUserInput;
    switch(mainMenuUserInput){
        case (1): cout << "Hello";  //New Game Connection
        case (2): cout << "Hello"; //Score List Connection
        case (3): cout << "Hello"; //Instruction Connection
        case (4): cout << "Hello"; //Credits Connection
        case (5): cout << "Hello"; //Exit Connection
        default:
            cout << "Enter a valid Input" << endl; 
            cin >> mainMenuUserInput;

        
    }
}

void splashScreen(){
    cout << "Hello I am the Splash Screen"; 


    this_thread::sleep_for(chrono::seconds(splashScreenRefresh));  //sleep console for specified time
    system("cls");
    mainMenu(); //link to mainMenu Function

}





int main(){
    //gameFrame();
    splashScreen();
    return(0);
}
