#pragma once

#ifndef CHECKBOX_C

	#define CHECKBOX_C
	
	checkbox* checkbox_create(int id, int x, int y)
	{
		checkbox* c = (checkbox*)malloc(sizeof(checkbox));
		
		c->id = id;
		c->x = x;
		c->y = y;
		c->value = false;
		c->on_hover = false;
		c->clicked = false;
		
		return c;
	}
	void checkbox_destroy(checkbox* c)
	{
		free(c);
	}
	void checkbox_update(checkbox* c, game* g)
	{
		int mx = GetMousePosition().x;
		int my = GetMousePosition().y;
		
		if (mx >= c->x &&
			my >= c->y &&
			mx <= (c->x + CHECKBOX_WIDTH) &&
			my <= (c->y + CHECKBOX_HEIGHT))
		{
			c->on_hover = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				c->clicked = true;
			else
				c->clicked = false;
		} else
		{
			c->on_hover = false;
			c->clicked = false;
		}
		
		if (c->clicked)
			c->value = !c->value;
	}
	void checkbox_paint(checkbox* c)
	{
		DrawRectangle(c->x, c->y, CHECKBOX_WIDTH, CHECKBOX_HEIGHT, GRAY);
		Color co = DARKGRAY;
		if (c->value)
			co = WHITE;
		DrawRectangle(
			c->x + CHECKBOX_BORDER,
			c->y + CHECKBOX_BORDER,
			CHECKBOX_WIDTH - CHECKBOX_BORDER * 2,
			CHECKBOX_HEIGHT - CHECKBOX_BORDER * 2,
			co);
	}

#endif
