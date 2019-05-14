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
