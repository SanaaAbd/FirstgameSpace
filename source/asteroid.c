#pragma once

#ifndef ASTEROID_C

	#define ASTEROID_C

	#define ASTEROID_TYPES 3
	#define ASTEROID_WIDTH 128
	#define ASTEROID_HEIGHT 128

	entity_asteroid* entity_asteroid_create(float x, float y, int type)
	{
		entity_asteroid* ea = (entity_asteroid*)malloc(sizeof(entity_asteroid));

		ea->x = x;
		ea->y = y;
		ea->type = type;
		ea->disposed = false;
		ea->speed = (float)util_random(3, 12);
		ea->rotspeed = (float)(util_random(12, 17) / 5);
		if (util_random_bool())
			ea->rotspeed = !ea->rotspeed;
		ea->speedx = (float)util_random(0, 5);
		if (util_random_bool())
			ea->speedx = !ea->speedx;
		ea->rotation = (float)util_random(10, 100);
		ea->particle_cooldown = 0;
		ea->killed_by_player = false;

		entity_asteroid_set_props_based_on_type(ea);

		return ea;
	}
	void entity_asteroid_destroy(entity_asteroid* ea)
	{
		UnloadTexture(ea->texture);
		free(ea);
	}
	void entity_asteroid_set_props_based_on_type(entity_asteroid* ea)
	{
		switch (ea->type)
		{
			default: {} break;
			case 0:
			{
				ea->health = util_random(50, 100);
				ea->damage = 15;
				ea->score_inc = 1;
			} break;
			case 1:
			{
				ea->health = util_random(100, 150);
				ea->damage = 25;
				ea->score_inc = 5;
			} break;
			case 2:
			{
				ea->health = util_random(40, 90);
				ea->damage = 12;
				ea->score_inc = 1;
			} break;
		}
		char* toLoad = (char*)malloc((strlen("res/asteroidXX.png") + 1) * sizeof(char));
		sprintf(toLoad, "res/asteroid%d.png", ea->type);
		ea->texture = LoadTexture(toLoad);
		free(toLoad);
		
		ea->texture.width = ASTEROID_WIDTH;
		ea->texture.height = ASTEROID_HEIGHT;
	}
	void entity_asteroid_spawn_particle(entity_asteroid* ea, game* g)
	{
		size_t time = util_random(10, 35);
		size_t rptr = 45;
		
		// top-left particle
		game_add_particle(g, ea->x + rptr, ea->y + rptr, -0.5f, -0.5f, time, 1);
		time = util_random(10, 35);
		
		// top-right particle
		game_add_particle(g, ea->x + ASTEROID_WIDTH - rptr, ea->y + rptr, 0.5f, 0.5f, time, 1);
		time = util_random(10, 35);
		
		// bottom-left particle
		game_add_particle(g, ea->x + rptr, ea->y + ASTEROID_HEIGHT - rptr, -0.5f, 0.5f, time, 1);
		time = util_random(10, 35);
		
		// bottom-right particle
		game_add_particle(g, ea->x + ASTEROID_WIDTH - rptr, ea->y + ASTEROID_HEIGHT - rptr, 0.5f, -0.5f, time, 1);
		
		ea->particle_cooldown = 25;
	}
	void entity_asteroid_update(entity_asteroid* ea, game* g)
	{
		ea->y += ea->speed;
		ea->x += ea->speedx;
		ea->rotation += ea->rotspeed;

		if (ea->y >= (HEIGHT + ASTEROID_HEIGHT) ||
			ea->x >= (WIDTH + ASTEROID_WIDTH) ||
			ea->x < -ASTEROID_WIDTH)
		{
			ea->disposed = true;
			return;
		}
		if (ea->health <= 0)
		{
			ea->disposed = true;
			if (ea->killed_by_player)
				g->score += ea->score_inc;
		}
		if (ea->particle_cooldown > 0)
			ea->particle_cooldown--;
		
		// check for collisions with other asteroids
		for (int i = 0; i < g->asteroids->length; i++)
		{
			entity_asteroid* oa = (entity_asteroid*)array_list_get(g->asteroids, i);
			if (oa != NULL)
			{
				if (!oa->disposed)
				{
					int tx = (int)ea->x;
					int ty = (int)ea->y + ASTEROID_HEIGHT;
					
					int otx = (int)oa->x + i;
					int oty = (int)oa->y + ASTEROID_HEIGHT;
					
					if (tx >= otx &&
						tx <= otx + ASTEROID_WIDTH &&
						ty >= oty &&
						ty <= oty + ASTEROID_HEIGHT)
					{
						entity_asteroid_spawn_particle(ea, g);
						entity_asteroid_spawn_particle(oa, g);
						
						ea->disposed = true;
						oa->disposed = true;
						
						return;
					}
				}
			}
		}
		
		// must be at the end, as it may call return
		for (int i = 0; i < ASTEROID_WIDTH; i++)
		{
			int tx = (int)ea->x;
			int ty = (int)ea->y + ASTEROID_HEIGHT;
			
			if ((int)g->player->x >= tx &&
				(int)g->player->x <= tx + ASTEROID_WIDTH &&
				HEIGHT - 75 >= ty &&
				HEIGHT - 75 <= ty + (ASTEROID_HEIGHT / 4))
			{
				g->player->health -= ea->damage;
				
				entity_player_spawn_particle(g->player, g);
				
				ea->disposed = true;
				return;
			}
		}
	}
	void entity_asteroid_paint(entity_asteroid* ea)
	{
		if (debug)
		{
			char* toPrint = (char*)malloc((strlen("asteroid XXXhp XXXdmg") + 1) * sizeof(char));
			sprintf(toPrint, "asteroid %dhp %ddmg", ea->health, ea->damage);
			DrawText(toPrint, (int)ea->x, (int)ea->y - 12, 12, RED);
			free(toPrint);
			
			DrawRectangle((int)ea->x, (int)ea->y, ASTEROID_WIDTH, ASTEROID_HEIGHT, WHITE);
			DrawRectangle((int)ea->x + 2, (int)ea->y + 2, ASTEROID_WIDTH - 4, ASTEROID_HEIGHT - 4, GRAY);
		}
		util_draw_rotated(&ea->texture, (int)ea->x, (int)ea->y, ea->rotation, WHITE);
	}

#endif
