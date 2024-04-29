#pragma once

#ifndef GAME_H

	#define GAME_H
	
	#define GAME_MAX_SOUNDS 99
	
	typedef enum
	{
		state_developer_logo,
		state_game_logo,
		state_menu,
		state_game,
		state_shop,
		state_about,
		state_options
	} game_state;
	
	typedef enum
	{
		level_type_normal = 0,
		level_type_asteroid = 1
	} level_type;
	
	typedef struct
	{
		game_state state;
		array_list* entities; // TODO: rename to aliens
		array_list* bullets;
		array_list* alien_bullets;
		array_list* particles;
		array_list* player_particles;
		array_list* asteroids;
		array_list* buttons;
		array_list* buttons_about;
		array_list* buttons_ingame;
		array_list* buttons_opt;
		array_list* dialogs;
		array_list* checkboxes;
		entity_player* player;
		Texture2D background;
		Texture2D logo;
		int _bg1y;
		int _bg2y;
		int level;
		int empty_cooldown;
		int score;
		level_type ltype;
		int asteroidTimeCap;
		int asteroidSpawnCooldown;
		bool paused;
		mmenu* menu_pause;
		mmenu* menu_death;
		int* level_dialogs;
		game_settings* options;
		Sound sounds[GAME_MAX_SOUNDS];
	} game;

#endif
