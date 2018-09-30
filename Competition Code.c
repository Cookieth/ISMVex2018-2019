#pragma config(Sensor, dgtl1,  limitSwitch,    sensorTouch)
#pragma config(Motor,  port2,           right,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           left,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           arm,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           frontMangonel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           backMangonel,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           claw,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

void basicAutonomous();
void nAutonomous();

void pre_auton()
{
  bStopTasksBetweenModes = true;
}

task autonomous()
{
	basicAutonomous();
}



//---------------------------------------------------------------------------------------------------------------
//
//																D R I V E R  C O N T R O L   S E C T I O N
//---------------------------
// Functions
//---------------------------
//
//---------------------------
// Controller 1
//---------------------------
// AccelX:
// AccelY:
// AccelZ:
// Btn5U: Mangonel
// Btn5D: Mangonel
// Btn6U: Intake
// Btn6D: Intake
// Btn7U:
// Btn7D: Switch Controller
// Btn7L:
// Btn7R:
// Btn8U:
// Btn8D: Switch Direction
// Btn8L: Change "Gear"
// Btn8R: Change "Gear"
// Ch1:
// Ch2: Right-Side Base Motors
// Ch3: Left-Side Base Motors
// Ch4:
//---------------------------
// Controller 2
//---------------------------
// AccelXXmtr2:
// AccelYXmtr2:
// AccelZXmtr2:
// Btn5UXmtr2: Claw --> Arm
// Btn5DXmtr2: Claw --> Arm
// Btn6UXmtr2:
// Btn6DXmtr2:
// Btn7UXmtr2:
// Btn7DXmtr2: Switch Controller
// Btn7LXmtr2: Claw
// Btn7RXmtr2: Claw
// Btn8UXmtr2:
// Btn8DXmtr2: Switch Direction
// Btn8LXmtr2: Change "Gear"
// Btn8RXmtr2: Change "Gear"
// Ch1Xmtr2:
// Ch2Xmtr2: Right-Side Base Motors
// Ch3Xmtr2: Left-Side Base Motors
// Ch4Xmtr2:
//---------------------------------------------------------------------------------------------------------------
task usercontrol()
{
	int driveGear = 1;
	int direction = 1;
	int driveController = 1;
	int trueCh2;
    	int trueCh3;
	while (true){
			
		//=======================BASE CONROL (BOTH CONTROLLERS)=======================
		if(driveController == 1) {
			trueCh2 = (vexRT[Ch2]*direction)/driveGear;
			trueCh3 = (vexRT[Ch3]*direction)/driveGear;
		}
		else {
			trueCh2 = (vexRT[Ch2Xmtr2]*direction)/driveGear;
			trueCh3 = (vexRT[Ch3Xmtr2]*direction)/driveGear;
		}

		if(((vexRT[Btn8D] == 1) && (driveController == 1))|| ((vexRT[Btn8DXmtr2] == 1) && (driveController == -1))) {
			direction = direction * -1;
			wait1Msec(0500);
		}
		if(((vexRT[Btn7D] == 1) && (driveController == 1)) || ((vexRT[Btn7DXmtr2] == 1) && (driveController == -1))) {
			driveController = driveController * -1;
			wait1Msec(0500);
		}

		if(((vexRT[Btn8R] == 1) && (driveController == 1)) || ((vexRT[Btn8RXmtr2] == 1) && (driveController == -1))) {
			driveGear += 1;
			wait1Msec(0500);
		}
		else if(((vexRT[Btn8L] == 1) && (driveController == 1)) || ((vexRT[Btn8LXmtr2] == 1) && (driveController == -1))&&(driveGear > 1)){
			driveGear -= 1;
			wait1Msec(0500);
		}

		motor[right] = trueCh2;
		motor[left] = trueCh3;

		//=======================ARM CONTROL (PARTNER JOYSTICK)===================

		if(vexRT[Btn5UXmtr2]==1) {
			motor[arm] = 127;
		}
		else if(vexRT[Btn5DXmtr2] == 1) {
			motor[arm] = -127;
		}
		else {
			motor[arm] = 0;
		}

		if(vexRT[Btn7LXmtr2] == 1) {
			motor[claw] = 40;
		}
		else if(vexRT[Btn7RXmtr2] == 1) {
			motor[claw] = -40;
		}
		else {
			motor[claw] = 0;
		}

	      	//=======================MANGONEL CONTROL (MAIN JOYSTICK)===================

		if(vexRT[Btn6U] == 1) {
			motor[intake] = 127; //ADJUSTABLE
			if(SensorValue[limitSwitch] != 1) {
				motor[frontMangonel] = 127;
				motor[backMangonel] = 127;
			}
			else {
				motor[frontMangonel] = 0;
				motor[backMangonel] = 0;
			}
		}
		else if(vexRT[Btn6D] == 1) {
			motor[intake] = -127; //ADJUSTABLE
		}
		else {
			motor[intake] = 0;
		}

		if(vexRT[Btn5U]==1) {
			motor[frontMangonel] = 127;
			motor[backMangonel] = 127;
		}
		else if(vexRT[Btn5D] == 1 && SensorValue[limitSwitch] != 1) {
			motor[frontMangonel] = 127;
			motor[backMangonel] = 127;
		}
		else {
			motor[frontMangonel] = 0;
			motor[backMangonel] = 0;
		}
	} //end of while loop
}

//---------------------------------------------------------------------------------------------------------------
//
//                                A U T O N O M O U S   C O N T R O L   S E C T I O N
//														Functions:
//																basicAutonomous - Simple sutonomous code
//																nAutonomous - Template autonomous code
//
//---------------------------------------------------------------------------------------------------------------

void basicAutonomous(){
  motor[left] = 127;
  motor[right] = 127;
  wait1Msec(2000);
  motor[left] = -127;
  motor[right] = -127;
  wait1Msec(1000);
  motor[left] = 127;
  motor[right] = 0;
  wait1Msec(1000);
  motor[left] = 127;
  motor[right] = 127;
  wait1Msec(2000);
  motor[left] = 0;
  motor[right] = 0;
  wait1Msec(2000);

  motor[frontMangonel] = 0;
  motor[backMangonel] = 0;
}

void nAutonomous(){

}
