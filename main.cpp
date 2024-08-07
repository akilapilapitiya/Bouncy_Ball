                                            // L I B R A R Y   I M P O R T S
#include <iostream> 
#include <iomanip>
#include <thread>          //For Code Sleep
#include <chrono>          //To make the code sleep
#include <cstdlib>         // For system()
#include <fstream>         //File Handling
#include <cstring>
#include <conio.h> // Include the conio.h header for _kbhit() and _getch() (to control the ball accotding to inputs)
using namespace std;



                                            // G L O B A L   V A R I A B L E S 
//Game Frame Dimensions
const int frameWidth = 100;
const int frameHeight = 25;

int splashScreenRefresh = 4; //Duration of the Splash Screen 


int mainMenuUserInput = 0;  //Store the users Input from thew Main Menu


string valueStore;         //Used in File Read to get User Scores

// Define directions using an enumeration (benaragamaa)
enum eDirect
{
    STOP = 0,
    UP,
    DOWN
};
// Declare direction variable
eDirect dir;


                                    // G L O B A L I Z E   A L L  F U N C T I O N S

void gameFrame();          //Draw the Game Frame
int mainMenu();            //Main Menu Configurations
void returnToMainMenu();   //Function to Return to the Main Menu from Menu Elements
void splashScreen();       //Splash Screen Design for the Game
void creditsPage();        //Credits Page from main Menu
int scoreFileReader();    //Reads the file used to store Scores
void gameInstructions();   //Instruction Page for the game
void input();// Function to handle keyboard input 


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

int mainMenu(){//AKILA
    system("cls");
    cout << "Game Menu";
    cout << "1 - New Game, 2 - Scores, 3 - Instructions, 4 - Credits,  5 - Exit ";
    cin >> mainMenuUserInput;
    switch(mainMenuUserInput){
        case (1): cout << "Hello";  //New Game Connection
        case (2): scoreFileReader(); //Score List Connection
        case (3): gameInstructions(); //Instruction Connection
        case (4): creditsPage(); //Credits Connection
        case (5): break; //Exit Connection
        default:
            cout << "Enter a valid Input" << endl; 
            cin >> mainMenuUserInput;       
    }
}

void returnToMainMenu(){//AKILA
    cout << "\n";
    cout << "Enter 0 to return to main Menu" ;
    cin  >> mainMenuUserInput;
    while(mainMenuUserInput != 0){
        cout << "Enter a valid Input" ;
        cin  >> mainMenuUserInput;
    }
    if(mainMenuUserInput == 0){
        mainMenu(); //link to mainMenu Function
    }
}

void splashScreen(){//AKILA
    for(int i = 0; i < frameWidth; i++) cout <<"-";
    cout << endl;
    
    cout << "|" << "                                                                                                  " << "|" << endl;
    cout << "|" << "       BALLBOUNCEBALb                        BALl     EBAl                                        " << "|" << endl;
    cout << "|" << "       BALLBOUNCEBALLBb                      BALl     EBAl                                        " << "|" << endl;
    cout << "|" << "       BALl        )LBOb                     BALl     EBAl                                        " << "|" << endl;
    cout << "|" << "       BALl       )LLBOp                     BALl     EBAl                                        " << "|" << endl;
    cout << "|" << "       BALLBOUNCEBALLp      LBBALLBOUNl      BALl     EBAl                                        " << "|" << endl;
    cout << "|" << "       BALLBOUNCEBALLb      LBBALLBOUNl      BALl     EBAl                                        " << "|" << endl;
    cout << "|" << "       BALl       )LLBOb            UNl      BALl     EBAl                                        " << "|" << endl;
    cout << "|" << "       BALl        )LBOU    LBBALLBOUNl      BALl     EBAl                                        " << "|" << endl;
    cout << "|" << "       BALLBOUNCEBALLBOp    LBB     UNl      BALb     EBAb                                        " << "|" << endl;
    cout << "|" << "       BALLBOUNCEBALLBp     LBBALLBOUNCEb    BALBl    EBALl                                       " << "|" << endl;
    cout << "|" << "                                                                                                  " << "|" << endl;
    cout << "|" << "                                                                                                 " << "|" << endl;
    cout << "|" << "       BALLBOUNCEBALb                                                                             " << "|" << endl;
    cout << "|" << "       BALLBOUNCEBALLBb                                                                           " << "|" << endl;
    cout << "|" << "       BALL         LBOb                                                                          " << "|" << endl;
    cout << "|" << "       BALL        LLBOp                             LLBO0                                        " << "|" << endl;
    cout << "|" << "       BALLBOUNCEBALLp     LLBBALLBOU   BALl    LLBl   lCE0 0LBBA     NCEBALLBBA    UNCEBALLBB0   " << "|" << endl;
    cout << "|" << "       BALLBOUNCEBALLb    lLLB    BOUN  BALl    LLBl   lCEBALLBBALl   UNCE   LBBA   OUN     LBBl  " << "|" << endl;
    cout << "|" << "       BALL        LLBOb  lLLB    BOUN  BALl    LLBl   lCEB    BALl   UNC           OUN     LBB0  " << "|" << endl;
    cout << "|" << "       BALL         LBOU  lLLB    BOUN  BALl    LLBl   lCEB    BALl   UNC           OUNCEBALLB0   " << "|" << endl;
    cout << "|" << "       BALLBOUNCEBALLBOp  lLLB   LBOUN  BALL0  ALLBl   lCEB    BALl   UNCE   LBBA   OUN0          " << "|" << endl;
    cout << "|" << "       BALLBOUNCEBALLBp    0LBBALLBOU    0ALLBBALL0    lCEB    BALl    NCEBALLBBA    UNCEBALLBB   " << "|" << endl;
    cout << "|" << "                                                                                                  " << "|" << endl;
    cout << "|" << "                                                                                                  " << "|" << endl;

    for(int k = 0; k < frameWidth; k++) cout <<"-"; 


    this_thread::sleep_for(chrono::seconds(splashScreenRefresh));  //sleep console for specified time
    mainMenu(); //link to mainMenu Function

}


void creditsPage(){//AKILA
    system("cls");
    cout << "Ball Bounce" << endl;
    cout << ""
    returnToMainMenu(); 
}


int scoreFileReader(){//AKILA
    system("cls");
    cout << "Display Scorecard";
    fstream readFile;
    readFile.open("score.txt", ios::in);
    if(!readFile.is_open()){
        cout << "Error In Opening the File";
        return(0);
    }
    readFile.close();
    returnToMainMenu();
}

void gameInstructions(){
    system("cls");
    cout << "Display Game Instructions";
    returnToMainMenu();
}

// Function to handle keyboard input (benaragama)
void input()
{
    if (_kbhit()) // Check if a key has been pressed
    {
        char key = _getch(); // Get the pressed key
        switch (key) // Determine the action based on the key
        {
            case 'w':
                dir = UP; // Move up
                break;
            case 's':
                dir = DOWN; // Move down
                break;
            default:
                break; // Do nothing for other keys
        }
        // Clear the input buffer to avoid multiple triggers from the same key press
        while (_kbhit())
        {
            key = _getch();
        }
    }
    else
    {
        dir = STOP; // Stop movement if no key is pressed
    }
}




int main(){
    //gameFrame();
    splashScreen();
    return(0);
}
