#pragma once

#ifndef ALIEN_BULLET_C

	#define ALIEN_BULLET_C
	
	#define ALIEN_BULLET_WIDTH 2
	#define ALIEN_BULLET_HEIGHT 15
	
	entity_alien_bullet* entity_alien_bullet_create(float x, float y, float xs, float ys, int damage, Color c)
	{
		entity_alien_bullet* b = (entity_alien_bullet*)malloc(sizeof(entity_alien_bullet));
		
		b->x = x;
		b->y = y;
		b->speedx = xs;
		b->speedy = ys;
		b->damage = damage;
		b->disposed = false;
		b->colour = c;
		
		return b;
	}
	void entity_alien_bullet_destroy(entity_alien_bullet* b)
	{
		free(b);
	}
	void entity_alien_bullet_update(entity_alien_bullet* b, entity_player* plr, game* g)
	{
		b->x += b->speedx;
		b->y += b->speedy;
		
		if ((int)b->x >= (int)plr->x &&
			(int)b->x <= (int)plr->x + PLAYER_WIDTH &&
			(int)b->y >= HEIGHT - 75 &&
			(int)b->y <= (HEIGHT - 75) + PLAYER_HEIGHT)
		{
			plr->health -= b->damage;
			
			entity_player_spawn_particle(plr, g);
			
			b->disposed = true;
		}
		
		if (b->y > HEIGHT)
		{
			b->disposed = true;
		}
	}
	void entity_alien_bullet_paint(entity_alien_bullet* b)
	{
		DrawRectangle((int)b->x, (int)b->y, ALIEN_BULLET_WIDTH, ALIEN_BULLET_HEIGHT, b->colour);
	}

#endif
