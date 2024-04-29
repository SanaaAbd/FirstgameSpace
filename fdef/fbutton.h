#pragma once

#ifndef FBUTTON_H

	#define FBUTTON_H
	
	button* button_create(const char* caption, int x, int y, size_t text_size, int id);
	button* button_create_img(int x, int y, int id);
	void button_destroy(button* b);
	size_t button_get_width(button* b);
	size_t button_get_height(button* b);
	void button_update(button* b);
	void button_paint(button* b);

#endif
