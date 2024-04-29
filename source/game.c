#pragma once

#ifndef GAME_C

	#define GAME_C
	
	#define BACKGROUND_SPEED 2
	#define GAME_MIN_ALIENS 5
	#define GAME_MAX_ALIENS 15
	#define GAME_EMPTY_COOLDOWN 55
	#define GAME_ASC_MIN 10
	#define GAME_ASC_MAX 100
	
	game* game_create()
	{
		game* g = (game*)malloc(sizeof(game));
		
		g->state = state_menu;
		g->entities = array_list_create();
		g->bullets = array_list_create();
		g->alien_bullets = array_list_create();
		g->particles = array_list_create();
		g->buttons = array_list_create();
		g->buttons_about = array_list_create();
		g->buttons_ingame = array_list_create();
		g->buttons_opt = array_list_create();
		g->checkboxes = array_list_create();
		g->asteroids = array_list_create();
		g->dialogs = array_list_create();
		
		g->background = LoadTexture("res/background.png");
		g->_bg1y = 0;
		g->_bg2y = -HEIGHT;
		g->level = 0;
		g->empty_cooldown = 0;
		g->score = 0;
		g->paused = false;
		g->asteroidTimeCap = 0;
		
		game_set_level_type(g);
		
	
		
		g->logo.width = 250;
		g->logo.height = 150;
		
		game_set_menus(g);
		game_set_dialogs(g);
		
		g->options = game_settings_create();
		
		game_init_sfx(g);
		
		return g;
	}
	void game_set_dialogs(game* g)
	{
		dialog* d = dialog_create();
		d->sender = strdup("Host:");
		d->lines = (char**)malloc(sizeof(char*) * 3);
		d->lines[0] = strdup("This is host of this universe");
		d->lines[1] = strdup("Host 00353.");
		d->lines[2] = strdup("Stay safe.");
		d->lines_count = 3;
		d->border_colour = PINK;
		d->colour = BLUE;
		
		array_list_push(g->dialogs, d);
		
		d = dialog_create();
		d->sender = strdup("Player:");
		d->lines = (char**)malloc(sizeof(char*) * 2);
		d->lines[0] = strdup("Im new here!");
		d->lines[1] = strdup("Nice to meet you! :D");
		d->lines_count = 2;
		d->border_colour = PURPLE;
		d->colour = RED;
		
		array_list_push(g->dialogs, d);
		
		d = dialog_create();
		d->sender = strdup("Host:");
		d->lines = (char**)malloc(sizeof(char*));
		d->lines[0] = strdup("Nice to meet you too, sir.");
		d->lines_count = 1;
		d->border_colour = PINK;
		d->colour = BLUE;
		
		array_list_push(g->dialogs, d);
		
		d = dialog_create();
		d->sender = strdup("Player:");
		d->lines = (char**)malloc(sizeof(char*) * 3);
		d->lines[0] = strdup("Be careful, there has been weird things.");
		d->lines[1] = strdup("I will let you know if anything happens.");
		d->lines[2] = strdup("Be prepared.");
		d->lines_count = 3;
		d->border_colour = PURPLE;
		d->colour = RED;
		
		array_list_push(g->dialogs, d);
		
		d = dialog_create();
		d->sender = strdup("Player:");
		d->lines = (char**)malloc(sizeof(char*) * 2);
		d->lines[0] = strdup("I am full loaded with bullets,");
		d->lines[1] = strdup("i think i will be fine.");
		d->lines_count = 2;
		d->border_colour = PINK;
		d->colour = BLUE;
		
		array_list_push(g->dialogs, d);
		
		d = dialog_create();
		d->sender = strdup("Host:");
		d->lines = (char**)malloc(sizeof(char*) * 2);
		d->lines[0] = strdup("There is an safe area just in case,");
		d->lines[1] = strdup("its not to far.");
		d->lines_count = 2;
		d->border_colour = PURPLE;
		d->colour = RED;
		
		array_list_push(g->dialogs, d);
		
		d = dialog_create();
		d->sender = strdup("Player:");
		d->lines = (char**)malloc(sizeof(char*) * 2);
		d->lines[0] = strdup("Thank you but,");
		d->lines[1] = strdup("I wouldn't need it.");
		d->lines_count = 2;
		d->border_colour = PINK;
		d->colour = BLUE;
		
		array_list_push(g->dialogs, d);
		
		d = dialog_create();
		d->sender = strdup("Host:");
		d->lines = (char**)malloc(sizeof(char*) * 2);
		d->lines[0] = strdup("The last ship said that...");
		d->lines[1] = strdup("wonder if they are still alive...");
		d->lines_count = 2;
		d->border_colour = PURPLE;
		d->colour = RED;
		
		array_list_push(g->dialogs, d);
		
		d = dialog_create();
		d->sender = strdup("UNKNOWN CREATURE Leader");
		d->lines = (char**)malloc(sizeof(char*));
		d->lines[0] = strdup("LITTLE HUMANS I CAME TO DESTROY YOU");
		d->lines_count = 1;
		d->border_colour = RED;
		d->colour = MAROON;
		
		array_list_push(g->dialogs, d);
		
		d = dialog_create();
		d->sender = strdup("Host:");
		d->lines = (char**)malloc(sizeof(char*) * 2);
		d->lines[0] = strdup("H-huhh WAHT?");
		d->lines[1] = strdup("Ship! SHip!");
		d->lines_count = 2;
		d->border_colour = PINK;
		d->colour = BLUE;
		
		array_list_push(g->dialogs, d);
		
		d = dialog_create();
		d->sender = strdup("General Vimus");
		d->lines = (char**)malloc(sizeof(char*) * 2);
		d->lines[0] = strdup("I heard it too!");
		d->lines[1] = strdup("WE ARE GETTING INVADED!");
		d->lines_count = 2;
		d->border_colour = PURPLE;
		d->colour = RED;
		
		array_list_push(g->dialogs, d);
		
		d = dialog_create();
		d->sender = strdup("Alien Leader");
		d->lines = (char**)malloc(sizeof(char*));
		d->lines[0] = strdup("Your chances are zero.");
		d->lines_count = 1;
		d->border_colour = RED;
		d->colour = MAROON;
		
		array_list_push(g->dialogs, d);
		
		g->level_dialogs = (int*)malloc(100 * sizeof(int));
		for (int i = 0; i < 100; i++)
			g->level_dialogs[i] = -1;
		
		g->level_dialogs[0] = 0;
		g->level_dialogs[1] = 1;
		g->level_dialogs[2] = 2;
		g->level_dialogs[3] = 3;
		g->level_dialogs[5] = 4;
		g->level_dialogs[6] = 5;
		g->level_dialogs[7] = 6;
		g->level_dialogs[8] = 7;
		g->level_dialogs[9] = 8;
		g->level_dialogs[10] = 9;
		g->level_dialogs[11] = 10;
		g->level_dialogs[12] = 11;
		//g->level_dialogs[17] = 11;
	}
	void game_set_menus(game * g)
	{
		g->menu_death = mmenu_create();
		
		g->menu_death->x = 150;
		g->menu_death->y = 150;
		g->menu_death->width = 500;
		g->menu_death->height = 300;
		g->menu_death->border_px = 4;
		g->menu_death->border_colour = BLUE;
		g->menu_death->colour = DARKBLUE;
		
		g->menu_pause = mmenu_create();
		
		g->menu_pause->x = 150;
		g->menu_pause->y = 150;
		g->menu_pause->width = 500;
		g->menu_pause->height = 300;
		g->menu_pause->border_px = 4;
		g->menu_pause->border_colour = BLUE;
		g->menu_pause->colour = DARKBLUE;

		mmenu_add_button(g->menu_death, 500 - MeasureText("RESPAWN", 40), 240, "RESPAWN", 40, 0);
		mmenu_add_button(g->menu_death, 500 - MeasureText("RRESPAWN", 40), 280, "QUIT GAME", 40, 1);
		
		mmenu_add_button(g->menu_pause, 500 - MeasureText("RESPAWN", 40), 240, "UNPAUSE", 40, 2);
		mmenu_add_button(g->menu_pause, 500 - MeasureText("RRESPAWN", 40), 280, "    MENU", 40, 3);
		
		// INGAME BUTTONS
		button* pauseB = button_create_img(10, HEIGHT - 16 - 10, 0);
		pauseB->tex = LoadTexture("res/pause.png");
		
		array_list_push(g->buttons_ingame, pauseB);
	}
	void game_set_level_type(game* g)
	{
		if (g->level == 4)
		{
			g->ltype = level_type_asteroid;
			g->asteroidTimeCap = util_random(900, 1500);
			g->asteroidSpawnCooldown = util_random(GAME_ASC_MIN, GAME_ASC_MAX);
			return;
		}
		if (g->level >= 13 && g->level <= 16)
		{
			g->ltype = level_type_normal;
			return;
		}
		
		int levelType = util_random(0, 100);
		if (levelType < 70)
			g->ltype = level_type_normal;
		else
			g->ltype = level_type_asteroid;
		
		if (g->ltype == level_type_asteroid)
		{
			g->asteroidTimeCap = util_random(900, 1500);
			g->asteroidSpawnCooldown = util_random(GAME_ASC_MIN, GAME_ASC_MAX);
		}
	}
	void game_clear_arrays(game* g)
	{
		for (int i = 0; i < g->entities->length; i++)
			entity_alien_destroy(((entity_alien*)array_list_get(g->entities, i)));
		for (int i = 0; i < g->particles->length; i++)
			particle_destroy((particle*)array_list_get(g->particles, i));
		for (int i = 0; i < g->bullets->length; i++)
			entity_bullet_destroy((entity_bullet*)array_list_get(g->bullets, i));
		for (int i = 0; i < g->alien_bullets->length; i++)
			entity_alien_bullet_destroy((entity_alien_bullet*)array_list_get(g->alien_bullets, i));
		for (int i = 0; i < g->asteroids->length; i++)
			entity_asteroid_destroy((entity_asteroid*)array_list_get(g->asteroids, i));
	}
	void game_destroy(game* g)
	{
		game_clear_arrays(g);

		// clear up arraylists before removing them
		for (int i = 0; i < g->buttons->length; i++)
			button_destroy((button*)array_list_get(g->buttons, i));
		for (int i = 0; i < g->buttons_about->length; i++)
			button_destroy((button*)array_list_get(g->buttons_about, i));
		for (int i = 0; i < g->buttons_ingame->length; i++)
			button_destroy((button*)array_list_get(g->buttons_ingame, i));
		for (int i = 0; i < g->buttons_opt->length; i++)
			button_destroy((button*)array_list_get(g->buttons_opt, i));
		for (int i = 0; i < g->dialogs->length; i++)
			dialog_destroy((dialog*)array_list_get(g->dialogs, i));
		for (int i = 0; i < g->checkboxes->length; i++)
			checkbox_destroy((checkbox*)array_list_get(g->checkboxes, i));
		
		mmenu_destroy(g->menu_pause);
		mmenu_destroy(g->menu_death);
		
		array_list_destroy(g->entities);
		array_list_destroy(g->bullets);
		array_list_destroy(g->alien_bullets);
		array_list_destroy(g->particles);
		array_list_destroy(g->buttons);
		array_list_destroy(g->buttons_about);
		array_list_destroy(g->buttons_opt);
		array_list_destroy(g->checkboxes);
		array_list_destroy(g->asteroids);
		array_list_destroy(g->dialogs);
		array_list_destroy(g->buttons_ingame);
		
		entity_player_destroy(g->player);
		game_settings_destroy(g->options);
		
		UnloadTexture(g->background);
		UnloadTexture(g->logo);
		
		free(g);
	}
	void game_erase_all(game* g)
	{
		game_clear_arrays(g);
		
		array_list_clear(g->bullets);
		array_list_clear(g->entities);
		array_list_clear(g->particles);
		array_list_clear(g->alien_bullets);
		array_list_clear(g->asteroids);
	}
	void game_add_alien(game* g, entity_alien_type type, float x, int y)
	{
		entity_alien* ea = entity_alien_create(type, x, y);
		
		array_list_push(g->entities, ea);
	}
	void game_add_particle(game* g, float x, float y, float speedx, float speedy, int lifespan, unsigned int type)
	{
		particle* p = particle_create(x, y, speedx, speedy, lifespan, type);
		
		array_list_push(g->particles, p);
	}
	void game_add_asteroid(game* g, float x, float y)
	{
		int type = util_random(0, ASTEROID_TYPES + 1);
		// an ugly workaround, because the clean code not always works;
		//int type = 1;
		//if (util_random(0, 100) > 50)
		//	type = 2;
		entity_asteroid* ea = entity_asteroid_create(x, y, type);
		
		array_list_push(g->asteroids, ea);
	}
	void game_spawn_aliens(game* g) // TODO: rename it to game_prepare_level()
	{
		int levelType = util_random(0, 100);
		
		// if levelType < 80 then aliens spawn
		// otherwise asteroids will spawn
		if (g->ltype != level_type_asteroid)
		{
			float bx = 5.0f;
			int by = (int)(-ALIEN_HEIGHT * 1.5f);
		
			for (int i = 0; i < util_random(GAME_MIN_ALIENS, GAME_MAX_ALIENS + g->level); i++)
			{
				game_add_alien(g, entity_alien_type_saucer, bx, by);
			
				bx += (float)ALIEN_WIDTH;
				if (bx >= WIDTH - ALIEN_WIDTH)
				{
					bx = 5.0f;
					by += ALIEN_HEIGHT;
				}
			}
		}
	}
	int game_get_alien_count(game* g)
	{
		int w = 0;
		
		for (int i = 0; i < g->entities->length; i++)
		{
			entity_alien* ea = (entity_alien*)array_list_get(g->entities, i);
			if (ea != NULL)
				if (!ea->disposed)
					w++;
		}
		
		return w;
	}
	int game_get_asteroid_count(game* g)
	{
		int w = 0;
		
		for (int i = 0; i < g->asteroids->length; i++)
		{
			entity_asteroid* ea = (entity_asteroid*)array_list_get(g->asteroids, i);
			if (ea != NULL)
				if (!ea->disposed)
					w++;
		}
		
		return w;
	}
	int game_get_particle_count(game* g)
	{
		int w = 0;
		
		for (int i = 0; i < g->particles->length; i++)
		{
			particle* p = (particle*)array_list_get(g->particles, i);
			if (p != NULL)
				if (!p->disposed)
					w++;
		}
		
		return w;
	}
	bool game_save(game* g, const char* path)
	{
		FILE* f = fopen(path, "w");
		
		if (f == NULL)
			return false;
		
		// WRITE GAME
		{
			fprintf(f, "%d\n", g->level);
			fprintf(f, "%d\n", g->player->health);
			fprintf(f, "%d\n", g->score);
		}
			
		
		fclose(f);
		
		return true;
	}
	bool game_read(game* g, const char* path)
	{
		FILE* f = fopen(path, "r");
		
		if (f == NULL)
			return false;
		
		return true;
	}
	void game_reset(game* g)
	{
		g->paused = false;
		g->level = 0;
		g->score = 0;
		
		entity_player_destroy(g->player);
		g->player = entity_player_create(WIDTH / 2 - PLAYER_WIDTH / 2);
		
		game_erase_all(g);
	}
	void game_init_sfx(game* g)
	{
		g->sounds[0] = LoadSound("res/sound/alien_death.wav");
	}
	void game_play_sfx(game* g, int id)
	{
		PlaySound(g->sounds[id]);
	}
	void game_unload_sfx(game* g)
	{
		UnloadSound(g->sounds[0]);
	}

#endif
