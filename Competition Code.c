#pragma config(Sensor, in1,    potentiometer,  sensorPotentiometer)
#pragma config(Sensor, dgtl1,  limitSwitch,    sensorTouch)
#pragma config(Sensor, dgtl2,  rightEnc,       sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  rightSonar,     sensorSONAR_cm)
#pragma config(Sensor, dgtl6,  leftEnc,        sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  leftSonar,      sensorSONAR_cm)
#pragma config(Sensor, dgtl10, clawEnc,        sensorQuadEncoder)
#pragma config(Sensor, dgtl12, intakeLimit,    sensorTouch)
#pragma config(Motor,  port2,           right,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           right2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           arm,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           mangonel,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           left,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           left2,         tmotorVex393_MC29, openLoop, encoderPort, None)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

void basicAutonomous();
void nAutonomous();

task intakeControl();

void pre_auton()
{
	bStopTasksBetweenModes = true;
}

task autonomous()
{
	nAutonomous();
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
// Btn7U: Auton Tester
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
// Btn5UXmtr2:
// Btn5DXmtr2:
// Btn6UXmtr2: Claw --> Arm
// Btn5DXmtr2: Claw --> Arm
// Btn7UXmtr2: Auton Tester
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
  int mangonelState = 0;
  
  int threshold = 50;
  
  int lowCapDist = 12;
  int highCapDist = 12;
  
  startTask(intakeControl);
  SensorValue[leftEnc] = 0;
  SensorValue[rightEnc] = 0;
  
	while (true){
	
		if((vexRT[Btn7U] == 1) || (vexRT[Btn7UXmtr2] == 1)) {
			wait1Msec(0500);
			nAutonomous();
			
		}
		//=======================BASE CONROL (BOTH CONTROLLERS)=======================
		if(driveController == 1 && direction == 1) {
			trueCh2 = (vexRT[Ch2])/driveGear;
			trueCh3 = (vexRT[Ch3])/driveGear;
		}
		else if(driveController == 1 && direction == -1){
			trueCh2 = (vexRT[Ch3]*direction)/driveGear;
			trueCh3 = (vexRT[Ch2]*direction)/driveGear;
		}
		else if(driveController == -1 && direction == 1){
			trueCh2 = (vexRT[Ch2Xmtr2]/driveGear);
			trueCh3 = (vexRT[Ch3Xmtr2]/driveGear);
		}
		else if(driveController == -1 && direction == -1){
			trueCh2 = (vexRT[Ch3Xmtr2]*direction)/driveGear;
			trueCh3 = (vexRT[Ch2Xmtr2]*direction)/driveGear;
		}

		if((vexRT[Btn8D] == 1)|| (vexRT[Btn8DXmtr2] == 1)) {
			direction = direction * -1;
			wait1Msec(0500);
		}
		if((vexRT[Btn7D] == 1) || (vexRT[Btn7DXmtr2] == 1)) {
			driveController = driveController * -1;
			wait1Msec(0500);
		}

		if(((vexRT[Btn8R] == 1) && (driveController == 1)) || ((vexRT[Btn8RXmtr2] == 1) && (driveController == -1))) {
			driveGear += 1;
			wait1Msec(0500);
		}
		else if((((vexRT[Btn8L] == 1) && (driveController == 1)) || ((vexRT[Btn8LXmtr2] == 1) && (driveController == -1)))&&(driveGear > 1)){
			driveGear -= 1;
			wait1Msec(0500);
		}

		if(trueCh2 > threshold){
			motor[right] = trueCh2;
			motor[right2] = trueCh2;
		}
		else if(trueCh2 > 10 && trueCh2 < threshold){
			motor[right] = threshold;
			motor[right2] = threshold;
		}
		else if(trueCh2 < -10 && trueCh2 > (-threshold)){
			motor[right] = -threshold;
			motor[right2] = -threshold;
		}
		else if(trueCh2 < -threshold){
			motor[right] = trueCh2;
			motor[right2] = trueCh2;
		}
		else{
			motor[right] = 0;
			motor[right2] = 0;
		}
		
		if(trueCh3 > threshold){
			motor[left] = trueCh3;
			motor[left2] = trueCh3;
		}
		else if(trueCh3 > 10 && trueCh3 < threshold){
			motor[left] = threshold;
			motor[left2] = threshold;
		}
		else if(trueCh3 < -10 && trueCh3 > (-threshold)){
			motor[left] = -threshold;
			motor[left2] = -threshold;
		}
		else if(trueCh3 < -threshold){
			motor[left] = trueCh3;
			motor[left2] = trueCh3;
		}
		else{
			motor[left] = 0;
			motor[left2] = 0;
		}

		//=======================ARM CONTROL (PARTNER JOYSTICK)===================

		if(vexRT[Btn6UXmtr2]==1) {
			motor[arm] = 127;
		}
		else if(vexRT[Btn6DXmtr2] == 1) {
			motor[arm] = -127;
		}
		else if(vexRT[Btn5UXmtr2] == 1) {
			motor[arm] = 63;
		}
		else if(vexRT[Btn5DXmtr2] == 1) {
			motor[arm] = -63;
		}
		
		else {
			motor[arm] = 0;
		}

		if(vexRT[Btn7LXmtr2] == 1) {
			motor[claw] = 127;
		}
		else if(vexRT[Btn7RXmtr2] == 1) {
			motor[claw] = -127;
		}
		else if(vexRT[Btn8LXmtr2] == 1) {
			motor[claw] = 20;
		}
		else if(vexRT[Btn8RXmtr2] == 1) {
			motor[claw] = -20;
		}
		else {
			motor[claw] = 0;
		}

	      	//=======================MANGONEL CONTROL (MAIN JOYSTICK)===================
		

		
		
		
		if(vexRT[Btn5U]==1) {
			motor[mangonel] = 127;
			mangonelState = 1;
		}
		else if(mangonelState == 1 && SensorValue[limitSwitch] != 1) {
			motor[mangonel] = 127;
		}
		else if((SensorValue[limitSwitch] == 1 || vexRT[Btn5D] == 1) && vexRT[Btn6U] != 1) { //"Else if" due to conflicts with Btn6U in intake section; can't be left as just an "else" statement
			motor[mangonel] = 0;
			mangonelState = 0;
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

  motor[mangonel] = 0;
}

void nAutonomous(){
	motor[mangonel] = 127;
	wait1Msec(0500);
	motor[mangonel] = 0;
  	motor[arm] = -127;
  	wait1Msec(0500);
  	motor[arm] = 0;
  
  	motor[left] = 127;
  	motor[right] = 0;
  	wait1Msec(0200);
  	motor[left] = 127;
  	motor[right] = 127;
  	wait1Msec(0785);
  	motor[left] = 0;
  	motor[right] = 0;
  	wait1Msec(1000);
  	motor[left] = -127;
  	motor[right] = -127;
  	wait1Msec(0700);
  	motor[left] = 0;
  	motor[right] = 0;
  	wait1Msec(1000);
	motor[arm] = 127;
	wait1Msec(0400);
	motor[arm] = 0;
  	
  	if(SensorValue[potentiometer] < 1000) {
  		/*
		//RED AUTON
		motor[left] = 127;
		motor[right] = -127;
		wait1Msec(0550);
		motor[left] = 0;
  		motor[right] = 0;
  		wait1Msec(0500);
		motor[left] = 127;
		motor[right] = 127;
		wait1Msec(0810);
		
		//PUSHES CAP OFF OF BALL
		motor[left] = 0;
		motor[right] = 0;
		wait1Msec(0500);
		motor[left] = 127;
		motor[right] = 127;
		wait1Msec(0100);
		motor[left] = 0;
		motor[right] = 0;
		wait1Msec(0500);
		motor[left] = -127;
		motor[right] = -127;
		wait1Msec(0100);
		
		//TURN TO HIT LOW FLAG
		motor[left] = -127;
		motor[right] = 127;
		wait1Msec(0525);
		motor[left] = 0;
  		motor[right] = 0;
  		wait1Msec(0500);
		motor[arm] = -127;
		wait1Msec(0500);
		motor[arm] = 0;
		motor[left] = 127;
		motor[right] = 127;
		wait1Msec(0600);
		motor[left] = 0;
  	motor[right] = 0;
  	wait1Msec(0500);
		motor[left] = 127;
  	motor[right] = -127;
  	wait1Msec(0300);
  	motor[left] = 127;
  	motor[right] = 127;
  	wait1Msec(0200);
  	*/
  	}
	else if(SensorValue[potentiometer] > 1000 && SensorValue[potentiometer] < 3000) {
		//SKILLS AUTON
		motor[left] = 127;
		motor[right] = -127;
		wait1Msec(0550);
		motor[left] = 0;
  		motor[right] = 0;
  		wait1Msec(0500);
		motor[left] = 127;
		motor[right] = 127;
		wait1Msec(0850);
		motor[left] = 0;
		motor[right] = 0;
	  	
		//FLIPS CAP OFF OF BALL
		motor[arm] = -127;
		wait1Msec(0500);
		motor[arm] = 0;
		
		//TURN TO HIT LOW FLAG
		motor[left] = -127;
		motor[right] = 127;
		wait1Msec(0525);
		motor[left] = 0;
  		motor[right] = 0;
  		wait1Msec(0500);
		motor[left] = 127;
		motor[right] = 127;
		wait1Msec(0600);
		motor[left] = 0;
  	motor[right] = 0;
  	wait1Msec(0500);
		motor[left] = 127;
  	motor[right] = -127;
  	wait1Msec(0300);
  	motor[left] = 127;
  	motor[right] = 127;
  	wait1Msec(0200);
	}
  	else if(SensorValue[potentiometer] > 3000) {
  		/*
		//BLUE AUTON
		motor[left] = 127;
		motor[right] = -127;
		wait1Msec(0550);
		motor[left] = 0;
  		motor[right] = 0;
  		wait1Msec(0500);
		motor[left] = 127;
		motor[right] = 127;
		wait1Msec(0850);
		
		//PUSHES CAP OFF OF BALL
		motor[left] = 0;
		motor[right] = 0;
		wait1Msec(0500);
		motor[left] = 127;
		motor[right] = 127;
		wait1Msec(0100);
		motor[left] = 0;
		motor[right] = 0;
		wait1Msec(0500);
		motor[left] = -127;
		motor[right] = -127;
		wait1Msec(0100);
		
		//TURN TO HIT LOW FLAG
		motor[left] = 127;
		motor[right] = -127;
		wait1Msec(0525);
		motor[left] = 0;
  		motor[right] = 0;
  		wait1Msec(0500);
		motor[arm] = -127;
		wait1Msec(0500);
		motor[arm] = 0;
		motor[left] = 127;
		motor[right] = 127;
		wait1Msec(0600);
		motor[left] = 0;
  	motor[right] = 0;
  	wait1Msec(0500);
		motor[left] = 127;
  	motor[right] = -127;
  	wait1Msec(0300);
  	motor[left] = 127;
  	motor[right] = 127;
  	wait1Msec(0200);
  	*/
  	}
} 


task intakeControl(){
	int intakeUpState = -1;
  int intakeDownState = -1;
  
	while(true){
		if(vexRT[Btn6U] == 1 && intakeDownState == -1) {
			intakeUpState = intakeUpState * -1;
			wait1Msec(0500);
			//motor[intake] = 127; //ADJUSTABLE
			/*if(SensorValue[limitSwitch] != 1) {
				motor[frontMangonel] = 127;
				motor[backMangonel] = 127;
			}
			else {
				motor[frontMangonel] = 0;
				motor[backMangonel] = 0;
			}*/
		}
		else if(vexRT[Btn6U] == 1 && intakeDownState == 1){
			intakeDownState = intakeDownState * -1;
			intakeUpState = intakeUpState * -1;
			wait1Msec(0500);
		}
		else if(vexRT[Btn6D] == 1 && intakeUpState == -1) {
			intakeDownState = intakeDownState * -1;
			wait1Msec(0500);
			//motor[intake] = -127; //ADJUSTABLE
		}
		else if(vexRT[Btn6D] == 1 && intakeUpState == 1) {
			intakeUpState = intakeUpState * -1;
			intakeDownState = intakeDownState * -1;
			wait1Msec(0500);
			//motor[intake] = -127; //ADJUSTABLE
		}
		else {
			
		}
		
		if(intakeUpState == 1){
			motor[intake] = 127;
		}
		else if(intakeDownState == 1){
			motor[intake] = -127;
		}
		else{
			motor[intake] = 0;
		}
	}
}
