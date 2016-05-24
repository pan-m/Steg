/*
 ============================================================================
 Name        : parser.c of Steg
 Created on  : 2 Ιουλ 2014
 Author      : Panagiotis Michalopoulos
 Version     : 0.9
 Copyright   : Copyright(C) Panagiotis Michalopoulos
 Description : Create bitmap by parsing the image
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"

unsigned char* createTable(int size)
{
	unsigned char *pixels;

	pixels = (unsigned char *) malloc(size);
	if (pixels==NULL)
	{
		printf("Not enough memory space. Leaving...");
		exit(2);
	}
	return pixels;
}
void parser(FILE *bitmap, unsigned char *table, Vitals info)
{
	int rows,cols,i,j;
	unsigned char temp;

	rows = info.height;

	switch((info.width*3)%4)
	{
		case 0:
			cols = info.width*3;
			break;
		case 1:
			cols = info.width*3 + 3;
			break;
		case 2:
			cols = info.width*3 + 2;
			break;
		case 3:
			cols = info.width*3 + 1;
			break;
	}

	fseek(bitmap,info.offset,SEEK_SET);

	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			fscanf(bitmap, "%c", &temp);
			table[cols*i+j] = temp;
		}
	}
}








