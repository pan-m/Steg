/*
 ============================================================================
 Name        : definitions.h of Steg
 Created on  : 2 Ιουλ 2014
 Author      : Panagiotis Michalopoulos
 Version     : 0.9
 Copyright   : Copyright(C) Panagiotis Michalopoulos
 Description : Program specific structures
 ============================================================================
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include <limits.h>

typedef struct Vitals
	{
		int size;
		int offset;
		int width;
		int height;
		int image_size;
	}Vitals;

typedef struct Args
{
	char mode;
	char f_input[PATH_MAX];
	char f_output[PATH_MAX];
}Args;

#define TRUE 1
#define FALSE 0

#endif /* DEFINITIONS_H_ */
