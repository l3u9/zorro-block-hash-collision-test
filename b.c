#include<stdio.h>
#include<stdlib.h>

int main(){


	for(int i = 0; i < 10000; i++){
		uint8_t a = i;
		a = a * 5;
		if(a == 55){
			printf("%d\n", i);
		//	break;
		}
	}




}


