//CSCE 312: Lab-1 Problem-5 framework
// This is version-2; bugfix for timediff
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

#if defined(sun)
    #define CLOCKNAME CLOCK_HIGHRES
        
#else
    #define CLOCKNAME CLOCK_PROCESS_CPUTIME_ID
#endif

unsigned int driver_on_seat = 1<<8;
unsigned int driver_seat_belt_fastened = 1<<7;
unsigned int engine_running = 1<<6;
unsigned int doors_closed = 1<<5;
unsigned int key_in_car = 1<<4;
unsigned int door_lock_lever = 1<<3;
unsigned int brake_pedal = 1<<2;
unsigned int car_moving = 1<<1;
unsigned int bell = 0;
unsigned int door_lock_actuator = 0;
unsigned int brake_actuator = 0;

unsigned int temp;
unsigned int final;
unsigned int test;


//The code segment which implements the decision logic
inline void control_action(){

// Put your control/decision logic code segments inside this function
// This is the actual code whose execution time which is being measure
    // Requirement-1
    if (final == (1<<8 | 0<<7 | 1<<6)) bell = 1;
    else bell = 0;
    
    // Requirement-2
    if (final == (1<<8 | 1<<6 | 0<<5)) bell = 1;
    else bell = 0; // Requirement-3
    
    // Requirement-4
    if (final == (1<<8 | 1<<4)) door_lock_actuator = 0;
    else if (final == (1<<8 | 1<<3)) door_lock_actuator = 1;
    
    // Requirement-5
    if (final == (1<<2 | 1<<1)) brake_actuator = 1;
    else brake_actuator = 0;


}


inline void read_inputs_from_ip_if(){

	//place your input code here
	//to read the current state of the available sensors

    printf("Driver in Seat? ");
    scanf("%d", &temp);
    final = (temp)<<8;
    test = (temp)*256;
    
    
    printf("Seat Belt Fastened? ");
    scanf("%d", &temp);
    driver_seat_belt_fastened = (temp)<<7;
    final = final|driver_seat_belt_fastened;
    test = test+(temp)*128;
    
    printf("Engine Running? ");
    scanf("%d", &temp);
    engine_running = (temp)<<6;
    final = engine_running|final;
    test = test+(temp)*64;
    
    printf("Doors Closed? ");
    scanf("%d", &temp);
    doors_closed = (temp)<<5;
    final = doors_closed|final;
    test = test+(temp)*32;
    
    printf("Key in Car?" );
    scanf("%d", &temp);
    key_in_car = (temp)<<4;
    final = key_in_car|final;
    test = test+(temp)*16;
    
    printf("Door Lock Lever activated? ");
    scanf("%d", &temp);
    door_lock_lever = (temp)<<3;
    final = door_lock_lever|final;
    test = test+(temp)*8;
    
    printf("Brake Pedal pressed? ");
    scanf("%d", &temp);
    brake_pedal = (temp)<<2;
    final = brake_pedal|final;
    test = test+(temp)*4;
    
    printf("Car moving? ");
    scanf("%d",&temp);
    car_moving = (temp)<<1;
    final = car_moving|final;
    test = test+(temp)*2;
    
    printf("Hex code: %02x \n",final);
    printf("Decimal: %d \n",final);
    printf("(Test Decimal): %d \n",test);
    //scanf("Bell on? %d",&bell);
    //scanf("Door locked? %d", &door_lock_actuator);
    //scanf("Brake activated? %d",&brake_actuator);

}

inline void write_output_to_op_if(){

	//place your output code here
    //to display/print the state of the 3 actuators (DLA/BELL/BA)
	
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
	control_action();                 // process the sensors
	clock_gettime(CLOCKNAME, &time2);   // get current time

	write_output_to_op_if();    // output the values of the actuators
	
	timeDiff = diff(time1,time2); // compute the time difference

	printf("Timer Resolution = %u nanoseconds \n ",timeres.tv_nsec);
	printf("Calibrartion time = %u seconds and %u nanoseconds \n ", calibrationTime.tv_sec, calibrationTime.tv_nsec);
    printf("The measured code took %u seconds and ", timeDiff.tv_sec - calibrationTime.tv_sec);
	printf(" %u nano seconds to run \n", timeDiff.tv_nsec - calibrationTime.tv_nsec);
	
	return 0;
}
