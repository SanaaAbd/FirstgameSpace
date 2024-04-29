#pragma once

#ifndef PLAYER_C

	#define PLAYER_C
	
	#define PLAYER_HEALTH_RANGE 100
	#define PLAYER_SPEED 5.5f
	#define PLAYER_WIDTH 64
	#define PLAYER_HEIGHT 64
	#define PLAYER_HEALTH_PIXEL 2
	#define PLAYER_ASPEED_DEC 0.05f
	
	entity_player* entity_player_create(unsigned int start_pos_x)
	{
		entity_player* p = (entity_player*)malloc(sizeof(entity_player));
		
		p->x = start_pos_x;
		p->health = PLAYER_HEALTH_RANGE;
		p->reload_time = 0.0f;
		p->shoot_cooldown = 0;
		p->current_texture = 0;
		p->texture_cooldown = 50;
		p->direction = entity_player_direction_center;
		p->additional_speed = 0.0f;
		p->dead = false;
		
		p->textures[0] = LoadTexture("res/player.png");
		p->textures[0].width = PLAYER_WIDTH;
		p->textures[0].height = PLAYER_HEIGHT;
		
		p->textures[1] = LoadTexture("res/player1.png");
		p->textures[1].width = PLAYER_WIDTH;
		p->textures[1].height = PLAYER_HEIGHT;
		
		p->textures[2] = LoadTexture("res/player_shoot.png");
		p->textures[2].width = PLAYER_WIDTH;
		p->textures[2].height = PLAYER_HEIGHT;
		
		p->textures[3] = LoadTexture("res/player_r.png");
		p->textures[3].width = PLAYER_WIDTH;
		p->textures[3].height = PLAYER_HEIGHT;
		
		p->textures[4] = LoadTexture("res/player_r1.png");
		p->textures[4].width = PLAYER_WIDTH;
		p->textures[4].height = PLAYER_HEIGHT;
		
		p->textures[5] = LoadTexture("res/player_dead.png");
		p->textures[5].width = PLAYER_WIDTH;
		p->textures[5].height = PLAYER_HEIGHT;
		
		return p;
	}
	void entity_player_destroy(entity_player* p)
	{
		for (int i = 0; i < 6; i++)
			UnloadTexture(p->textures[i]);
		free(p);
	}
	void entity_player_spawn_particle(entity_player* p, game* g)
	{
		float tx = (float)p->x + PLAYER_WIDTH / 2;
		float ty = HEIGHT - 75 + PLAYER_HEIGHT / 2;
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
	void entity_player_update(entity_player* p, game* g)
	{
		// handle keys
		if (!p->dead)
		{
			if (IsKeyDown(KEY_LEFT))
			{
				p->direction = entity_player_direction_left;
				if (p->x > PLAYER_SPEED)
				{
					p->x -= PLAYER_SPEED / 2;
					p->additional_speed = -(PLAYER_SPEED / 2);
				}
			} else
			if (IsKeyDown(KEY_RIGHT))
			{
				p->direction = entity_player_direction_right;
				if (p->x < WIDTH - PLAYER_SPEED - PLAYER_WIDTH)
				{
					p->x += PLAYER_SPEED / 2;
					p->additional_speed = PLAYER_SPEED / 2;
				}
			} else
			{
				p->direction = entity_player_direction_center;
				if (p->additional_speed != 0.0f)
				{
					if (p->additional_speed > 0.0f)
						p->additional_speed -= PLAYER_ASPEED_DEC;
					else if (p->additional_speed < 0.0f)
						p->additional_speed += PLAYER_ASPEED_DEC;
				}
			}
			if (IsKeyDown(KEY_SPACE) || g->options->autoshoot)
			{
				p->current_texture = 2;
			
				if (p->shoot_cooldown <= 0)
				{
					p->shoot_cooldown = 10;
					
					// SHOOTING
					entity_bullet* newbullet = entity_bullet_create((int)p->x + PLAYER_WIDTH / 2, HEIGHT - 75, 0, -7, 10);
					array_list_push(g->bullets, newbullet);
				}
			} else
			{
				p->current_texture = 0;
			}
		
			if (p->additional_speed > 0.1f ||
				p->additional_speed < -0.1f)
				p->x += p->additional_speed;
		
			if (p->x < 0.0f)
				p->x = 0.0f;
			if (p->x > WIDTH - PLAYER_WIDTH)
				p->x = WIDTH - PLAYER_WIDTH;
			
			if (g->options->mouse_control)
			{
				p->x = GetMousePosition().x;
			}
		}
		
		// handle cooldowns
		if (p->texture_cooldown > 0)
			p->texture_cooldown--;
		if (p->shoot_cooldown > 0)
			p->shoot_cooldown--;
		
		if (!p->dead)
		{
			if (p->texture_cooldown <= 0)
				p->texture_cooldown = 50;
			
			if (p->texture_cooldown > 25)
			{
				switch (p->direction)
				{
					case entity_player_direction_center:
					{
						p->current_texture = 1;
					} break;
					case entity_player_direction_left:
					{
						p->current_texture = 4;
					} break;
					case entity_player_direction_right:
					{
						p->current_texture = 4;
					} break;
					default:
					{} break;
				}
			} else
			{
				switch (p->direction)
				{
					case entity_player_direction_center:
					{
						p->current_texture = 0;
					} break;
					case entity_player_direction_left:
					{
						p->current_texture = 3;
					} break;
					case entity_player_direction_right:
					{
						p->current_texture = 3;
					} break;
					default:
					{} break;
				}
			}
		}
		
		if (p->health <= 0)
		{
			p->dead = true;
			p->current_texture = 5;
		}
	}
	void entity_player_paint(entity_player* p, int target_y)
	{
		DrawTexture(p->textures[p->current_texture], (int)p->x, target_y, WHITE);
	}

#endif
