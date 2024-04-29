#pragma once

#ifndef FMMENU_H

	#define FMMENU_H
	
	mmenu* mmenu_create();
	void mmenu_destroy(mmenu* m);
	void mmenu_update(mmenu* m, game* g);
	void mmenu_paint(mmenu* m);
	void mmenu_add_button(mmenu* m, int x, int y, const char* caption, size_t text_size, int id);

#endif
