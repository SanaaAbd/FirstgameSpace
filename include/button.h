#pragma once

#ifndef BUTTON_H

	#define BUTTON_H
	
	typedef enum
	{
		button_text,
		button_image
	} button_type;
	
	typedef struct
	{
		char* caption;
		int x;
		int y;
		int id;
		size_t text_size;
		bool clicked;
		bool on_hover;
		button_type type;
		Texture2D tex;
	} button;

#endif
