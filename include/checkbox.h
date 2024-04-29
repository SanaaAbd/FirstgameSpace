#pragma once

#ifndef CHECKBOX_H

	#define CHECKBOX_H
	
	#define CHECKBOX_WIDTH 25
	#define CHECKBOX_HEIGHT 25
	#define CHECKBOX_BORDER 2
	
	typedef struct
	{
		int id;
		int x;
		int y;
		bool on_hover;
		bool clicked;
		bool value;
	} checkbox;

#endif
