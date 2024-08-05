
//                      L I B R A R I E S
#include <iostream>
#include <chrono> // Time the tasks
#include <cstdlib> // For system configs
using namespace std;

//                  G L O B A L  V A R I A B L E S




// Function List
void welcomeSplashScreen();      // Splash Screen at Initialization                     == AKILA
void screenClear();              // Switch and clear terminal based on time intervals   == AKILA



//                      F U N C T I O N S

void screenClear(int time){
    auto duration = std::chrono::seconds(time);                 //Set Time in which changes occur
    auto start_time = std::chrono::steady_clock::now();         // Obtain Current time
    while ((std::chrono::steady_clock::now() - start_time) < duration) { 
        //Loop to idle while in Sllep time
    }
    system("cls");
}

void welcomeSplashScreen(){
    system("cls");
    //cout << "************************************************************************************************************************" << endl;
    cout << "       ************     ***              ************     ************     ************      ***      ***               " << endl;
    cout << "       ************     ***              ************     ************     ************      ***      ***               " << endl;
    cout << "       ***              ***              ***      ***     ***      ***     ***      ***      ***      ***               " << endl;
    cout << "       ************     ***              ************     ************     ************      ************               " << endl;
    cout << "       ************     ***              ************     ************     ************      ************               " << endl;
    cout << "       ***              ***              ***      ***     ***              ***                        ***               " << endl;
    cout << "       ***              ************     ***      ***     ***              ***               ************               " << endl;
    cout << "       ***              ************     ***      ***     ***              ***               ************               " << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "       ************     ************     ************     ************                                                  " << endl;
    cout << "       ************     ************     ************     ************                                                  " << endl;
    cout << "       ***      ***         ***          ***      ***     ***      ***                                                  " << endl;
    cout << "       ************         ***          ***      ***     ***      ***                                                  " << endl;
    cout << "       ************         ***          ************     ***      ***                                                  " << endl;
    cout << "       ***      ***         ***          *********        ***      ***                                                  " << endl;
    cout << "       ************     ************     ***     ***      ************                                                  " << endl;
    cout << "       ************     ************     ***      ****    ************                                                  " << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "                             ******************" << endl;
    cout << "                          ******************"                     << endl;
    cout << "          ******         ****************"  << endl;
    cout << "       *****  ****     **************"  << endl;
    cout << "         *********  *************         **********"  << endl;
    cout << "          ***************************************"  << endl;
    cout << "             **********************************"  << endl;
    cout << "               *********************************"  << endl;
    cout << "                  *******************************"  << endl;
    cout << "                        *****************"  << endl;
    cout <<"--------------------------------------------------------------------------------------------------------------------------"<< endl;







    //screenClear(3);
    //cout << "Time out";
}


int main(){
    welcomeSplashScreen();
    return(0);

}
