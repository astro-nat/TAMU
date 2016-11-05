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
#define DOS 0x10000000;
#define SBF 0x01000000;
#define ER 0x00100000;
#define DC 0x00010000;
#define KC 0x00001000;
#define DLL 0x00000100;
#define BP 0x00000010;
#define CM 0x00000001;

unsigned int bell = 0;
unsigned int door_lock_actuator = 0;
unsigned int brake_actuator = 0;

unsigned int input;
unsigned int final = 0x00000000;
unsigned int test;

void read_inputs_from_ip_if(){

	//place your input code here
	//to read the current state of the available sensors
    printf("Final: %d",final);
	printf("Driver in Seat? ");
	scanf("%d", &input);
    if (input == 1) {final = final | DOS;}
	printf("Final: %08x",final);
   
	printf("Seat Belt Fastened? ");
	scanf("%d", &input);
    if (input == 1) final = final | SBF;
    printf("Final: %08x",final);
    
	printf("Engine Running? ");
	scanf("%d", &input);
    if (input == 1) final = final | ER;
    printf("Final: %08x",final);
    
	printf("Doors Closed? ");
    scanf("%d", &input);
    if (input == 1) final = final | DC;
    printf("Final: %08x",final);
    
	printf("Key in Car?" );
    scanf("%d", &input);
    if (input == 1) final = final | KC;
    printf("Final: %08x",final);
    
	printf("Door Lock Lever activated? ");
    scanf("%d", &input);
    if (input == 1) final = final | DLL;
    printf("Final: %08x",final);
    
	printf("Brake Pedal pressed? ");
    scanf("%d", &input);
    if (input == 1) final = final | BP;
    printf("Final: %08x",final);
    
	printf("Car moving? ");
	scanf("%d",&input);
    if (input == 1) final = final | CM;
    printf("Final: %08x",final);
    
    printf("Hex code: %08x \n",final);
    printf("Decimal: %d \n",final);
    printf("(Test Decimal): %d \n",test);
    
	//scanf("Bell on? %d",&bell);
	//scanf("Door locked? %d", &door_lock_actuator);
	//scanf("Brake activated? %d",&brake_actuator);
	
}

void write_output_to_op_if(){

	//place your output code here
    //to display/print the state of the 3 actuators (DLA/BELL/BA)
	if(bell == 1) printf("\nBell is on!\n");
	else printf ("\nBell is off.\n");
	
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
    printf("La Final: %d", final);
    if (final < 0x10111111) bell = 1;
		
	// Requirement-2
    else if ((final >= 0x11100000) && (final <= 0x11101111)) {bell = 1;}
	//else bell = 0; // Requirement-3

	// Requirement-4
	else if ((final > 0x10001000) && (final <= 0x10001111)) door_lock_actuator = 0;
    //else if (final == (1<<8 | 1<<3)) door_lock_actuator = 1;
	
	// Requirement-5
	else if (final >= 0x00000011) brake_actuator = 1;
	//else brake_actuator = 0;
	
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
