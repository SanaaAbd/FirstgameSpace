#pragma once

/*
 * MMENU (Movable Menu) is basically the movable menu you see on the pause screen
 */

#ifndef MMENU_H

	#define MMENU_H
	
	typedef struct
	{
		int x;
		int y;
		int width;
		int height;
		int border_px;
		Color border_colour;
		Color colour;
		unsigned int components;
		array_list* buttons;
	} mmenu;

#endif
