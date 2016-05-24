/*
 ============================================================================
 Name        : replace.c of Steg
 Created on  : 2 Ιουλ 2014
 Author      : Panagiotis Michalopoulos
 Version     : 0.9
 Copyright   : Copyright(C) Panagiotis Michalopoulos
 Description : All the work is done here
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definitions.h"


void encode(char* message, unsigned char* table)
{
	int i,j,k=0;
	unsigned char extractor = 0b10000000;
	unsigned char bit;

	for (i=0;i<=strlen(message);i++)
	{
		extractor = 0b10000000;
		for (j=0;j<8;j++)
		{
			bit = message[i] & extractor;
			if (bit == 0)
			{
				if (table[k]%2 == 1)
				{
					table[k] = table[k] - 1;
				}
			}
			else
			{
				if (table[k]%2 == 0)
				{
					table[k] = table[k] + 1;
				}
			}
			extractor = extractor >> 1;
			k++;
		}
	}
}

void decode(unsigned char *table, Vitals info)
{
	int i,j;
	unsigned char extractor = 0b00000001;
	unsigned char byte;

	for (i=0;i<info.image_size;i+=8)
	{
		byte = 0;
		for (j=0;j<8;j++)
		{
			byte += (table[i+j] & extractor)*pow(2,7-j);
			//printf("%d + ",byte);
		}
		//printf("= %c or %d\n",byte,byte);
		printf("%c",byte);
		if (byte == '\0')
			break;
	}
	printf("\n");
}


void writeBack(unsigned char *table, char f_input[PATH_MAX], char f_output[PATH_MAX], Vitals info)
{
	FILE *dest;
	int i,counter=0;
	char command[] = "copy /b ";

	strncat(command,f_input,PATH_MAX);
	strcat(command," ");
	strncat(command,f_output,PATH_MAX);
	system(command);
	printf("%s\n",f_output);
	dest = fopen(f_output,"rb+");

	fseek(dest,info.offset,SEEK_SET);
	//printf("OK");
	for(i=0;i<info.image_size;i++)
	{
		//printf("OK");
		fprintf(dest,"%c",table[i]);
		counter++;
		//printf("OK");
	}
	fclose(dest);
}


