/*
 ============================================================================
 Name        : input.c of Steg
 Created on  : 8 Ιουλ 2014
 Author      : Panagiotis Michalopoulos
 Version     : 0.9
 Copyright   : Copyright(C) Panagiotis Michalopoulos
 Description : Handling user I/O
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "definitions.h"

void intro(void)
{
	printf("*****************************************\n");
	printf("*    SST--Simple Steganography Tool     *\n");
	printf("* Copyright(C) Panagiotis Michalopoulos *\n");
	printf("*****************************************\n\n");
}


void f_names(char *name, char *text)
{
	do
	{
	printf("%s", text);
	scanf("%s",name); //FIXME: format string attack
	}while (access(name,F_OK) < 0);
}

char* get_message(char *message)
{
	int c;
	int i = 0;

	printf("Give your message: ");
	message = (char *)malloc(sizeof(char));

	c = getchar(); //FIXME: This is needed in iteractive mode for neutralizing the \n from previous scanf. In args mode it is not needed.
	while ((c = getchar()) != '\n')
	{
		*(message+i) = c;
		i++;
		message = realloc(message, (i+1)*sizeof(char));
	}
	message[i] = '\0';
	return message;
}

char get_mode()
{
	char mode;

	do
	{
	printf("Enter the desired mode (e/d): ");
	scanf("%c",&mode);
	}while ((mode != 'e') && (mode !='d'));
	return mode;
}


void arg_control(int argc, char *argv[]) //TODO: Poorly written. Needs revising.
{
	if (argc > 4)
	{
		printf("\nIncorrect arguments number!!\nMode \"-e\" takes exactly two arguments.\nMode \"-d\" takes exactly one argument.");
		exit(1);
	}
	if ((argc != 3) && (strncmp(argv[1], "-d", 2) == 0))
	{
		printf("\nThe \"-d\" mode takes exactly one argument.\n");
		exit(1);
	}
	if ((argc != 4) && (strncmp(argv[1], "-e", 2) == 0))
	{
		printf("\nThe \"-e\" mode takes exactly two arguments.\n");
		exit(1);
	}
	if (!strncmp(argv[1], "-d", 2) && !strncmp(argv[1], "-e", 2))
	{
		printf("\nMode \"%s\" not recognized\n", argv[1]);
		exit(1);
	}
}


Args arg_parse(char *argv[])
{
	Args arguments;

	if (strncmp(argv[1], "-e", 2) == 0)
	{
		arguments.mode = 'e';
		strncpy(arguments.f_input,argv[2],PATH_MAX);
		strncpy(arguments.f_output,argv[3],PATH_MAX);
	}
	else
	{
		arguments.mode = 'd';
		strncpy(arguments.f_input,argv[2],PATH_MAX);
	}
	return arguments;
}






