//                                              L I B R A R Y   I M P O R T S
#include <iostream> 
#include <iomanip>         //Outputs adjustments
#include <thread>          //For Code Sleep
#include <chrono>          //To make the code sleep
#include <windows.h>       //For String Colours    used in design Functions
#include <cstdlib>         // For system()
#include <fstream>         //File Handling
#include <string>          //String Manipulations
#include <sstream>         //File handling brak of characters
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


//Obstacle and Ball draw RESET constants
const int dynamicDistanceAdjustConstant = 60;           //Initial Distance Between the Ball and Obstacle
const int ballPositionFromTopConstant = 17;             //At startup Ball Position   DEFAULT :: 17 (do not exceed)
const int dynamicDistanceAdjustNegetiveConstant = 30;   //Initial Distance between left wall and the obstacle when dynamicDistanceAdjust == 0

// Game Time Related Constants
const bool timeOutStatusConstant = false;                     //Default time out Status
const int gameTimeReset = 0;                            //RESETS the Game Time
const int gameplayTimeUpdater = 30;                     //Gameplay time in Seconds(Try to add values divisible by sleepTimeConstant)
const int gameplayTimeConstant = (gameplayTimeUpdater * 1000);  //Convert gameplay time seconds to milliseconds

//Ball Related Controls
const int maximumHeightTheBallCanMoveConstant = 2;      //Maximum height the ball is allowed to move
const int ballMoveUpToKeyPressConstant = 3;             //With each Keypress number of lines the ball moves up 
const int ballFallRateConstant = 2;                     //Rate in which the ball falls down


//Player Management and Score Maps
const int gameScoreIncrementConstant = 5;               //Increment of score for avoiding a single Obstacle
const int gameScoreBonusConstant = 1;                   //Bonus for keeping the ball on the ground
const int gameScoreReset = 0;                           //Reset Value for the Game Score
const string playerNameReset = "";                      //Reset Value for Player name
const int numberOfPlayersExpectedConstant = 10;         //Size of the playerStatArray
const bool highScoreStatusConstant = false;             //Reset the high score status to false

//Global Structure named playerStats
struct playerStats{
    string playerName;
    int playerScore;
};
struct playerStats playerStatArray[numberOfPlayersExpectedConstant + 1];    //Assign the Structure to an array for data storing


// Global Constants to controll gameplay Speeds(Relative to game Scores)
const int obstacleMoveRateConstant = 4;                         //Rate at which the obstacle Moves to left RESET value

int gameSpeedControllArray[] = {20,     //gameSpeedControllArray[0]  First Speed Increment
                                40,     //gameSpeedControllArray[1]  Second Speed Increment
                                60};     //gameSpeedControllArray[2]  Third Speed Increment

const int gameSpeedControlPointerConstant = 0; //Reset check loop value to zero
const int speedDeltaConstant = 4;               //Rate of change in obstacle movement speed


//Colors for Designer
const int whiteColor = 7;
const int yellowColor = 6;
const int redColor = 4;
const int greenColor = 2;
const int greyColor = 8;
const int blueColor = 3;
const int pinkColor = 13;



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
int gameScore;                      //Ingame Variable to store the players score
string playerName;                  // Ingame Variable to store the players name
bool highScoreStatus;               //Variable to handle the High Score Status

//Game Time Controls and Reset Functionality
bool timeOutStatus;                       //Variable to sotre timeout status
int gameTime;                       //Time the Game is Played
int remainingTime;                  //Time Left to play

// Global Variables to controll gameplay Speeds(Relative to game Scores)
int gameSpeedControlPointer;        //Variable to locate Array Vaslues in the game speed changer array
int obstacleMoveRate;               //Variable to control the Rate in which the obstacles Move


//Score File Read Related
string nameStoreVariable;           //Used to ssstream the values in file reading [playername]
int scoreStoreVariable;             //Used to ssstream the values in file reading [playerscore]

//Marks Sorting Dummy Variables
string nameStoreDummyVariable;      //Used to store the name while sorting the scores in descending order
int scoreStoreDummyVariable;        //Used to store the name while sorting the scores in descending order



//----------------------------------------------------------------------------------------------------------------------------------------------

//                                  G L O B A L I Z E   A L L  F U N C T I O N S


// MENU RELATED
void gameFrame();           //Draw the Game Frame
int mainMenu();             //Main Menu Configurations
void returnToMainMenu();    //Function to Return to the Main Menu from Menu Elements
void splashScreen();        //Splash Screen Design for the Game
void creditsPage();         //Credits Page from main Menu
int scoreDisplay();         //Display Scores
void gameInstructions();    //Instruction Page for the game

//GAME LOGIC RELATED
int gameInitialize();                   //main Menu Connect for new Game
void gameVariableResetFunction();       //Resets all variable Data for a new Game
void input();                           //Function to handle keyboard input
void keyBoardLogic();                   //Function to bind ingame Actions with Keyboard logics
void timeHandler();                     //Function to Control Game Played Time
int gameDraw();                         //Draw the Game in all Instances
void ballFall();                        //Make the Ball Fall Down
void gamePhaseChanger();                //Change the game spped based on the marks gained
void gameOverDisplay();                 //Game Over Prompt with menu Includes
int dataWriteFunction();                //Function to write the user data to the file
int highScoreIdentifier();              //Identify if the last upadted score is the highest score

//GAME STARTUP FUNCTIONS
int gameStartUp();                     //All Tasks Handled At Game Start
void fileCreateFunction();             //Create 'score.txt' if it does not exist
int scoreFileReader();                 //Read the Score File and Update the array
void scoreArraySort();                 //Sort the ScoreArray in descending order

//DRAW FUNCTIONS
void splashScreenDraw();                //Splash Screen Design
void gameMenuScreenDraw();              //Game menu Design
void gameOverInterface();               //Game Over Display Design
void instructionInterface();            //Instructions Interface Design 
void scoreDisplayInterface();           //Draw player Scores
void highScoreGameOverInterface();      //Draw High Score when Game Over
void creditsInterface();                //Draw ingame Credits display interface
void timeOutGameOverInterface();        //Draw the game over interface when there is a timeout


//TESTING FUNCTIONS
void gamePlayTestingDetails();         //inside  gameInitialize();



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
    
    gameMenuScreenDraw();
    cin >> mainMenuUserInput;

    if(mainMenuUserInput == 1){
        gameInitialize();
    }else if (mainMenuUserInput == 2){
        scoreDisplay();
    }else if (mainMenuUserInput == 3){
        gameInstructions();
    }else if (mainMenuUserInput == 4){
        creditsPage();
    }else if (mainMenuUserInput == 5){
        return(0);
    }else{
        system("cls");
        mainMenu();

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
    splashScreenDraw();
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
int scoreDisplay(){//AKILA                           
    scoreDisplayInterface();

    returnToMainMenu();
    return(0);
}

// FUNCTION to handle the game instructions window
void gameInstructions(){//benaragama
    system("cls");                              //Clear the terminal
    instructionInterface();                     //Instructions Interface Design

    returnToMainMenu();                         //Connection to main menu function
}


//---------------------------------------------------------------------------------------------------------------------

//                                I N G A M E    F U N C T I O N S


//Function to Initialize the Game
int gameInitialize(){//AKILA

    //Call the reset Function
    gameVariableResetFunction();
    
    //Draw an interface to Get users Name
    // Input User name to store marks
    //On completion, call the game logic system
    system("cls");
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
        timeHandler();                                                      //Update Game Time
        input();                                                            //Call the inputs function
        keyBoardLogic();                                                    //Call the keyboard logic function
        ballFall();                                                         //Call the Function to make the Ball Fall
        gamePhaseChanger();                                                 //Changes the Phase of Gameplay based on score
        //Conditions to loop the game and Mark the scores
        gameScore += gameScoreBonusConstant;
        if((dynamicDistanceAdjust <= 0) && (dynamicDistanceAdjustNegetive <= 2)){
            dynamicDistanceAdjust = dynamicDistanceAdjustConstant;                 //Reset dynamicDistanceAdjust to default
            dynamicDistanceAdjustNegetive = dynamicDistanceAdjustNegetiveConstant; //Reset dynamicDistanceAdjustNegetive to default
            gameScore += gameScoreIncrementConstant;                               //Increment the Game Score by desires
        }
        system("cls");                                          //Refresh the Console

        //Testing FUNCTIONS
        //gamePlayTestingDetails();
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
    gameSpeedControlPointer = gameSpeedControlPointerConstant;      //Reset the Game Speed Pointer
    obstacleMoveRate = obstacleMoveRateConstant;     //Reset the Speed in Wich the Obstacles Move
    highScoreStatus = highScoreStatusConstant;       //Reset the High Score Status to false

    //Player Info Resets
    playerName = playerNameReset;                   //Reset thePlayer Name to NULL
    gameScore = gameScoreReset;                     //Reset the game score to 0

    //Time Corrections
    timeOutStatus = timeOutStatusConstant;          //Reset Time Out Status Constant
    gameTime = gameTimeReset;                       //Reset game time
    remainingTime = gameplayTimeUpdater;            //Reset remaining time

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

//Function to Handle inGameTime
void timeHandler(){
    if(gameTime >= gameplayTimeConstant){
        timeOutStatus = true;
        gameOverStatus = true;
    }
    else{
        gameTime += sleepTimeConstant;
    }
    remainingTime = ((gameplayTimeConstant - gameTime) / 1000);

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
    if(dynamicDistanceAdjust <= 0){
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
    cout << endl;

    //Game Score Display
    cout << "SCORE: "  << setw(4)<< gameScore << setw(30) << "" << "Remaining Time: " << setw(6) << remainingTime ;

    return(0);
}

//FUNCTION to make the ball Fall Down
void ballFall(){//AKILA
    if(ballPositionFromTop >= 16){
    }else{
        ballPositionFromTop += ballFallRateConstant;
    }
}

//FUNCTION to change the game Speed
void gamePhaseChanger(){
    if( gameSpeedControllArray[gameSpeedControlPointer] == gameScore){
        obstacleMoveRate += speedDeltaConstant;
        gameSpeedControlPointer++;
    }
}

//FUNCTION to act in Game Over Instance
void gameOverDisplay(){//AKILA
    system("cls");
    dataWriteFunction();            //Call Function to Write the data to the file
    if(highScoreStatus == true){
        highScoreGameOverInterface();         //Call High Score Game Over Interface
    }else if(timeOutStatus == true){
             timeOutGameOverInterface();     //Call time Out Game Over Interface
        }else{
            gameOverInterface();       //Call Game Over Interface
    }
    returnToMainMenu();
    gameVariableResetFunction();    //Call Function to Reset All Dynamic Data
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

    scoreFileReader();                          //Read the Score File in the Array
    scoreArraySort();                           //Sort the User Details Array in Ascending Order
    highScoreIdentifier();                      //Find Whether the Score is a High Score


    return(0);
}

// FUNCTION to identify if the Score is the Highest Score
int highScoreIdentifier(){
    if(gameScore == playerStatArray[0].playerScore){
        highScoreStatus = true;
    }
    return(0);
}



//---------------------------------------------------------------------------------------------------------------------------

//                                 S T A R T U P   F U N C T I O N S

//FUNCTION for the GAME STARTUP
int gameStartUp(){
    fileCreateFunction();                        //Call thew file Create Function
    scoreFileReader();                          //Read the Score File in the Array
    scoreArraySort();                           //Sort the User Details Array in Ascending Order

    return(0);
}

//FUNCTION to Create 'score.txt' if it doesn't exist
void fileCreateFunction(){
    fstream fileCreator;
    fileCreator.open("score.txt", ios::app);
    if(!fileCreator.is_open()){
        cout << "Error in opening the File" << endl;
    }
    fileCreator.close();
}


//FUNCTION to read the Score File and Store in the Array
int scoreFileReader(){//AKILA
	fstream readFile;                           //Read File Variable Defined
    readFile.open("score.txt", ios::in);        //open "score.txt"
    if(!readFile.is_open()){                    //check if the file is open
        cout << "Error In Opening the File";    //Statement if the file is not open
        return(0);                              //Exit program if file is not open
    }
    for (int i = 0; (getline(readFile, valueStore) && (i < numberOfPlayersExpectedConstant)); i++) {
        stringstream ss(valueStore);
        // Extract the name and score from the line
        if (getline(ss, nameStoreVariable, ',') && (ss >> scoreStoreVariable)) {
            playerStatArray[i].playerName = nameStoreVariable;              //Assign the Array with the name
            playerStatArray[i].playerScore = scoreStoreVariable;            //Assign the Array with the score
        }
    }  
    readFile.close();                                                       //Close file reader

    /*
    //Performance testing
    for(int i = 0; i < (numberOfPlayersExpectedConstant); i++){
    	cout << playerStatArray[i].playerName << " and " << playerStatArray[i].playerScore << endl;
	}*/
    return(0);
    }

//Sort the Score Array in Descending Order
void scoreArraySort(){//AKILA
    for(int i = 0; i < numberOfPlayersExpectedConstant; i++){
        for(int m = i; m >= 0; m--){
            if(playerStatArray[m].playerScore < playerStatArray[m + 1].playerScore){

                //Swap the m'th set of element to dummy variables
                nameStoreDummyVariable = playerStatArray[m].playerName;
                scoreStoreDummyVariable = playerStatArray[m].playerScore;

                //Copy the set of element of (m + 1)'th set to m'th set
                playerStatArray[m].playerName = playerStatArray[m + 1].playerName;
                playerStatArray[m].playerScore = playerStatArray[m + 1].playerScore;

                //Copy the dummy data to the (m + 1)'th set
                playerStatArray[m + 1].playerName = nameStoreDummyVariable;
                playerStatArray[m + 1].playerScore = scoreStoreDummyVariable;
            }
        }
    }
    //Performance testing
    for(int i = 0; i < (numberOfPlayersExpectedConstant); i++){
    	cout << playerStatArray[i].playerName << " and " << playerStatArray[i].playerScore << endl;
    }
}



//-----------------------------------------------------------------------------------------------------------------------------------------------

int main(){

    gameStartUp();
    splashScreen();
    //gameInitialize();

   return (0); 
}



//------------------------------------------------------------------------------------------------------------------------
//                                  D E S I G N      T E M P L A T E S 


void splashScreenDraw(){
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, blueColor);
    cout<<  "_____________________________________________________________________________________________________________ " << endl;
    cout << "|                                                                                                           | " << endl;
    cout << "|       BTTTTTTTTTTTTb                        BALl     EBAl                                                 | " << endl;
    cout << "|       BALLBOUNCEBALLBb                      BALl     EBAl                                                 | " << endl;
    cout << "|       BALl        )LBOb                     BALl     EBAl                                                 | " << endl;
    cout << "|       BALl       )LLBOp                     BALl     EBAl                                                 | " << endl;
    cout << "|       BALLBOUNCEBALLp      TTOTTTTDT0       BALl     EBAl                                                 | " << endl;
    cout << "|       BALLBOUNCEBALLb      LBBALLBOUNl      BALl     EBAl                                                 | " << endl;
    cout << "|       BALl       )LLBOb            UNl      BALl     EBAl                                                 | " << endl;
    cout << "|       BALl        )LBOU    LBBALLBOUNl      BALl     EBAl                                                 | " << endl;
    cout << "|       BALLBOUNCEBALLBOp    LBB     UNl      BALb     EBAb                                                 | " << endl;
    cout << "|       BALLBOUNCEBALLB0     LBBALLBOUNC0     BALBl    EBALl                                                | " << endl;
    cout << "|                                                                                                           | " << endl;
    cout << "|                                                                                                           | " << endl;
    cout << "|       BALLBOUNCEBALb                                                                                      | " << endl;
    cout << "|       BALLBOUNCEBALLBb                                                                                    | " << endl;
    cout << "|       BALL         LBOb                                                                                   | " << endl;
    cout << "|       BALL        LLBOp                             LLBO0                                                 | " << endl;
    cout << "|       BALLBOUNCEBALLp     LLBBALLBOU   BALl    LLBl   lCE0 0LBBA     NCEBALLBBA    UNCEBALLBB0            | " << endl;
    cout << "|       BALLBOUNCEBALLb    lLLB    BOUN  BALl    LLBl   lCEBALLBBALl   UNCE   LBBA   OUN     LBBl           | " << endl;
    cout << "|       BALL        LLBOb  lLLB    BOUN  BALl    LLBl   lCEB    BALl   UNC           OUN     LBB0           | " << endl;
    cout << "|       BALL         LBOU  lLLB    BOUN  BALl    LLBl   lCEB    BALl   UNC           OUNCEBALLB0            | " << endl;
    cout << "|       BALLBOUNCEBALLBOp  lLLB   LBOUN  BALL0  ALLBl   lCEB    BALl   UNCE   LBBA   OUN0                   | " << endl;
    cout << "|       BALLBOUNCEBALLBp    0LBBALLBOU    0ALLBBALL0    lCEB    BALl    NCEBALLBBA    UNCEBALLBB            | " << endl;
    cout << "|                                                                                                           | " << endl;
    cout<<  "_____________________________________________________________________________________________________________ " << endl;
    	SetConsoleTextAttribute(h, whiteColor);
}



void gameMenuScreenDraw(){
    system("cls");
	cout<< "  _____________________________________________________________________________________________________________     " << endl;  
	cout<< " |       _____________________________________________________            ...      \\  |  /      ...            |   " << endl;
	cout<< " |      |                                                     |         .@ @ @.     \\ | /     .@ @ @.          |   " << endl;
	cout<< " |      |     G G G           A       M         M  E E E E    |        '@ @ @ @.  ___\\|/___  '@ @ @ @.         |   " << endl;
	cout<< " |      |   G       G        A A      M M     M M  E          |        '@ @ @ @.     /|\\     '@ @ @ @'         |   " << endl;
	cout<< " |      |  G                A   A     M  M   M  M  E          |         '@ @ @'     / | \\      @ @ @           |   " << endl;
	cout<< " |      |  G     G G G     A A A A    M   M M   M  E E E      |           '''      /  |  \\      '''            |   " << endl;
	cout<< " |      |  G       G G    A       A   M    M    M  E         /______________________________________________   |    " << endl;
	cout<< " |      |   G     G  G   A         A  M         M  E        /                                               |  |    " << endl;
	cout<< " |      |     G G    G  A           A M         M  E E E E /  M        M  E E E E E  N       N  U        U  |  |    " << endl;
	cout<< " |      |_________________________________________________/   M M    M M  E          N N     N  U        U  |  |    " << endl;
	cout<< " |                                                  |         M  M  M  M  E          N  N    N  U        U  |  |    " << endl;
	cout<< " |           /\\        /\\        /\\                 |         M   M    M  E E E      N   N   N  U        U  |  | " << endl;
	cout<< " |          /  \\      /  \\      /  \\                |         M        M  E          N    N  N  U        U  |  | " << endl;
	cout<< " |         /|  |\\    /|  |\\    /|  |\\               |         M        M  E          N     N N   U      U   |  | " << endl;
	cout<< " |          |  |      |  |      |  |                |         M        M  E E E E E  N       N    U U U     |  |    " << endl;
	cout<< " |          |  |      |  |      |  |                |_______________________________________________________|  |    " << endl;
	cout<< " |          |__|      |__|      |__|                                                                           |    " << endl;
    cout<< " |           )(        )(        )(           1.  New Game                                                     |    " << endl;
    cout<< " |          (  )      (  )      (  )          2.  Score Details                                                |    " << endl;
    cout<< " |           )(        )(        )(           3.  How to play                                                  |    " << endl;
    cout<< " |          (  )      (  )      (  )          4.  Credits                                                      |    " << endl;
    cout<< " |           )(        )(        )(           5.  Exit                                                         |    " << endl;
    cout<< " |                                                                                                             |    " << endl;
    cout<< " ______________________________________________________________________________________________________________     " << endl;
    cout<<"              Enter your choice  >>>>  ";
}

void gameOverInterface(){
    system("cls");
    cout<<"   ______________________________________________________________________________________________________________  "<<endl;
	cout<<"  |                                                                                                              | "<<endl;
	cout<<"  |                                                                                                              | "<<endl;
	cout<<"  |                                                                                                              | "<<endl;
    cout<<"  |        =================================================================================================     | "<<endl;
    cout<<"  |                G G G G        A       M       M  E E E E      O O O  V         V  E E E E  R R R             | "<<endl;
    cout<<"  |              G        G      A A      M M   M M  E           O     O  V       V   E        R    R            | "<<endl;
    cout<<"  |             G               A   A     M  M M  M  E E E      O       O  V     V    E E E    R    R            | "<<endl;
    cout<<"  |             G     G G G    A A A A    M   M   M  E E E      O       O   V   V     E E E    R R R             | "<<endl;
    cout<<"  |              G      G G   A       A   M       M  E           O     O     V V      E        R   R             | "<<endl;
    cout<<"  |                G G G  G  A         A  M       M  E E E E      O O O       V       E E E E  R    R            | "<<endl;
    cout<<"  |        =================================================================================================     | "<<endl;
    cout<<"  |                                                                                                              | "<<endl;
    cout<<"  |                                                                                                              | "<<endl;
    cout<<"  |                                     YOUR FINAL SCORE IS >>>>>>>>>>   " << setw(5) << gameScore << "                                   | "<<endl;
    cout<<"  |                                                                                                              | "<<endl;
    cout<<"  |                                                                                                              | "<<endl;
    cout<<"  |                                                                                                              | "<<endl;
    cout<<"  |                                                                                                              | "<<endl;
    cout<<"  |                                                                                                              | "<<endl;
    cout<<"  |                                                                                                              | "<<endl;
    cout<<"  |______________________________________________________________________________________________________________| "<<endl;

}

void instructionInterface(){
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "____________________________________________________________________________________________________"<< endl;
	cout << "|                                                                                                  |" << endl;
	cout << "|    H    H  OOOOOO   W     W      TTTTTTTT   OOOOOO         PPPPPP   L       AAAAAA    Y     Y    |" << endl;
	cout << "|    H    H  O    O   W     W         Tl      O    O         P    P   L       A    A    Y     Y    |" << endl;
	cout << "|    HHHHHH  O    O   W  W  W         Tl      O    O         PPPPPP   L       AAAAAA    YYYYYYY    |" << endl;
	cout << "|    H    H  O    O   W  W  W         Tl      O    O         P        L       A    A          Y    |" << endl;	
	cout << "|    H    H  OOOOOO   WWW WWW         Tl      OOOOOO         P        LLLLL   A    A     YYYYYY    |" << endl;
	cout << "|                                                                                                  |" << endl; 
	cout << "|                                                                                                  |" << endl;	
	cout << "|                                                                               ..                 |" << endl;
	cout << "| Avoid Landing the Ball on the Spikes                                       ,@@@@@@,              |" << endl;
	cout << "|                                                                           @@@@@@@@@@             |" << endl;
	cout << "| Use 'W' to move the ball Up to Avoid Spkies                              @@@@@@@@@@@@            |" << endl;
	cout << "|                                                                           @@@@@@@@@@             |" << endl;
	cout << "| Clear as many Spikes you can in order to score Points                      '@@@@@@'  A           |" << endl;
	cout << "|                                                                               ''    AAA          |" << endl;
	cout << "|                                                                                    AAAAA         |" << endl;
	cout << "|                                                                                   AAAAAAA        |" << endl;
	cout << "|              Collect the highest number of points in " << setw(3) << gameplayTimeUpdater << " seconds                                 |" << endl;
	cout << "|                                                                                                  |" << endl;
	cout << "|              Earn "<<setw(2) << gameScoreIncrementConstant << " marks for clearing any Obstacle                                             |" << endl;
	cout << "|                                                                                                  |" << endl;
	cout << "|              Earn "<<setw(2) << gameScoreBonusConstant << " bonus Marks for keeping the ball On the Ground                              |" << endl;
	cout << "|                                                                                                  |" << endl;
	cout << "|                                                                                                  |" << endl;	
	cout << "____________________________________________________________________________________________________" << endl;

}

void scoreDisplayInterface(){
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, blueColor); 
    cout << "____________________________________________________________________________________________________" << endl;
	cout << "|                                                                                                  |" << endl;
	cout << "|        SSSSSSSSSS     CCCCCCCCCC      OOOOOOOO      RRRRRRRRRR     EEEEEEEEEE     SSSSSSSSSS     |" << endl;
	cout << "|        SSSSSSSSSS     CCCCCCCCCC     OOOOOOOOOO     RRRRRRRRRR     EEEEEEEEEE     SSSSSSSSSS     |" << endl;
	cout << "|        SSSS           CCCC           OOOO  OOOO     RRRR   RRR     EEEE           SSSS           |" << endl;
	cout << "|        SSSSSSSSSS     CCCC           OOOO  OOOO     RRRRRRRRRR     EEEEEEEEEE     SSSSSSSSSS     |" << endl;
	cout << "|        SSSSSSSSSS     CCCC           OOOO  OOOO     RRRRRRRRRR     EEEEEEEEEE     SSSSSSSSSS     |  " << endl;
	cout << "|             SSSSS     CCCC           OOOO  OOOO     RRRR RRRR      EEEE                 SSSS     |" << endl;
	cout << "|        SSSSSSSSSS     CCCCCCCCCC     OOOOOOOOOO     RRRR  RRRR     EEEEEEEEEE     SSSSSSSSSS     |" << endl;
	cout << "|        SSSSSSSSSS     CCCCCCCCCC      OOOOOOOO      RRRR   RRRR    EEEEEEEEEE     SSSSSSSSSS     |" << endl;
	cout << "|                                                                                                  |" << endl;
    SetConsoleTextAttribute(h, whiteColor);  
	cout << "|" << left << setw(29) << "" << setw(25) << "----------------------------" << setw(38) << "" << "   |" <<endl;
	cout << "|" << left   << setw(29) <<"" << "|"<< setw(15) << "Player Name " << "|" << right << setw(10) << "Score" << left << "|" << setw(41) << "" << "|" << endl;
	cout << "|" << left << setw(29) << "" << setw(25) << "----------------------------" << setw(38) << "" << "   |" <<endl;
	for(int i = 0; i < 10; i++ ){
		cout << left << "|"<< setw(29) << "" << "|" << setw(15) << playerStatArray[i].playerName << "|"  << right << setw(10) << playerStatArray[i].playerScore   << left << "|"<< setw(41) << "" << "|" << endl;
	}
	cout << "|" << left << setw(29) << "" << setw(25) << "----------------------------" << setw(38) << "" << "   |" <<endl;	
	cout << "|                                                                                                  |" << endl;
	cout << "____________________________________________________________________________________________________" << endl;
}


void highScoreGameOverInterface(){
    cout << "High Score Game Over " << endl;
}

void creditsInterface(){
    cout << "Credits Interface " << endl;
}

void timeOutGameOverInterface(){
    cout << "Time Out Game OVer interface" << endl;
}


//-------------------------------------------------------------------------------------------------------------------------

//                                   T E S T I N G   A S S I S T A N C E

//Stats Display
void gamePlayTestingDetails(){
    cout << "Dynamic Diastance Adjust: "<< dynamicDistanceAdjust << endl;
    cout << "dynamicDistanceAdjustNegetive: "<< dynamicDistanceAdjustNegetive << endl;
    cout << "ballPositionFromTop: " << ballPositionFromTop << endl;
    cout << "obstacleMoveRate: " << obstacleMoveRate << endl;


}
