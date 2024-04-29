#pragma once

#ifndef DIALOG_H

	#define DIALOG_H
	
	#define DIALOG_X 150
	#define DIALOG_Y 150
	#define DIALOG_WIDTH 500
	#define DIALOG_HEIGHT 300
	#define DIALOG_BORDER 10
	#define DIALOG_FONT_SIZE 20
	#define DIALOG_FONT_COLOUR WHITE
	
	typedef struct
	{
		char* sender;
		char** lines;
		size_t lines_count;
		Color colour;
		Color border_colour;
	} dialog;

#endif
