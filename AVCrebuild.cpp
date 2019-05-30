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

class Robot{ //list of variables
	private:
	int whiteness[320];
	unsigned char v_goLeft; //speed of left motor going forward
	unsigned char v_goRight; //speed of right motor giong forward
	unsigned char dv; //difference of speed of left and right motors
	const int base = 47;
	//bool linePresent = true;
	public: //methods list
		Robot(){};
		~Robot(){};
		int initHardware();
		void openGate();
		void lineThere();
		int measureLine();
		void turnLeft(double speed);
		void turnRight(double speed);
		void goStraight();
		void getSpeed(double ratio);
		void findLine();
		int row = 120;
		bool linePresent = true;
		void DegL90();
		void DegR90();
	
};

int main () {
	open_screen_stream();
	Robot robot;
	robot.initHardware();
	set_motors(1,48);
	set_motors(5,48);
	hardware_exchange();
	robot.openGate();
	while(  robot.linePresent){
	robot.measureLine();
	}
}

int Robot::initHardware(){
	int err = init(0);
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

void Robot::lineThere(){
	int max = 125;
	int faultCounter = 0;
	take_picture();
	for(int i = 0; i < 320; i++){
		int number = get_pixel(120, i, 3);
		if(number > max){
			faultCounter++;
		}
	}
	if(faultCounter < 30){
		linePresent = false;
		//cout<<" no line ";
	}
	else{
		linePresent = true;
		//cout<<" line ";
	}
	//cout<<", ";
	//cout<<faultCounter;
	faultCounter = 0;
}

void Robot::findLine(){
	set_motors(1, base + 5);
	set_motors(5, base - 5);
	hardware_exchange();
	sleep1(500);
	lineThere();
}

int Robot::measureLine(){
	lineThere();
	while(linePresent == false){
		findLine();
	}
	take_picture();
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

	//if(leftWhite < 2){
	//	DegL90();
	//	cout<<" hard left";
	//}
	//else if(rightWhite < 2){
	//	DegR90();
	//	cout<<" hard right ";
	//}

	double ratio = (leftWhite-rightWhite);
	getSpeed(ratio);
	return 0;
}
void Robot::getSpeed(double ratio){
	cout<<ratio;
	double speed = ratio/40;
	if (speed>12){
		speed=12;
	}else if(speed < -12){
		speed = 12;
	}
	if(speed < 0){
		speed = fabs(speed);
	}

	if(speed > 0 && speed < 1){
		speed = 1;
	}

	if (ratio>80){
		turnRight(speed);
	} else if (ratio< -80){
		turnLeft(speed);
	}else {
		goStraight();
	}
}

void Robot::turnRight(double speed){
	set_motors(5, base +speed);
	set_motors(1, base -speed/3);
	hardware_exchange();
	//cout << " turn right ";
	
}
void Robot::turnLeft(double speed){
	set_motors(1,base - speed);
	set_motors(5, base + speed/3);
	hardware_exchange();
	//cout << " turn left ";
} 
void Robot::goStraight(){
	set_motors(1, base - 5);
	set_motors(5, base + 5);
	hardware_exchange();
	//cout << " go straight ";
}

void Robot::DegL90(){
	set_motors(1, base - 5);
	set_motors(5, base - 5);
	hardware_exchange();
	sleep1(500);
}

void Robot::DegR90(){
	set_motors(1, base + 5);
	set_motors(1, base + 5);
	hardware_exchange();
	sleep1(500);
}

