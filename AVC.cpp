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
//#include "E101.h"

using namespace std;
//int main(){
//struct timespec ts_start;
//struct timespec ts_end;
//clock_gettime(CLOCK_MONOTONIC, &ts_start);
//for ( int i = 0 ; i< 560;i++){//ci n t Robot : : Fo l lowL ine ( ) {
//MeasureLine ( ) ;
//i f ( l i n e _ p r e s e nt ) {
//dv = ( i n t ) ( l i n e _ e r r o r∗kp ) ;
// / / dv = 0;
//v _ l e f t = v _ l eft _ g o + dv ;
//v _ r i g h t = v _ r i g ht _ g o + dv ;
//cout << " l i n e _ e r r o r = " << l i n e _ e r r o r << " dv= " <<dv ;
//SetMoto rs ( ) ;
//} else {
// / / go back
//cout << " Line mi s sing " <<endl ;
//v _ l e f t = 39;
//v _ r i g h t = 55;
//SetMoto rs ( ) ;
//sleep1 ( 1 0 0 ) ;
//}
//re tu rn 0;
//}ode_to_time();
//double x = sin(i);
//}
//clock_gettime(CLOCK_MONOTONIC, &ts_end);
//long elapsed = (ts_end.tv_sec-ts_start.tv_sec)*1000000000 +
//ts_end.tv_nsec-ts_start.tv_nsec;
//cout<<"elapsed[ns]="<<elapsed<<endl;
//

//while not connected
while(connect_to_server != 0){
	int connect_to_server( char server_addr[15], int port);
	int send_to_server( char message[24]);
	int receive_from_server( char message[24]);
}

class Robot{ //declaration
	private:
		int v_left,v_right, cam_tilt;
		int dv;
		double line_error;
		int quadrant;
		const int cam_width + 320;
		const  int cam_height  =240;
		
		const int v_lefy_go =52; 
		const int v_right_go = 43;
		double kp = 0.05;
		int line_present = 1;
	
	public:
		Rob(){};
		int initHardware();
		void ReadSetMotors();
		void SetMotors();
		int MeasureLine();
		int FollowLine();
};
int main () { // example of main ( ) i n v o k i n g the c l a s s
	Robot robot;
	robot.InitHardware () ;
	int count = 0;
	open_screen_stream () ;
	while ( count < 5000)
		{
		robot.MeasureLine () ;
		robot.FollowLine () ;
		count ++;
		}
	// s a v e _ p i ct u r e ( " f i l e 1 " ) ;
	close_screen_stream ( ) ;
	stoph() ;
	return 0;
}

int Robot::MeasureLine(){
	int row = 0;
	int col = 0;
	take_picture();
	
	
	
		while (col < 320){
	double a = double[i];
	
	col = col++;
}
}

int Robot::FollowLine(){
	MeasureLine();
	if (line_present){
		dv = ( int ) (line_error∗kp) ;
		// dv = 0;
		v_left = v_left_go + dv ;
		v_right = v_right_go + dv ;
		cout<< "l i n e _ e r r o r = " << line_error << " dv= " <<dv ;
		SetMotors() ;
	} else {
	// go back
		cout<< " Line missing " <<endl ;
		v_left = 39;
		v_right = 55;
		SetMotors () ;
		sleep1( 100 ) ;
	}
	return 0;
}

