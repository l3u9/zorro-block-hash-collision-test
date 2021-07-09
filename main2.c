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
#include <time.h>
#include "zorro.h"
#include "header.h"

uint8_t find_state[16];
uint8_t find_state2[16];

uint8_t sbox[256] = {
	0xB2, 0xE5, 0x5E, 0xFD, 0x5F, 0xC5, 0x50, 0xBC, 0xDC, 0x4A, 0xFA, 0x88, 0x28, 0xD8, 0xE0, 0xD1,
	0xB5, 0xD0, 0x3C, 0xB0, 0x99, 0xC1, 0xE8, 0xE2, 0x13, 0x59, 0xA7, 0xFB, 0x71, 0x34, 0x31, 0xF1,
	0x9F, 0x3A, 0xCE, 0x6E, 0xA8, 0xA4, 0xB4, 0x7E, 0x1F, 0xB7, 0x51, 0x1D, 0x38, 0x9D, 0x46, 0x69,
	0x53, 0x0E, 0x42, 0x1B, 0x0F, 0x11, 0x68, 0xCA, 0xAA, 0x06, 0xF0, 0xBD, 0x26, 0x6F, 0x00, 0xD9,
	0x62, 0xF3, 0x15, 0x60, 0xF2, 0x3D, 0x7F, 0x35, 0x63, 0x2D, 0x67, 0x93, 0x1C, 0x91, 0xF9, 0x9C,
	0x66, 0x2A, 0x81, 0x20, 0x95, 0xF8, 0xE3, 0x4D, 0x5A, 0x6D, 0x24, 0x7B, 0xB9, 0xEF, 0xDF, 0xDA,
	0x58, 0xA9, 0x92, 0x76, 0x2E, 0xB3, 0x39, 0x0C, 0x29, 0xCD, 0x43, 0xFE, 0xAB, 0xF5, 0x94, 0x23,
	0x16, 0x80, 0xC0, 0x12, 0x4C, 0xE9, 0x48, 0x19, 0x08, 0xAE, 0x41, 0x70, 0x84, 0x14, 0xA2, 0xD5,
	0xB8, 0x33, 0x65, 0xBA, 0xED, 0x17, 0xCF, 0x96, 0x1E, 0x3B, 0x0B, 0xC2, 0xC8, 0xB6, 0xBB, 0x8B,
	0xA1, 0x54, 0x75, 0xC4, 0x10, 0x5D, 0xD6, 0x25, 0x97, 0xE6, 0xFC, 0x49, 0xF7, 0x52, 0x18, 0x86,
	0x8D, 0xCB, 0xE1, 0xBF, 0xD7, 0x8E, 0x37, 0xBE, 0x82, 0xCC, 0x64, 0x90, 0x7C, 0x32, 0x8F, 0x4B,
	0xAC, 0x1A, 0xEA, 0xD3, 0xF4, 0x6B, 0x2C, 0xFF, 0x55, 0x0A, 0x45, 0x09, 0x89, 0x01, 0x30, 0x2B,
	0xD2, 0x77, 0x87, 0x72, 0xEB, 0x36, 0xDE, 0x9E, 0x8C, 0xDB, 0x6C, 0x9B, 0x05, 0x02, 0x4E, 0xAF,
	0x04, 0xAD, 0x74, 0xC3, 0xEE, 0xA6, 0xF6, 0xC7, 0x7D, 0x40, 0xD4, 0x0D, 0x3E, 0x5B, 0xEC, 0x78,
	0xA0, 0xB1, 0x44, 0x73, 0x47, 0x5C, 0x98, 0x21, 0x22, 0x61, 0x3F, 0xC6, 0x7A, 0x56, 0xDD, 0xE7,
	0x85, 0xC9, 0x8A, 0x57, 0x27, 0x07, 0x9A, 0x03, 0xA3, 0x83, 0xE4, 0x6A, 0xA5, 0x2F, 0x79, 0x4F
};

//uint8_t iv[16];
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

	//key_copy(iv, state);	
		
	
}


void gen_state(uint8_t *state, uint8_t *state2){
	srand(time(NULL));
	int i,j, cnt=0;
	//uint8_t diff[4] = {0, 85, 0, 42};
	//uint8_t diff2[4] = {123, 136, 35, 131};
	
	uint8_t diff[4] = { 0, 85, 0, 42 };
	uint8_t diff2[4] = { 123, 136, 35, 131};
	
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
	uint8_t round = 3;
	
	//zorroOneRoundEnc(state, round);

	
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

void gen_iv(uint8_t *iv){
	srand(time(NULL));
	int i;
	uint8_t a;

	for(i = 0; i < 16; i++){
		a = rand()%256;
		iv[i] = a;
	}

}

void test(uint8_t *state, uint8_t *iv){
	int i;
	key_copy(key, state);
	state_xor(key, iv);
	state_xor(state, key);
	
	for(i = 0; i < 3; i++){
		zorroOneRoundEnc(state, 1);
	}
	
			


}

void do_sbox(uint8_t *state){
	int i;
	for(i = 0; i < 16; i++)
		state[i] = sbox[state[i]];

	
}

void gen_round4(uint8_t *state, uint8_t *state2){
	srand(time(NULL));
	int i, j, cnt;

	uint8_t diff[16] = {123, 136, 35, 131};
	uint8_t diff2[16] = {0, 85, 0, 42};

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




}


int main()	{
	//uint8_t state[16];
	//uint8_t state2[16];

	//test();

	uint8_t iv[16] = {234,116,234,213,159,135,211,35,229,42,55,239,204,240,198,222};

	uint8_t state[16] = {0x4e, 0xe2, 0xf0, 0x2f, 0x96, 0x3a, 0xc1, 0x1b, 0xeb, 0x66, 0xba, 0x52, 0xbc, 0xba, 0x9c, 0x00};

	uint8_t state2[16] = {0x4e, 0x7c, 0xe6, 0x80, 0x96, 0xb2, 0xd7, 0x8e, 0xeb, 0xf8, 0xac, 0xfd, 0xbc, 0x32, 0x8a, 0x95};

	uint8_t key[16];

	uint8_t key2[16];
	
	gen_round4(state, state2);

	printState("state1: ", state);
	printState("state2: ", state2);
	
	for(int i = 0; i < 3; i++){
		zorroOneRoundDec(state, 1);
		zorroOneRoundDec(state2, 1);
	}
	
	key_copy(key, state);	
	key_copy(key2, state2);	

	state_xor(key, iv);
	state_xor(key2, iv);
		
	state_xor(state, key);
	state_xor(state2, key2);


	//PGV_11(state,iv);
	//PGV_11(state2, iv);

//	printState("state1: ", state);
//	printState("state2: ", state2);
	
	print_diff(state, state2);
		
	for(int i = 0; i < 4; i++){
		if(i == 3){
			printf("3라운드\n");		
			print_diff(state,state2);
			printf("\n");		
		}		

		zorroOneRoundEnc(state, 1);
		zorroOneRoundEnc(state2, 1);
	}	

	printState("state1: ", state);
	printState("state2: ", state2);
	
	
	print_diff(state, state2);	

	printf("\n");
//	state_xor(state, key);
//	state_xor(state2, key2);
	
	print_diff(state, state2);

	state_xor(state, iv);
	state_xor(state2, iv);
	
	printState("state1: ", state);
	printState("state2: ", state2);
	print_diff(state, state2);

/*
	for(int i = 0; i < 3; i++){
		zorroOneRoundEnc(state,1);
		zorroOneRoundEnc(state2,1);
	}
	
	print_diff(state, state2);
	printf("\n");

	do_sbox(state);
	do_sbox(state2);
	
	print_diff(state, state2);
	printf("\n");
*/

/*
	gen_round4(state, state2);

	for(int i = 0; i < 3; i++){
		zorroOneRoundDec(state,1);
		zorroOneRoundDec(state2,1);
	}

	PGV_11(state, iv);
	PGV_11(state2, iv);
	
	printState("state1: ",state);
	printState("state2: ", state2);
	
	print_diff(state, state2);
	printf("\n");

	//do_sbox(state);
	//do_sbox(state2);

	//print_diff(state, state2);

*/

/*
	printf("[Stage1]\n");
	printState("state1: ", state);
	printState("state2: ", state2);
	
	for(int i = 0; i < 3; i++){
		zorroOneRoundEnc(state,1);
		zorroOneRoundEnc(state2, 1);
	}

	do_sbox(state);
	do_sbox(state2);
	
	print_diff(state, state2);
	for(int i = 0; i < 3; i++){
		//test(state,iv);
		//test(state2, iv);
		PGV_11(state, iv);
		PGV_11(state2, iv);
	}

	printf("\n\n");
	print_diff(state, state2);


	printState("state1: ", state);
	printState("state2: ", state2);
	printf("[Stage2]\n");




	gen_round4(state, state2);
	printState("state1: ", state);
	printState("state2: ", state2);
	print_diff(state, state2);
	
	for(int i = 0; i < 3; i++){
		zorroOneRoundDec(state,1);
		zorroOneRoundDec(state2,1);
	}
	
	printf("\n\n");

	for(int i = 0; i < 3; i++){
		//test(state, iv);
		//test(state2, iv);
		PGV_11(state, iv);
		PGV_11(state2, iv);
	}

	print_diff(state, state2);
	printState("state1: ", state);
	printState("state2: ", state2);
*/

/*	
	test(state, iv);
	test(state2, iv);
	printState("state1: ", state);
	printState("state2: ", state2);

	print_diff(state, state2);

	do_sbox(state);
	do_sbox(state2);
	
	printState("state1: ", state);
	printState("state2: ", state2);

	print_diff(state, state2);
*/



/*
	PGV_11(state, iv);
	PGV_11(state2, iv);
	printState("state1: ", state);
	printState("state2: ", state2);
*/



/*
	for(int j = 0; j < 1; j++){
		
		//PGV_11(state, iv);
		//PGV_11(state2, iv);
		//zorroCompleteEnc(state, iv);
		//zorroCompleteEnc(state2, iv);
		if(array_element_equal(state, state2,16)){
			printf("index: %d\n", j);
			printState("state1: ", state);
			printState("state2: ", state2);
		}
	}
	//printState("PGV test:", state);
	
	//printState("PGV test2:", state2);
*/	

}
