/*
Sample Solution-1 for Lab-1, Problem-4
Add your own INPUT/OUTPUT code to test it.
*/
#include <stdio.h>
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
unsigned int final = 0x00;
unsigned int test;

unsigned int output;  



//For input interface implementation
inline void read_inputs_from_ip_if(){

		/* write your own input code */
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
    //printf("Final: %08x",final);
    
    //printf("Hex code: %08x \n",final);
    //printf("Decimal: %d \n",final);
    //printf("(Test Decimal): %d \n",test);
    
    //scanf("Bell on? %d",&bell);
    //scanf("Door locked? %d", &door_lock_actuator);
    //scanf("Brake activated? %d",&brake_actuator);


}

//For output interface implementation
inline void write_output_to_op_if(){

    //place your output code here
    //to display/print the state of the 3 actuators (DLA/BELL/BA)
    door_lock_actuator = 0;
    bell = 0;
    brake_actuator = 0;
    
    //if(output == 0x1) bell = 1;
    
    if(output == ((0x1 | 0x2) || (0 | 0x2))) door_lock_actuator = 1;
    
    if(output == ((0x1 | 0x2 | 0x4) || (0 | 0x2 | 0x4) || (0x1 | 0 | 0x4) || (0 | 0 | 0x4))) brake_actuator = 1;
    
    if (bell = 1) printf("\nBell is on!");
    printf("Bell: %d",bell);
    else printf("\nBell is off.");
    
    if (door_lock_actuator = 1) printf("\nDoor is locked.");
    else if (door_lock_actuator = 0) printf("\nDoor is not locked");
    
    if (brake_actuator = 1) printf("\nBrakes are activated.");
    else if (brake_actuator = 0) printf("\nBrakes are not activated");
    

}


//The code segment which implements the decision logic
inline void control_action(){

	//Reset output
	output = 0;
	
	//Requirement 1, 2, 3
	switch (final)
	{
		case 5:
		case 7:
		case 13:
			output =  0x1;
	}

	//Requirement 4
	switch (final)
	{
		case 32:
		case 49:
			output = output | 0x2;
	}

	//Requirement 5
	if ((final) == 0xc0)
			output = output | 0x4;

}


//The main program
int main(int argc, char *argv[])
{
	
	/*The main control loop which keeps the system alive and responsive for ever, 
	until the system is powered off */
	for (; ; )
	{
		read_inputs_from_ip_if();
		control_action();
		write_output_to_op_if();

	}
	
	return 0;
}
