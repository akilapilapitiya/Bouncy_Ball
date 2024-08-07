                                            // L I B R A R Y   I M P O R T S
#include <iostream> 
#include <iomanip>         //Outputs adjustments
#include <thread>          //For Code Sleep
#include <chrono>          //To make the code sleep
#include <cstdlib>         // For system()
#include <fstream>         //File Handling
#include <cstring>         //String Manipulations
#include <conio.h>         // Include the conio.h header for _kbhit() and _getch() (to control the ball accotding to inputs)
using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------

                                            // G L O B A L   V A R I A B L E S 

const int frameWidth = 100;     //Game Frame Width Dimensions
const int frameHeight = 25;     //Game Frame Height Dimensions
int splashScreenRefresh = 4;    //Duration of the Splash Screen 
int mainMenuUserInput = 0;      //Store the users Input from thew Main Menu
string valueStore;              //Used in File Read to get User Scores

// Define directions using an enumeration (BENARAGAMA)
enum eDirect
{
    STOP = 0,
    UP,
    DOWN
};
// Declare direction variable
eDirect dir;


bool gameOver;      //check whether game is ended or not(Chanuka)
int moveUp;         //moving ball upwards
int moveDown;       //moving ball downwards
//----------------------------------------------------------------------------------------------------------------------------------------------

                                    // G L O B A L I Z E   A L L  F U N C T I O N S

void gameFrame();          //Draw the Game Frame
int mainMenu();            //Main Menu Configurations
void returnToMainMenu();   //Function to Return to the Main Menu from Menu Elements
void splashScreen();       //Splash Screen Design for the Game
void creditsPage();        //Credits Page from main Menu
int scoreFileReader();     //Reads the file used to store Scores
void gameInstructions();   //Instruction Page for the game
void input();              // Function to handle keyboard input
int ingameLogic();         //Control newgame Functions 
int gameDraw();            //Draw the Game


//---------------------------------------------------------------------------------------------------------------------------------------------

                                                    // F U N C T I O N S 

// FUNCTION to draw the game Frame (Inputs defined: GLOBAL frameWidth, GLOBAL frameHeight)                                                    
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

// FUNCTION to display and configure the main menu (Inputs taken from user to GLOBAL mainMenuUserInput)
int mainMenu(){//AKILA
    system("cls");
    cout << "Game Menu" << endl;
    cout << "1 - New Game \n 2 - Scores \n3 - Instructions \n4 - Credits \n5 - Exit ";
    cin >> mainMenuUserInput;
    switch(mainMenuUserInput){
        case (1): ingameLogic();              //New Game Connection
        case (2): scoreFileReader();            //Score List Connection
        case (3): gameInstructions();           //Instruction Connection
        case (4): creditsPage();                //Credits Connection
        case (5): break;                        //Exit Connection
        default:
            cout << "Enter a valid Input" << endl; 
            cin >> mainMenuUserInput;       
    }
    return(0);
}

//FUNCTION to handle the returns from the main menu (Inputs taken from user to GLOBAL mainMenuUserInput)
void returnToMainMenu(){//AKILA
    cout << "\n";
    cout << "Enter 0 to return to main Menu" ;
    cin  >> mainMenuUserInput;
    while(mainMenuUserInput != 0){                  //If user inputs an invalid input
        cout << "Enter a valid Input" ;
        cin  >> mainMenuUserInput;
    }
    if(mainMenuUserInput == 0){                     //Return logic to the main menu
        mainMenu();                                 //link to mainMenu Function
    }
}

// FUNCTION to display the splash screen
void splashScreen(){//AKILA
    for(int i = 0; i < frameWidth; i++) cout <<"-";
    cout << endl;
    
    cout << "                                                                                                  " << endl;
    cout << "       BTTTTTTTTTTTTb                        BALl     EBAl                                        " << endl;
    cout << "       BALLBOUNCEBALLBb                      BALl     EBAl                                        " << endl;
    cout << "       BALl        )LBOb                     BALl     EBAl                                        " << endl;
    cout << "       BALl       )LLBOp                     BALl     EBAl                                        " << endl;
    cout << "       BALLBOUNCEBALLp      TTOTTTTDT0       BALl     EBAl                                        " << endl;
    cout << "       BALLBOUNCEBALLb      LBBALLBOUNl      BALl     EBAl                                        " << endl;
    cout << "       BALl       )LLBOb            UNl      BALl     EBAl                                        " << endl;
    cout << "       BALl        )LBOU    LBBALLBOUNl      BALl     EBAl                                        " << endl;
    cout << "       BALLBOUNCEBALLBOp    LBB     UNl      BALb     EBAb                                        " << endl;
    cout << "       BALLBOUNCEBALLB0     LBBALLBOUNC0     BALBl    EBALl                                       " << endl;
    cout << "                                                                                                  " << endl;
    cout << "                                                                                                  " << endl;
    cout << "       BALLBOUNCEBALb                                                                             " << endl;
    cout << "       BALLBOUNCEBALLBb                                                                           " << endl;
    cout << "       BALL         LBOb                                                                          " << endl;
    cout << "       BALL        LLBOp                             LLBO0                                        " << endl;
    cout << "       BALLBOUNCEBALLp     LLBBALLBOU   BALl    LLBl   lCE0 0LBBA     NCEBALLBBA    UNCEBALLBB0   " << endl;
    cout << "       BALLBOUNCEBALLb    lLLB    BOUN  BALl    LLBl   lCEBALLBBALl   UNCE   LBBA   OUN     LBBl  " << endl;
    cout << "       BALL        LLBOb  lLLB    BOUN  BALl    LLBl   lCEB    BALl   UNC           OUN     LBB0  " << endl;
    cout << "       BALL         LBOU  lLLB    BOUN  BALl    LLBl   lCEB    BALl   UNC           OUNCEBALLB0   " << endl;
    cout << "       BALLBOUNCEBALLBOp  lLLB   LBOUN  BALL0  ALLBl   lCEB    BALl   UNCE   LBBA   OUN0          " << endl;
    cout << "       BALLBOUNCEBALLBp    0LBBALLBOU    0ALLBBALL0    lCEB    BALl    NCEBALLBBA    UNCEBALLBB   " << endl;
    cout << "                                                                                                  " << endl;
    cout << "                                                                                                  " << endl;

    for(int k = 0; k < frameWidth; k++) cout <<"-";
    this_thread::sleep_for(chrono::seconds(splashScreenRefresh));    //sleep console for specified time
    mainMenu();                                                      //link to mainMenu Function

}

//FUNCTION to handle the credits window
void creditsPage(){//AKILA
    system("cls");                              //Clear the terminal
    cout << "Ball Bounce" << endl;
    cout << "";
    returnToMainMenu();                         //Connection to main menu function
}

//FUNCTION to handle the score card window
int scoreFileReader(){//AKILA
    system("cls");                              //Clear the terminal
    cout << "Display Scorecard";
    fstream readFile;                           //Read File Variable Defined
    readFile.open("score.txt", ios::in);        //open "score.txt"
    if(!readFile.is_open()){                    //check if the file is open
        cout << "Error In Opening the File";    //Statement if the file is not open
        return(0);                              //Exit program if file is not open
    }
    readFile.close();                           //Close file reader
    returnToMainMenu();                         //Connection to main menu function
    return(0);                                  //Useless return for code completemess
}

// FUNCTION to handle the game instructions window
void gameInstructions(){//AKILA
    system("cls");                              //Clear the terminal
    cout << "Display Game Instructions";
    returnToMainMenu();                         //Connection to main menu function
}

// FUNCTION to handle keyboard input (BENARAGAMA)
void input(){//BENARAGAMA
    if (_kbhit())                               // Check if a key has been pressed
    {
        char key = _getch();                    // Get the pressed key
        switch (key)                            // Determine the action based on the key
        {
            case 'w':
                dir = UP;                       // Move up
                break;
            case 's':
                dir = DOWN;                     // Move down
                break;
            default:
                break;                          // Do nothing for other keys
        }
        // Clear the input buffer to avoid multiple triggers from the same key press
        while (_kbhit())
        {
            key = _getch();
        }
    }
    else
    {
        dir = STOP;                             // Stop movement if no key is pressed
    }
}


//-----------------------------------------------------------------------------------------------------------








int ingameLogic(){//CHANUKA
    switch (dir)
    {
    case UP:                    //Move up
        moveUp++;
        break;
    case DOWN:                  //Move down
        moveDown++;
        break;
    default:
        break;
    }

    return(0);    
}


int gameDraw(){//CHANUKA

    int ballPushDistance = 20;

    cout <<setw(ballPushDistance) <<" ";
    cout << setw(10)<< "   ,@@@@," <<endl;
    cout <<setw(ballPushDistance) <<" ";
	cout <<setw(10)<< "  ,@@@@@@@@," <<endl;
    cout <<setw(ballPushDistance) <<" ";
	cout <<setw(10)<< "  @@@@@@@@@@" <<endl;
    cout <<setw(ballPushDistance) <<" ";
	cout <<setw(10)<< "  '@@@@@@@@'" <<endl;
    cout <<setw(ballPushDistance) <<" ";
	cout <<setw(10)<< "    '@@@@'" <<endl;


    return(0);
}





//-----------------------------------------------------------------------------------------------------------------------------------------------

int main(){
    //gameFrame();
    //splashScreen();
    gameDraw();

    /*while (!gameOver)//until gameOver game will run
	{
		mainMenu();
	}
    return(0);*/
}
