/**
This is a C Implementation of the Zorro Cipher designed by Gerard et al.

The MIT License (MIT)

Copyright (c) 2015 Christian Walter

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zorro.h"
#include <time.h>

uint8_t key[16];

void key_copy(uint8_t *a, uint8_t *b){
	for(int i = 0; i < 16; i++){
		a[i] = b[i];
	}

}


int array_element_equal(uint8_t *a, uint8_t *b, int size){
	int i, j, s1=0, s2=0;

	for(i = 0; i<size; i++)
		for(j = 0; j < size; j++)
			if(a[i] == b[j]){
				s1++;				
				break;
			}
	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++)
			if(b[i] == a[j]){
				s2++;
				break;
			}

	if(s1 == s2 && s1 == size)
		return 1;
	else
		return 0;



}



void ConvertHexStrToArray(const char *hex_str, uint8_t * array)
{
	size_t i; //, array_size = strlen(hex_str)/2;
	size_t array_size = 16;
	char t[3];
	
	for(i = 0; i < array_size; i++){
		memcpy(t,(hex_str + i *2),2);
		t[2] = '\0';
		*(array + i) = (uint8_t)strtoul(t, NULL, 16);	
	}

}





void state_xor(uint8_t *state1, uint8_t *state2){

	
	for(int i = 0; i < 16; i++)
		state1[i] = state1[i] ^ state2[i];
}


void printState(char * text, uint8_t * state)	{
	int i;
	printf("%s: ", text);
	for(i=0; i<16; i++)	{
		printf("%02X ", state[i]);
	}
	printf("\n");
}

void PGV_11(uint8_t *state, uint8_t *iv){
	key_copy(key, state);

	state_xor(key, iv);
		
	
	zorroCompleteEnc(state,key);
	
	state_xor(state, iv);
		
	
}

void gen_iv(uint8_t *iv){
	srand(time(NULL));
	int i;
	uint8_t a;

	for(i = 0; i < 16; i++){
		a = rand()%256;
		iv[i] = a;
	}

}

void gen_state(uint8_t *state, uint8_t *state2){
	srand(time(NULL));
	int i,j, cnt=0;
	uint8_t diff[4] = {0, 158, 22, 175};
	uint8_t diff2[4] = {0, 136, 22, 149};
	uint8_t a;
	
	for(i = 0; i < 16; i+=4){
		for(j = 0; j < 4; j++){
			
			a = rand()% 256;
			if((cnt%2) == 0){
				state[i + j] = a;
				state2[i + j] = a ^ diff[j];

			}else{
				state[i + j] = a;
				state2[i + j] = a ^ diff2[j];
			}
		}
			cnt++;
	}
	/*
	for(i = 0; i < 16; i++){
		a = rand()%256;
		iv[i] = a;
	}

*/
}

void print_diff(uint8_t *state, uint8_t *state2){
	
	int i;
	for(i = 0; i < 16; i++){
		if((i%4) == 0)
			printf("-----------------------\n");
		printf("%d\n", state[i] ^ state2[i]);
	}

}

int main()	{
	uint64_t i,j;	

	uint8_t state[16];

	uint8_t state2[16];

	//uint8_t iv[16] = {141, 2, 166, 169, 186, 25, 184, 73, 190, 135, 102, 20, 104, 107, 22, 224};
	
	uint8_t iv[16] = {74, 225, 124, 126, 117, 133, 126, 42, 107, 179, 114, 152, 163, 152, 50, 250};

	uint8_t initial_state[16];	
	uint8_t initial_state2[16];	

	for(i = 0; i < 1; i++){
		//gen_iv(iv);
		for(j = 0; j < 0x1; j++){
			if((j % 1000000) == 0)
				printf("%llu\n", j);	
			gen_state(state, state2);

			//print_diff(state, state2);
		
			key_copy(initial_state, state);
			key_copy(initial_state2, state2);


			PGV_11(state, iv);
			PGV_11(state2, iv);
	
			if(array_element_equal(state, state2, 16)){
		
			printf("try: %llud\n", j);
	
			printState("initial_state1: ", initial_state);
			printState("initial_state2: ", initial_state2);


			printState("state1: ", state);
			printState("state2: ", state2);
			break;	
			}
		}
	}
}
