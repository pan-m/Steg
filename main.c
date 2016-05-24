/*
 ============================================================================
 Name        : main.c of Steg
 Created on  : 2 Ιουλ 2014
 Author      : Panagiotis Michalopoulos
 Version     : 0.9
 Copyright   : Copyright(C) Panagiotis Michalopoulos
 Description : Entry point
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "definitions.h"


Vitals vitalInfo(FILE *);
unsigned char* createTable(int);
void parser(FILE *, unsigned char *, Vitals);
void encode(char* , unsigned char * );
void writeBack(unsigned char[PATH_MAX], char[PATH_MAX], char *, Vitals);
void intro(void);
void f_names(char *, char *);
char* get_message(char *);
void decode(unsigned char *, Vitals);
void arg_control(int, char *);
Args arg_parse(char *);
char get_mode();


/*
 * Works both from cmd and interactively
 * Only problem: when encoding with args it truncates the first letter
 * of the message and it doesn't saves it.
 *
 */



int main(int argc, char *argv[])
{
	FILE* bitmap;
	unsigned char* pixels;
	Vitals info;
	char* message;
	Args arguments;

	intro();

	if (argc > 1)
	{
		arg_control(argc, argv);
		arguments = arg_parse(argv);
	}
	else
	{
		arguments.mode = get_mode();
		f_names(arguments.f_input, "Give input file name: ");
		if (arguments.mode == 'e')
		{
			f_names(arguments.f_output, "Give output file name: ");
		}
	}


	bitmap = fopen(arguments.f_input, "rb");
	info = vitalInfo(bitmap);
	pixels = createTable(info.image_size);
	parser(bitmap,pixels,info);

	if (arguments.mode == 'e')
	{
		printf("\nThe given image is %d bytes.\nIt's dimensions are: %dx%d\n",info.size,info.width,info.height);
		printf("\nTherefore your message can be up to %d characters long.\n",info.image_size/8);
		message = get_message(message);
		printf("%s", message);

		encode(message,pixels);
		writeBack(pixels, arguments.f_input, arguments.f_output, info);
	}
	else
	{
		decode(pixels, info);
	}
	if (argc == 1)
	{
		system("PAUSE"); // The pause command is only executed when in iteractive mode.
	}
	return 0;
}
