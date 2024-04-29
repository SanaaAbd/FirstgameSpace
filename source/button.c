#pragma once

#ifndef BUTTON_C

	#define BUTTON_C
	
	button* button_create(const char* caption, int x, int y, size_t text_size, int id)
	{
		button* b = (button*)malloc(sizeof(button));
		
		b->caption = strdup(caption);
		b->x = x;
		b->y = y;
		b->text_size = text_size;
		b->clicked = false;
		b->on_hover = false;
		b->id = id;
		b->type = button_text;
		
		return b;
	}
	button* button_create_img(int x, int y, int id)
	{
		button* b = (button*)malloc(sizeof(button));
		
		b->x = x;
		b->y = y;
		b->id = id;
		b->clicked = false;
		b->on_hover = false;
		b->type = button_image;
		
		return b;
	}
	void button_destroy(button* b)
	{
		free(b->caption);
		if (b->type == button_image)
			UnloadTexture(b->tex);
		free(b);
	}
	size_t button_get_width(button* b)
	{
		if (b->type == button_text)
			return MeasureText(b->caption, b->text_size);
		else if (b->type == button_image)
			return b->tex.width;
		else
			return 0; // not implemented
	}
	size_t button_get_height(button* b)
	{
		if (b->type == button_text)
			return b->text_size;
		else if (b->type == button_image)
			return b->tex.height;
		else
			return 0; // not implemented
	}
	void button_update(button* b)
	{
		int mx = GetMousePosition().x;
		int my = GetMousePosition().y;
		
		if (mx >= b->x &&
			mx <= (b->x + button_get_width(b)) &&
			my >= b->y &&
			my <= (b->y + button_get_height(b)))
		{
			b->on_hover = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				b->clicked = true;
			else
				b->clicked = false;
		} else
		{
			b->on_hover = false;
			b->clicked = false;
		}
	}
	void button_paint(button* b)
	{
		if (b->type == button_text)
		{
			if (b->on_hover)
				DrawText(b->caption, b->x, b->y, b->text_size, WHITE);
			else
				DrawText(b->caption, b->x, b->y, b->text_size, GRAY);
		} else if (b->type == button_image)
		{
			if (b->on_hover)
				DrawTexture(b->tex, b->x, b->y, WHITE);
			else
				DrawTexture(b->tex, b->x, b->y, GRAY);
		}
	}

#endif
