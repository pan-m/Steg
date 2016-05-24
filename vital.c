/*
 ============================================================================
 Name        : vital.c of Steg
 Created on  : 2 Ιουλ 2014
 Author      : Panagiotis Michalopoulos
 Version     : 0.9
 Copyright   : Copyright(C) Panagiotis Michalopoulos
 Description : Function for retrieving file info
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"

Vitals vitalInfo(FILE *bitmap)
{
	Vitals info;
	short int format;

	fscanf(bitmap, "%2c", &format);
	if (format != 0x4D42)
	{
			printf("Not a BMP. Leaving...");
			exit(1);
	}

	fseek(bitmap, 2, SEEK_SET);
	fscanf(bitmap, "%4c", &info.size);

	fseek(bitmap, 10, SEEK_SET);
	fscanf(bitmap, "%4c", &info.offset);

	fseek(bitmap, 18, SEEK_SET);
	fscanf(bitmap, "%4c", &info.width);
	fscanf(bitmap, "%4c", &info.height);

	fseek(bitmap, 34, SEEK_SET);
	fscanf(bitmap, "%4c", &info.image_size);

	return info;
}
