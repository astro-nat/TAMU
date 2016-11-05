/*
Lab-1, Problem-4, Sample soltion-2
Note: Only requirement 1,2,3,4 is covered 
modify this code to include requirement 5 also

Also add your own INPUT/OUTPUT code to test it.

*/

unsigned int input;  

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
    
    if(output == 0x1) bell = 1;
    
    if(output == ((0x1 | 0x2) || (0 | 0x2))) door_lock_actuator = 1;
    
    if(output == ((0x1 | 0x2 | 0x4) || (0 | 0x2 | 0x4) || (0x1 | 0 | 0x4) || (0 | 0 | 0x4))) brake_actuator = 1;
    
    if (bell = 1) printf("\nBell is on!");
    else if (bell = 0) printf("\nBell is off.");
    
    if (door_lock_actuator = 1) printf("\nDoor is locked.");
    else if (door_lock_actuator = 0) printf("\nDoor is not locked");
    
    if (brake_actuator = 1) printf("\nBrakes are activated.");
    else if (brake_actuator = 0) printf("\nBrakes are not activated");
    

}


//The code segment which implements the decision logic
inline void control_action(){

	//Requirement 1, 2, 3, 4 only
	switch (input & 0xff) //Change to 0xff for all 5 requirements
	{
		case 5:
		case 7:
		case 13:
			output = 1;
		break;

		case 32:
		case 34:
		case 36:
		case 38:
		case 40:
		case 42:
		case 44:
		case 46:
		case 49:
		case 51:
			output = 2;
		break;

		case 53:
		case 55:
			output = 3;
		break;

		case 57:
		case 59:
			output = 2;
		break;

		case 61:
			output = 3;
		break;

		case 63:
			output = 2;
	
	}


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
