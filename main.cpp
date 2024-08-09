//                                              L I B R A R Y   I M P O R T S
#include <iostream> 
#include <iomanip>         //Outputs adjustments
#include <thread>          //For Code Sleep
#include <chrono>          //To make the code sleep
#include <cstdlib>         // For system()
#include <fstream>         //File Handling
#include <string>         //String Manipulations
#include <sstream>          //File handling brak of characters
#include <conio.h>         //for _kbhit() and _getch() (to control the ball according to inputs)
using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------

//                                            G L O B A L   C O N S T A N T S
// GAME RELATED  DIMENSION
const int frameWidthConstant = 100;                 //Game Frame Width Dimensions
const int frameHeightConstant = 25;                 //Game Frame Height Dimensions
const int gameBodyHeightConstant = 23;              //Height of play area including the floor   
const int ballHeightConstant = 5;                   //Height of the Ball
const int ballIdlePositionFromTop = 18;             //At game start the ball is draw under this number of lines
const int obstaclePositionFromTopConstant = 19;     //All throughout the game obstacle start draw after these number of lines

const int ballPositionFromLeftConstant = 20;        //Distance to the ball From the left wall
const int ballWidthConstant = 10;                   //Width of the ball
const int obstacleWidthConstant = 7;                //Width of the Obstacle


//GAME RELATED

//Ball Draw Array
string drawBall[] = {"  ,@@@@,  ",     //drawBall[0]
                     ",@@@@@@@@,",     //drawBall[1]
                     "@@@@@@@@@@",     //drawBall[2]
                     "'@@@@@@@@'",     //drawBall[3]
                     "  '@@@@'  "};    //drawBall[4]

//Obstacle Draw Array
string drawObstacle[] = {"   A   ",    //drawObstacle[0]
                         "  AAA  ",    //drawObstacle[1]
                         " AAAAA ",    //drawObstacle[2]
                         "AAAAAAA"};   //drawObstacle[3]

//Game Draw related Constants
const bool gameOverStatusConstant = false;              //Game over status set to false by Default
const int sleepTimeConstant = 300;                      //Ingame Console Refresh time in milli seconds
const int obstacleMoveRate = 4;                         //Rate at which the obstacle Moves to left

//Obstacle and Ball draw RESET constants
const int dynamicDistanceAdjustConstant = 60;           //Initial Distance Between the Ball and Obstacle
const int ballPositionFromTopConstant = 17;             //At startup Ball Position   DEFAULT :: 17 (do not exceed)
const int dynamicDistanceAdjustNegetiveConstant = 30;   //Initial Distance between left wall and the obstacle when dynamicDistanceAdjust == 0


//Ball Related Controls
const int maximumHeightTheBallCanMoveConstant = 2;      //Maximum height the ball is allowed to move
const int ballMoveUpToKeyPressConstant = 3;             //With each Keypress number of lines the ball moves up 
const int ballFallRateConstant = 2;                     //Rate in which the ball falls down


//Player Management and Score Maps
const int gameScoreIncrementConstant = 1;               //Increment of score for avoiding a single Obstacle
const int gameScoreReset = 0;                           //Reset Value for the Game Score
const string playerNameReset = "";                      //Reset Value for Player name
const int numberOfPlayersExpectedConstant = 10;         //Size of the playerStatArray

//Global Structure named playerStats
struct playerStats{
    string playerName;
    int playerScore;
};
struct playerStats playerStatArray[numberOfPlayersExpectedConstant];    //Assign the Structure to an array for data storing


//------------------------------------------------------------------------------------------------------------------

//                                            G L O B A L   V A R I A B L E S 
// MENU RELATED
int splashScreenRefresh = 4;    //Duration of the Splash Screen Sleep time
int mainMenuUserInput = 0;      //Store the users Input from thew Main Menu
string valueStore;              //Used in File Read to get User Scores


//GAME RELATED

// Keyboard Mapping Directions
enum eDirect{
    STOP = 0,
    UP,
    DOWN
};

// Declare direction variable
eDirect dir;

// Game draw related dynamic Variables
bool gameOverStatus;                //Variable to store the game over status
int dynamicDistanceAdjust;          //Variable to store Distance between Ball and Obstacle
int ballPositionFromTop;            //Variable to store Position of the ball Fram top         
int dynamicDistanceAdjustNegetive;  //Variable to store the distancve between left wall and the obstacle when dynamicDistanceAdjust == 0

//Player Management and Score Maps
int gameScore; 
string playerName;


//----------------------------------------------------------------------------------------------------------------------------------------------

//                                  G L O B A L I Z E   A L L  F U N C T I O N S


// MENU RELATED
void gameFrame();          //Draw the Game Frame
int mainMenu();            //Main Menu Configurations
void returnToMainMenu();   //Function to Return to the Main Menu from Menu Elements
void splashScreen();       //Splash Screen Design for the Game
void creditsPage();        //Credits Page from main Menu
int scoreFileReader();     //Reads the file used to store Scores
void gameInstructions();   //Instruction Page for the game



//GAME LOGIC RELATED
int gameInitialize();                   //main Menu Connect for new Game
void gameVariableResetFunction();       //Resets all variable Data for a new Game
void input();                           //Function to handle keyboard input
void keyBoardLogic();                   //Function to bind ingame Actions with Keyboard logics
int gameDraw();                         //Draw the Game in all Instances
void ballFall();                        //Make the Ball Fall Down
void gameOverDisplay();                 //Game Over Prompt with menu Includes
int dataWriteFunction();               //Function to write the user data to the file


//---------------------------------------------------------------------------------------------------------------------------------------------

//                                M E N U   R E L A T E D   F U N C T I O N S 

// FUNCTION to draw the game Frame                  (Inputs defined: GLOBAL frameWidthConstant, GLOBAL frameHeightConstant)                                                    
void gameFrame(){//AKILA
    for(int i = 0; i < frameWidthConstant; i++) cout <<"-";
    cout << endl;
    for(int j = 0;j < frameHeightConstant; j++){
        cout <<"|";
        cout << setw(frameWidthConstant - 1);
        cout << "|" << endl;
    }
    for(int k = 0; k < frameWidthConstant; k++) cout <<"-";
}

// FUNCTION to display and configure the main menu  (Inputs taken from user to GLOBAL mainMenuUserInput)
int mainMenu(){//AKILA
    system("cls");
    cout << "Game Menu" << endl;
    cout << "1 - New Game \n 2 - Scores \n3 - Instructions \n4 - Credits \n5 - Exit ";
    cin >> mainMenuUserInput;
    switch(mainMenuUserInput){
        case (1): gameInitialize();                //New Game Connection
        case (2): scoreFileReader();            //Score List Connection
        case (3): gameInstructions();           //Instruction Connection
        case (4): creditsPage();                //Credits Connection
        case (5): return(0);                        //Exit Connection
        default:
            cout << "Enter a valid Input" << endl; 
            cin >> mainMenuUserInput;       
    }
    return(0);
}

//FUNCTION to handle the returns from the main menu     (Inputs taken from user to GLOBAL mainMenuUserInput)
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
    for(int i = 0; i < frameWidthConstant; i++) cout <<"-";
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

    for(int k = 0; k < frameWidthConstant; k++) cout <<"-";
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


//-----------------------------------------------------------------------------------------------------------

//                                I N G A M E    F U N C T I O N S


//Function to Initialize the Game
int gameInitialize(){//AKILA

    //Call the reset Function
    gameVariableResetFunction();
    
    //Draw an interface to Get users Name
    // Input User name to store marks
    //On completion, call the game logic system
    cout << "Enter Player Name: ";
    cin >> playerName;
    system("cls");



    //Game loop
    while(!gameOverStatus){
        gameDraw();                                                         //Call the GameDraw Function
        this_thread::sleep_for(chrono::milliseconds(sleepTimeConstant));    //Set the refresh time for console (sleep time)
        if(dynamicDistanceAdjust > 0){                                      //Condition if the obstacle is right to the ball
            dynamicDistanceAdjust -= obstacleMoveRate;                      //Move the obstacle left
        }else if(dynamicDistanceAdjustNegetive > 2){                        //Condition if the obstacle is under or left of ball
            dynamicDistanceAdjustNegetive -= obstacleMoveRate;              //Move the obstacle left
        }
        input();                                                            //Call the inputs function
        keyBoardLogic();                                                    //Call the keyboard logic function
        ballFall();                                             //Call the Function to make the Ball Fall

        //Conditions to loop the game and Mark the scores
        if((dynamicDistanceAdjust == 0) && (dynamicDistanceAdjustNegetive == 2)){
            dynamicDistanceAdjust = dynamicDistanceAdjustConstant;                 //Reset dynamicDistanceAdjust to default
            dynamicDistanceAdjustNegetive = dynamicDistanceAdjustNegetiveConstant; //Reset dynamicDistanceAdjustNegetive to default
            gameScore += gameScoreIncrementConstant;                               //Increment the Game Score by desires
        }
        system("cls");                                          //Refresh the Console
    }
    gameOverDisplay();                                          //Call the game Over Function
    return(0);
}

//FUNCTION to reset variables to a new game
void gameVariableResetFunction(){
    //New Game Resets
    gameOverStatus = gameOverStatusConstant;                    // Preset the Game Over Status

    dynamicDistanceAdjust = dynamicDistanceAdjustConstant;      //Reset the Dynamic Distance Adjust for new Game
    ballPositionFromTop = ballPositionFromTopConstant;          //Reset the Position of the ball From the top
    dynamicDistanceAdjustNegetive = dynamicDistanceAdjustNegetiveConstant;   //Reset the Dynamic Distance Adjust Negetive for new Game

    //Player Info Resets
    playerName = playerNameReset;                   //Reset thePlayer Name to NULL
    gameScore = gameScoreReset;                     //Reset the game score to 0

}

// FUNCTION to handle keyboard input
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

//FUNCTION to control logic with keyboard Inputs
void keyBoardLogic(){//CHANUKA
    if(ballPositionFromTop > maximumHeightTheBallCanMoveConstant){
        switch (dir) {
            case UP:                           // Move up
                ballPositionFromTop -= ballMoveUpToKeyPressConstant;
                break;
        }
    }

}

//FUNCTION to draw the game in all 3 Instances
int gameDraw(){//AKILA
    //When the obstacle is in right of the ball
    if (dynamicDistanceAdjust > 0){
        for(int i = 0; i < gameBodyHeightConstant; i++){
            if(i > ballPositionFromTop){
                if((i - (ballPositionFromTop)) <= ballHeightConstant){
                    cout << left << setw(ballPositionFromLeftConstant) << "" << setw(ballWidthConstant) << drawBall[i - (ballPositionFromTop + 1)];   
                }else{
                    cout << left << setw(ballPositionFromLeftConstant + ballWidthConstant) << "";
                }
                if(i > ballIdlePositionFromTop){
                    cout << setw(dynamicDistanceAdjust) << "" << setw(obstacleWidthConstant) << drawObstacle[i - (obstaclePositionFromTopConstant)];
                } 
                cout << endl;        
            }else{
                cout << endl;
            }
        }
    }
    //When the distance between Obstacle and Ball is 0 || When the obstable is under the ball
    if(dynamicDistanceAdjust == 0){
        //Collsion Exit
        if((ballPositionFromTop > 12) && (dynamicDistanceAdjustNegetive == 30)){
            gameOverStatus = true;                  //Since there is a collision change game over bool value to true
            return(0);                              //Break the function
        }
        ///To be changed
        if((ballPositionFromTop > 12) && (dynamicDistanceAdjustNegetive != 30)){
            for (int i = 0; i < gameBodyHeightConstant; i++){
                if(i <= ballIdlePositionFromTop){
                cout << left << setw(obstacleWidthConstant + dynamicDistanceAdjustNegetive) << "";
                }
                if(i > ballIdlePositionFromTop){
                    cout << left << setw(dynamicDistanceAdjustNegetive) << "" << setw(obstacleWidthConstant) << drawObstacle[i - 19];
                 }   
                if(i - (ballPositionFromTop + 1) < ballHeightConstant){
                    cout << left << setw(ballPositionFromLeftConstant - (dynamicDistanceAdjustNegetive + obstacleWidthConstant)) << "" << setw(ballWidthConstant) << drawBall[i - (ballPositionFromTop + 1)] << endl;
                }else{
                    cout << endl;
                }
            }
        }

        if(ballPositionFromTop <= 12){
            for(int i  = 0; i < gameBodyHeightConstant; i++){
                //No collsion
                if(i - (ballPositionFromTop + 1) <= ballHeightConstant ){
                    cout << left << setw(ballPositionFromLeftConstant) << "" << setw(ballWidthConstant) << drawBall[i - (ballPositionFromTop + 1)] << endl;
                }

                if((i > (ballPositionFromTop + ballHeightConstant)) && (i <= ballIdlePositionFromTop)){
                    cout << endl;
                }
                 
                if(i > 18){
                cout << left << setw(dynamicDistanceAdjustNegetive) << "" << setw(obstacleWidthConstant) << drawObstacle[i - obstaclePositionFromTopConstant] << endl;
                }
            }       
        }    
    }
    //Draw the Game Floor
    for (int i = 0; i < frameWidthConstant; i++)cout << "-";

    return(0);
}

//FUNCTION to make the ball Fall Down
void ballFall(){//AKILA
    if(ballPositionFromTop >= 16){
    }else{
        ballPositionFromTop += ballFallRateConstant;
    }

}

//FUNCTION to act in Game Over Instance
void gameOverDisplay(){//AKILA
    system("cls");
    cout << "game Over" << endl;
    cout << "Your Score is: " << gameScore;
    dataWriteFunction();            //Call Function to Write the data to the file
    gameVariableResetFunction();    //Call Function to Reset All Dynamic Data
    returnToMainMenu();             //Call Function to Return to main Menu



}

// FUNCTION to save user data and Scores 
int dataWriteFunction(){
    fstream fileWriter;
    fileWriter.open("score.txt", ios::app);
    if(!fileWriter.is_open()){
        cout << "Error in opening the file " << endl;
        return(0);    
    }
    fileWriter << playerName << "," << gameScore;
    fileWriter << endl;
    fileWriter.close();
    return(0);
}






//-----------------------------------------------------------------------------------------------------------------------------------------------

int main(){

    //gameFrame();
    splashScreen();
    //gameInitialize();

   return (0); 
}
