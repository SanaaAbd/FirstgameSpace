#pragma once

#ifndef BULLET_C

	#define BULLET_C
	
	#define BULLET_WIDTH 2
	#define BULLET_HEIGHT 15
	
	entity_bullet* entity_bullet_create(float x, float y, float xs, float ys, int damage)
	{
		entity_bullet* b = (entity_bullet*)malloc(sizeof(entity_bullet));
		
		b->x = x;
		b->y = y;
		b->speedx = xs;
		b->speedy = ys;
		b->damage = damage;
		b->disposed = false;
		
		return b;
	}
	void entity_bullet_destroy(entity_bullet* b)
	{
		free(b);
	}
	// TODO: find a better way to transfer these arraylists
	void entity_bullet_update(entity_bullet* b, game* g)
	{
		b->x += b->speedx;
		b->y += b->speedy;
		
		if (b->y < -BULLET_HEIGHT)
		{
			b->disposed = true;
		}
		if (b->y < 0)
			b->disposed = true;
		for (int i = 0; i < g->entities->length; i++)
		{
			entity_alien* ea = (entity_alien*)array_list_get(g->entities, i);
			if (ea != NULL)
			{
				if (!ea->disposed)
				{
					if (b->x >= ea->x &&
						b->y >= ea->y &&
						b->x <= ea->x + ALIEN_WIDTH &&
						b->y <= ea->y + ALIEN_HEIGHT)
					{
						ea->health -= b->damage;
						b->disposed = true;
					}
				}
			}
		}
		for (int i = 0; i < g->asteroids->length; i++)
		{
			entity_asteroid* ea = (entity_asteroid*)array_list_get(g->asteroids, i);
			if (ea != NULL)
			{
				if (!ea->disposed)
				{
					if (b->x >= ea->x &&
						b->y >= ea->y &&
						b->x <= ea->x + ASTEROID_WIDTH &&
						b->y <= ea->y + ASTEROID_HEIGHT)
					{
						int neh = ea->health - b->damage;
						if (neh <= 0)
							ea->killed_by_player = true;
						ea->health = neh;
						
						entity_asteroid_spawn_particle(ea, g);
						
						b->disposed = true;
					}
				}
			}
		}
	}
	void entity_bullet_paint(entity_bullet* b)
	{
		DrawRectangle((int)b->x, (int)b->y, BULLET_WIDTH, BULLET_HEIGHT, ORANGE);
	}

#endif
