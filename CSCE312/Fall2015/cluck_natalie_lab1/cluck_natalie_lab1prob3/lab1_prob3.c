// CSCE312: Lab-1 Problem-3 framework

/* ***   README   **** */

/*
This example program sounds the bell when driver is on seat 
AND haven't closed the doors. Use the general framework and the function 
shells, replace the code inside  the control_action() function with your 
own code to do problems 3 and 4.

Note: This code is designed to run in an infinite loop to mimic a real control system. 
If you prefer to read the inputs from a file, modify the code appropriately to terminate the
loop when all the inputs have been processed.

Turning in this file without your code will result in zero points being awarded for this problem.

run this file as : gcc filename.c -o executableName

*/


#include <stdio.h> //This is useful to do i/o to test the code 

unsigned int driver_on_seat;
unsigned int driver_seat_belt_fastened;
unsigned int engine_running;
unsigned int doors_closed;
unsigned int key_in_car;
unsigned int door_lock_lever;
unsigned int brake_pedal;
unsigned int car_moving;
unsigned int bell = 0;
unsigned int door_lock_actuator = 0;
unsigned int brake_actuator = 0;

void read_inputs_from_ip_if(){

	//place your input code here
	//to read the current state of the available sensors
	
	printf("Driver in Seat? ");
	scanf("%d", &driver_on_seat);
	
	printf("Seat Belt Fastened? ");
	scanf("%d", &driver_seat_belt_fastened);
	
	printf("Engine Running? ");
	scanf("%d", &engine_running);
	
	printf("Doors Closed? ");
	scanf("%d", &doors_closed);
	
	printf("Key in Car?" );
	scanf("%d", &key_in_car);

	printf("Door Lock Lever activated? ");
	scanf("%d", &door_lock_lever);
	
	printf("Brake Pedal pressed? ");
	scanf("%d", &brake_pedal);
	
	printf("Car moving? ");
	scanf("%d",&car_moving);
	
	
	
	//scanf("Bell on? %d",&bell);
	//scanf("Door locked? %d", &door_lock_actuator);
	//scanf("Brake activated? %d",&brake_actuator);
	
}

void write_output_to_op_if(){

	//place your output code here
    //to display/print the state of the 3 actuators (DLA/BELL/BA)
	if(bell == 1) printf("Bell is on!\n");
	else if (bell == 0) printf ("Bell is off.\n");
	
	if(door_lock_actuator == 1) printf("Door is locked.\n");
	else if (door_lock_actuator == 0) printf ("Doors are not locked.\n");
	
	if(brake_actuator == 1) printf("Brakes are activated.\n");
	else if (brake_actuator == 0) printf ("Brakes are not activated.\n");
	//fprintf("Door Locked: " + door_lock_actuator);
	//fprintf("Brake: " + brake_actuator);

}


//The code segment which implements the decision logic
void control_action(){

	/*
	The code given here sounds the bell when driver is on seat 
	AND hasn't closed the doors. (Requirement-2)
 	Replace this code segment with your own code to do problems 3 and 4.
	*/

	// Requirement-1
	if((engine_running == 1) && (driver_seat_belt_fastened == 0) && (driver_on_seat == 1)) bell = 1; 
	else bell = 0; // Requirement-3
		
	// Requirement-2
	if ((driver_on_seat == 1) && (engine_running == 1) && (doors_closed == 0)) { bell = 1; }
	else bell = 0; // Requirement-3

	// Requirement-4
	if ((driver_on_seat==0) && (key_in_car == 1))
		door_lock_actuator = 0;
	else if ((driver_on_seat = 1) && (door_lock_lever = 1))
		door_lock_actuator = 1;
	
	// Requirement-5
	if ((brake_pedal == 1) && (car_moving == 1))
		brake_actuator = 1;
	else brake_actuator = 0;
	
}

/* ---     You should not have to modify anything below this line ---------*/

int main()
{
	
	/*The main control loop which keeps the system alive and responsive for ever, 
	until the system is powered off */
	//for (; ; )
	{
		read_inputs_from_ip_if();
		control_action();
		write_output_to_op_if();

	}
	
	return 0;
}
