#pragma once

#ifndef DIALOG_C

	#define DIALOG_C
	
	dialog* dialog_create()
	{
		dialog* d = (dialog*)malloc(sizeof(dialog));
		
		return d;
	}
	void dialog_destroy(dialog* d)
	{
		free(d->sender);
		free(d->lines);
		free(d);
	}
	void dialog_update(dialog* d, game* g)
	{
		if (IsKeyPressed(KEY_ENTER) ||
			IsKeyPressed(KEY_SPACE))
		{
			g->level++;
			game_set_level_type(g);
		}
	}
	void dialog_paint(dialog* d)
	{
		DrawRectangle(DIALOG_X - DIALOG_BORDER,
					  DIALOG_Y - (DIALOG_BORDER * 4),
					  DIALOG_WIDTH + DIALOG_BORDER * 2,
					  DIALOG_HEIGHT + DIALOG_BORDER,
					  d->border_colour);
		DrawRectangle(DIALOG_X, DIALOG_Y, DIALOG_WIDTH, DIALOG_HEIGHT - (DIALOG_BORDER * 4), d->colour);
		
		int centeredX = DIALOG_WIDTH - (MeasureText(d->sender, 30) / 2);
		centeredX -= (int)(DIALOG_WIDTH / 4.5);
		DrawText(d->sender, centeredX, DIALOG_Y - 30, 30, DIALOG_FONT_COLOUR);
		
		int by = DIALOG_Y + 60;
		
		for (int i = 0; i < d->lines_count; i++)
		{
			char* line = d->lines[i];
			
			int bx = DIALOG_WIDTH - (MeasureText(line, DIALOG_FONT_SIZE) / 2);
			bx -= (int)(DIALOG_WIDTH / 4.5);
			
			DrawText(line, bx, by, DIALOG_FONT_SIZE, DIALOG_FONT_COLOUR);
			
			by += DIALOG_FONT_SIZE;
		}
	}

#endif
