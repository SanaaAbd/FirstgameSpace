#pragma once

#ifndef MMENU_C

	#define MMENU_C
	
	mmenu* mmenu_create()
	{
		mmenu* m = (mmenu*)malloc(sizeof(mmenu));
		
		m->buttons = array_list_create();
		m->components = 0;
		
		return m;
	}
	void mmenu_destroy(mmenu* m)
	{
		for (int i = 0; i < m->buttons->length; i++)
			button_destroy((button*)array_list_get(m->buttons, i));
		array_list_destroy(m->buttons);
		free(m);
	}
	void mmenu_update(mmenu* m, game* g)
	{
		for (int i = 0; i < m->buttons->length; i++)
		{
			button* b = (button*)array_list_get(m->buttons, i);
			button_update(b);
		}
	}
	void mmenu_paint(mmenu* m)
	{
		DrawRectangle(m->x - (m->border_px / 2),
					  m->y - (m->border_px / 2),
					  m->width + m->border_px,
					  m->height + m->border_px,
					  m->border_colour);
		DrawRectangle(m->x, m->y, m->width, m->height, m->colour);
		
		for (int i = 0; i < m->buttons->length; i++)
		{
			button* b = (button*)array_list_get(m->buttons, i);
			button_paint(b);
		}
	}
	void mmenu_add_button(mmenu* m, int x, int y, const char* caption, size_t text_size, int id)
	{
		button* b = button_create(caption, x, y, text_size, id);
		
		array_list_push(m->buttons, b);
		m->components++;
	}

#endif
