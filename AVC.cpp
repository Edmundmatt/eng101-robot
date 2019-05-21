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
	
	public:
		Robot(){};
		~Robot(){};
		int initHardware();
		void ReadSetMotors();
		void SetMotors();
		int MeasureLine();
		int FollowLine();
		void openGate();
};

int Robot::MeasureLine(){
	int row = 120;
	take_picture();
	update_screen();
	
	//Clear the array
	for(int i = 0; i<320; i++){
		fill_n(whiteness, i , 0);
	}
	
	for(int col = 0; col< 320; col++){
		int intensity = (int)get_pixel(row, col, 3);
		whiteness[col] = intensity;
		cout << whiteness[col];
			
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

	char message[24]="Please";
	char password[24];
	char IP[15]="130.195.6.196";

	connect_to_server(IP, 1024); //need to find this out!!
	send_to_server(message);
	receive_from_server(password);
	send_to_server(password);
	
	//return true;

}

int main () { // example of main ( ) i n v o k i n g the c l a s s
	open_screen_stream();
	Robot robot;
	robot.openGate();
	robot.MeasureLine();
	/*robot.initHardware () ;
	//int count = 0;
	open_screen_stream () ;
	while ( count < 5000)
		{
		robot.FollowLine () ;
		count ++;
		}
	// s a v e _ p i ct u r e ( " f i l e 1 " ) ;
	close_screen_stream ( ) ;
	stoph() ;*/
	close_screen_stream();
	return 0;
}
