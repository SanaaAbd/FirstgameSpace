#pragma once

#ifndef ALIEN_C

	#define ALIEN_C
	
	#define ALIEN_WIDTH 64
	#define ALIEN_HEIGHT 64
	#define ALIEN_Y_INC (int)(ALIEN_HEIGHT / 2)
	#define ALIEN_MIN_SC 25
	#define ALIEN_MAX_SC 150
	#define ALIEN_ZERO_S 2
	#define ALIEN_BASE_SPEED 4.5f
	#define ALIEN_ASPEED_INC 0.007f
	
	static float entity_alien_additional_speed = 0.0f;
	
	entity_alien* entity_alien_create(entity_alien_type type, const float x, const int y)
	{
		entity_alien* ea = (entity_alien*)malloc(sizeof(entity_alien));
		
		ea->x = x;
		ea->y = y;
		ea->type = type;
		ea->current_texture = 0;
		ea->texture_cooldown = 0;
		ea->shoot_cooldown = util_random(ALIEN_MIN_SC, ALIEN_MAX_SC);
		ea->disposed = false;
		ea->speed = ALIEN_BASE_SPEED;
		
		entity_alien_set_props_based_on_type(ea);
		
		return ea;
	}
	void entity_alien_destroy(entity_alien* ea)
	{
		for (int i = 0; i < ALIEN_TEXTURES; i++)
			UnloadTexture(ea->textures[i]);
		
		free(ea);
	}
	void entity_alien_set_props_based_on_type(entity_alien* ea)
	{
		switch (ea->type)
		{
			case entity_alien_type_saucer:
			{
				ea->health = 10;
				ea->damage = 10;
				ea->bullet_color = RED;
				ea->score_inc = 10;
				
				ea->textures[0] = LoadTexture("res/saucer.png");
				ea->textures[1] = LoadTexture("res/saucer1.png");
			} break;
			case entity_alien_type_squid:
			{
				ea->health = 50;
				ea->damage = 25;
				ea->score_inc = 25;
			} break;
			default:
			{
			} break;
		}
		entity_alien_scale_textures(ea, ALIEN_WIDTH, ALIEN_HEIGHT);
	}
	void entity_alien_scale_textures(entity_alien* ea, int w, int h)
	{
		for (int i = 0; i < ALIEN_TEXTURES; i++)
		{
			ea->textures[i].width = w;
			ea->textures[i].height = h;
		}
	}
	void entity_alien_update(entity_alien* ea, entity_player* plr, game* g)
	{
		if (ea->texture_cooldown > 0)
			ea->texture_cooldown--;
		if (ea->texture_cooldown <= 0)
			ea->texture_cooldown = 50;
		
		if (ea->texture_cooldown > 25)
			ea->current_texture = 1;
		else
			ea->current_texture = 0;
		
		if (ea->speed > 0.0f)
			ea->x += ea->speed + entity_alien_additional_speed;
		else
			ea->x += ea->speed - entity_alien_additional_speed;
		
		if (ea->x > (WIDTH - ALIEN_WIDTH) ||
			ea->x < 0)
		{
			ea->speed = -(ea->speed);
			ea->y += ALIEN_Y_INC;
			if (ea->x < 0)
				ea->x = 0;
			else
				ea->x = (WIDTH - ALIEN_WIDTH);
		}
		if (ea->y < 0)
			ea->y += ALIEN_ZERO_S;
		if (ea->y > HEIGHT)
		{
			// TODO: make it working
			
			//plr->health = 0;
		}
		if (ea->health <= 0)
		{
			entity_alien_additional_speed += ALIEN_ASPEED_INC;
			
			g->score += ea->score_inc;
			entity_alien_spawn_particle(ea, g);
			ea->disposed = true;
			
			game_play_sfx(g, 0);
		}
		if (ea->shoot_cooldown > 0)
			ea->shoot_cooldown--;
		if (ea->shoot_cooldown <= 0 && ea->y > -35)
		{
			float xspeed = 0.0f;
							
			if (plr->x > ea->x + ALIEN_WIDTH / 2)
				xspeed = 1.0f;
			else if (plr->x < ea->x - ALIEN_WIDTH / 2)
				xspeed = 1.0f;
							
			entity_alien_bullet* eab = entity_alien_bullet_create(ea->x,
				(float)ea->y,
				xspeed,
				7.0f,
				ea->damage,
				ea->bullet_color);
			array_list_push(g->alien_bullets, eab);
			
			ea->shoot_cooldown = util_random(ALIEN_MIN_SC, ALIEN_MAX_SC);
		}
	}
	void entity_alien_paint(entity_alien* ea)
	{
		if (debug)
		{
			char* toPrint = (char*)malloc((strlen("alien XXXhp XXXdmg") + 1) * sizeof(char));
			sprintf(toPrint, "alien %dhp %ddmg", ea->health, ea->damage);
			DrawText(toPrint, (int)ea->x, (int)ea->y - 12, 12, RED);
			free(toPrint);
			
			DrawRectangle((int)ea->x, (int)ea->y, ALIEN_WIDTH, ALIEN_HEIGHT, WHITE);
			DrawRectangle((int)ea->x + 2, (int)ea->y + 2, ALIEN_WIDTH - 4, ALIEN_HEIGHT - 4, GRAY);
		}
		DrawTexture(ea->textures[ea->current_texture], (int)ea->x, ea->y, WHITE);
	}
	void entity_alien_spawn_particle(entity_alien* ea, game* g)
	{
		float tx = (float)ea->x + ALIEN_WIDTH / 2;
		float ty = (float)ea->y + ALIEN_HEIGHT / 2;
		size_t time = util_random(10, 35);
								
		// top-left particle
		game_add_particle(g, tx, ty, -0.5f, -0.5f, time, 0);
		time = util_random(10, 35);
							
		// top-right particle
		game_add_particle(g, tx, ty, 0.5f, 0.5f, time, 0);
		time = util_random(10, 35);
							
		// bottom-left particle
		game_add_particle(g, tx, ty, -0.5f, 0.5f, time, 0);
		time = util_random(10, 35);
							
		// bottom-right particle
		game_add_particle(g, tx, ty, 0.5f, -0.5f, time, 0);
	}

#endif
