#pragma once

#ifndef UTIL_C

	#define UTIL_C
	
	// DEFINITION
	
	int util_random(int low, int up);
	bool util_random_bool();
	void util_draw_rotated(Texture2D* t, int x, int y, float rotation, Color c);
	
	// IMPLEMENTATION
	
	int util_random(int low, int up)
	{
		return rand() % (up - low - 1) + low;
	}
	bool util_random_bool()
	{
		return util_random(0, 100) < 50;
	}
	void util_draw_rotated(Texture2D* t, int x, int y, float rotation, Color c)
	{
		Rectangle r1 =
		{
			0.0f,
			0.0f,
			(float)t->width,
			(float)t->height
		};
		Rectangle r2 =
		{
			(float)x + ((float)t->width / 2.0f),
			(float)y + ((float)t->height / 2.0f),
			(float)t->width,
			(float)t->height
		};
		Vector2 v =
		{
			(float)t->width / 2.0f,
			(float)t->height / 2.0f
		};
		
		DrawTexturePro(*t, r1, r2, v, rotation, c);
	}

#endif
