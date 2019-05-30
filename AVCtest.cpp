#include <iostream>
#include <math.h>
#include <sys/time.h>
#include "E101.h"

using namespace std;


class Robot{ //declaration
	private:
	int whiteness[320];
	int redness[320] ;
		int v_left,v_right, cam_tilt;
		int dv;
		double line_error;
		int quadrant;
		
	int leftWhite = 0;
        int black = 0;
        int rightWhite = 0;
	int red = 0;
        
        int mArea = 20;
        double speed = 10;
        
		const int cam_width = 320;
		const  int cam_height  =240;
		
		const int v_lefy_go =52; 
		const int v_right_go = 43;
		double kp = 0.05;
		int line_present = 1;
		int leftThreshold = 150;
		int rightThreshold = 170;
	
	public:
		Robot(){};
		~Robot(){};
		
		int initHardware();
		void ReadSetMotors();
		void SetMotors();
		int MeasureLine();
	//	int FollowLine();
		void move();
		void openGate();
		void turnRight(int speed);
		void turnLeft(int speed);
		void goStraight();
};

int Robot::MeasureLine(){
        int row = 120;
        take_picture();
        //update_screen();

        //Clear the array
        for(int i = 0; i<320; i++){
                fill_n(whiteness, i , 0);
		 fill_n(redness, i , 0);
        }
        //Testing loop for camera input
        /*for(int col = 0; col< 320; col++){
                int intensity = (int)get_pixel(row, col, 3);
                whiteness[col] = intensity;
                cout << whiteness[col];
                if (whiteness[col]< 80 ) {
                        cout << " _______ ";
                }
        }*/
       leftWhite = 0;
       rightWhite=0;
       black =0;
	red = 0;
        for(int col = 0; col<320; col++){
                int intensity = (int)get_pixel(row,col, 3);
		whiteness[col] = intensity;
		int red = (int)get_pixel(row,col, 1)
		redness[col] = red;
        }
        for(int col = 0; col<320; col++){
                while(whiteness[col] > 80){
                        leftWhite++;
                        col++;
                }
                while(whiteness[col] < 80){
                        black++;
                        col++;
                }
                while(whiteness[col] > 80){
                        rightWhite++;
                        col++;
                }
        }
	
        

}

void Robot::moving(){
	  double ratio = (leftWhite-rightWhite);
        cout << "   " << ratio << "   ";
        
        if(ratio > mArea){
                //turn right
                speed = getSpeed(ratio, mArea);
                turnRight(speed);
        }
        else if(ratio < -mArea){
                //turn left
                speed = getSpeed(ratio, mArea);
                turnLeft(speed);
        }
        else {
                //go straight
                goStraight();
        }
        
	if ( redness> 0.65) {
	  //breaks;	
		quadrant ++;
		printf("break");
	}
        return 0;
	
}

double Robot::getSpeed(double ratio, double mArea){
        double ratio2 = fabs(ratio);
        double speed;
        if(ratio2 > 150){
                cout<<" hard turn ";
        }
        else{
                cout<<" soft turn ";
        }

        return speed;
}


void Robot::openGate() {

	char message[24]={'P','l','e','a','s','e'};
	char password[24];
	char IP[15]={'1','3','0','.','1','9','5','.','6','.','1','9','6'};

	connect_to_server(IP, 1024); //need to find this out!!
	send_to_server(message);
	receive_from_server(password);
	send_to_server(password);
	
	//return true;

}

void Robot::turnRight(int speed){
	cout << "turning right ";
}

void Robot::turnLeft(int speed){
	cout << "turning left ";
}

void Robot::goStraight(){
	cout << "_________ ";
}

int  robot::initHardware(){
	int err = init(0);
}

int main () { // example of main ( ) i n v o k i n g the c l a s s
	robot.initHardware();
	open_screen_stream();
	quadrant = 1;
	Robot robot;
	int count = 0;
	if (quadrant == 1 ){
		robot.openGate();
		quadrant ++;
	}
	else if (quadrant == 2) {
		while(count < 1000){
			robot.MeasureLine();
			robot.moving();
			count++;
		}
	}
	close_screen_stream();
	return 0;
}
