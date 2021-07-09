#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t ConvertHexStrToArray(const char *hex_str, uint8_t * array)
{
	size_t i, array_size = strlen(hex_str)/2;
	char t[3];
	
	for(i = 0; i < array_size; i++){
		memcpy(t,(hex_str + i *2),2);
		t[2] = '\0';
		*(array + i) = (uint8_t)strtoul(t, NULL, 16);	
	}
	return array_size;

}
 
 
int main()
{
	char *hex_str = "4ee2f02f";
	uint8_t array[16];
	
	size_t array_size = ConvertHexStrToArray(hex_str, array);
	for(int i = 4; i < 16; i++)
		array[i] = 0x00;

	printf("Converted : ");
	for(size_t i = 0; i < array_size; i++){
		printf("%02X\t", array[i]);
	} 
	printf("\n");

 
}


