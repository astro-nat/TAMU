//CSCE312: Lab-3 Problem-1 Timing Framework

/* ***   README   **** */
/*This file is a framework: i.e. there is no actual code whose execution time will be
measured. You need to populate the appropriate functions with the code that you wrote 
for the previous problems in order to get useful data. 

Turning in this file without your code will result in zero points being awarded for this problem.

run this file as: gcc FileName.c -o ExecutableName -lrt 

*/


#include <stdio.h>
#include <time.h>
// Macro definitions to ensure portablity between both sun.cs and linux.cs

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

#if defined(sun)
    #define CLOCKNAME CLOCK_HIGHRES
        
#else
    #define CLOCKNAME CLOCK_PROCESS_CPUTIME_ID
#endif
    

inline void read_inputs_from_ip_if(){
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

inline void write_output_to_op_if(){
    
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
inline void control_action(){

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

/*timespec diff from
http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
*/
struct timespec diff(struct timespec start, struct timespec end)
 {
    struct timespec temp;
    //the if condition handles time stamp end being smaller than than 
    //time stamp start which could lead to negative time.

     if ((end.tv_nsec-start.tv_nsec)<0) {
          temp.tv_sec = end.tv_sec-start.tv_sec-1;
          temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
      } else {
          temp.tv_sec = end.tv_sec-start.tv_sec;
          temp.tv_nsec = end.tv_nsec-start.tv_nsec;
      }
  return temp;
 }

int main(int argc, char *argv[])
{
	unsigned int cpu_mhz;
	unsigned long long int begin_time, end_time;
	struct timespec timeDiff,timeres;
	struct timespec time1, time2, calibrationTime;
	
    clock_gettime(CLOCKNAME, &time1);
	clock_gettime(CLOCKNAME, &time2);
	calibrationTime = diff(time1,time2); //calibration for overhead of the function calls
    clock_getres(CLOCKNAME, &timeres);  // get the clock resolution data
	
    read_inputs_from_ip_if(); // get the sensor inputs
	
	clock_gettime(CLOCKNAME, &time1); // get current time
	control_action();       // process the sensors
	clock_gettime(CLOCKNAME, &time2);   // get current time

	write_output_to_op_if();    // output the values of the actuators
	
	timeDiff = diff(time1,time2); // compute the time difference

	printf("Timer Resolution = %u nanoseconds \n ",timeres.tv_nsec);
	printf("Calibrartion time = %u seconds and %u nanoseconds \n ", calibrationTime.tv_sec, calibrationTime.tv_nsec);
    printf("The measured code took %u seconds and ", timeDiff.tv_sec - calibrationTime.tv_sec);
	printf(" %u nano seconds to run \n", timeDiff.tv_nsec - calibrationTime.tv_nsec);
	
	return 0;
}
