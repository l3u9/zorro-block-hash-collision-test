#define MAX_LEN 100
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
	FILE *fa, *fb;
	uint32_t random = 0;
	uint32_t plain_a = 0x00, plain_b = 0x00;	

	fa = fopen("textA.txt", "w");
	fb = fopen("textB.txt", "w");
	
	srand((unsigned)time(NULL));
	
	for(int i = 0; i < 16777216; i++){
		random = rand() % 0xffffffff;
		plain_a = random;
		plain_b = plain_a ^ 10360495;
		
		fprintf(fa, "%x\n", plain_a);
		fprintf(fb, "%x\n", plain_b); 

	} 


	return 0;


}


