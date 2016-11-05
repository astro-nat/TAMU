#include <stdio.h> //For input/output
#include <sys/time.h> //For gettimeofday() function

int main()
{
	unsigned int unsigned_int_var;
	double double_var;
	long long_var;
	long long longlong_var;
	char char_var;
	float float_var;
	struct timeval struct_timeval_var;
	
	FILE *my_file_pointer;
	if ( (my_file_pointer = fopen("lab1_prob2_out.txt", "w")) == NULL)
	{
		printf("Error opening the file, so exiting\n");
		exit(1);
	}
	
	fprintf(my_file_pointer,"Unsigned int data type is %d bits or %d bytes long.\n",sizeof(unsigned_int_var),sizeof(unsigned_int_var)*8);
	printf("Unsigned int data type is %d bytes or %d bits long\n",sizeof(unsigned_int_var), sizeof(unsigned_int_var)*8 );  
	
	fprintf(my_file_pointer,"Double data type is %d bits or %d bytes long.\n",sizeof(double_var),sizeof(double_var)*8);
	printf("Double data type is %d bytes or %d bits long\n",sizeof(double_var), sizeof(double_var)*8);
	
	fprintf(my_file_pointer,"Long data type is %d bits or %d bytes long.\n",sizeof(long_var),sizeof(long_var)*8);
	printf("Long data type is %d bytes or %d bits long\n",sizeof(long_var),sizeof(long_var)*8);
	
	fprintf(my_file_pointer,"Long long data type is %d bits or %d bytes long.\n",sizeof(longlong_var),sizeof(longlong_var)*8);
	printf("Long long data type is %d bytes or %d bites long\n",sizeof(longlong_var),sizeof(longlong_var)*8);
	
	fprintf(my_file_pointer,"Char data type is %d bits or %d bytes long.\n",sizeof(char_var),sizeof(char_var)*8);
	printf("Char data type is %d bits or %d bytes long.\n",sizeof(char_var),sizeof(char_var)*8);
	
	fprintf(my_file_pointer,"Float data type is %d bits or %d bytes long.\n",sizeof(float_var),sizeof(float_var)*8);
	printf("Float data type is %d bits or %d bytes long.\n",sizeof(float_var),sizeof(float_var)*8);
	
	fprintf(my_file_pointer,"Struct timeval data type is %d bits or %d bytes long.\n",sizeof(struct_timeval_var),sizeof(struct_timeval_var)*8);
	printf("Struct timeval data type is %d bits or %d bytes long.\n",sizeof(struct_timeval_var),sizeof(struct_timeval_var)*8);
	
	
	return 0;
}