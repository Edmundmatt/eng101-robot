/*
 * engr101.cxx
 * 
 * Copyright 2019 Pham Dong <dongpham@batavia.ecs.vuw.ac.nz>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <iostream>
#include <math.h>
#include <sys/time.h>
#include "E101.h"

using namespace std;


class Robot{ //declaration
	private:
		int whiteness[320];
		int v_left,v_right, cam_tilt;
		int dv;
		double line_error;
		int quadrant;
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
		int FollowLine();
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
	int leftWhite = 0;
	int black = 0;
	int rightWhite = 0;
	for(int col = 0; col<320; col++){
		int intensity = (int)get_pixel(row,col, 3);
		whiteness[col] = intensity;
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
	
	double ratio = (leftWhite-rightWhite);
	int mArea = 20;
	if(ratio > mArea){
		//turn left
		turnRight(5);
	}
	else if(ratio < -mArea){
		//turn right
		turnLeft(5);
	}
	else {
		//go straight
		goStraight();
	}
	
	return 0;
}


int Robot::FollowLine(){
	/*int whiteness[320] = MeasureLine();
	bool line_present = false;
	for(int i = 0; i<320; i++){
		if(whiteness[i] < 
	if (line_present){
		int dv = ( int ) (line_error∗kp) ;
		// dv = 0;
		int v_left = v_left_go + dv ;
		v_right = v_right_go + dv ;
		cout<< "line_error = " << line_error << " dv= " <<dv ;
		SetMotors() ;
	} else {
	// go back
		cout<< " Line missing " <<endl ;
		v_left = 39;
		v_right = 55;
		SetMotors () ;
		sleep1( 100 ) ;
	}*/
	return 0;
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

int main () { // example of main ( ) i n v o k i n g the c l a s s
	int err = init(0);
	open_screen_stream();
	Robot robot;
	robot.openGate();
	int count = 0;
	while(count < 1000){
		robot.MeasureLine();
		count++;
	}
	close_screen_stream();
	return 0;
}
