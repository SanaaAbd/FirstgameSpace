#pragma once

#ifndef FGAME_H

	#define FGAME_H
	
	game* game_create();
	void game_set_level_type(game* g);
	void game_clear_arrays(game* g);
	void game_destroy(game* g);
	void game_erase_all(game* g);
	void game_add_alien(game* g, entity_alien_type type, float x, int y);
	void game_add_particle(game* g, float x, float y, float speedx, float speedy, int lifespan, unsigned int type);
	void game_add_asteroid(game* g, float x, float y);
	void game_spawn_aliens(game* g);
	int game_get_alien_count(game* g);
	int game_get_asteroid_count(game* g);
	int game_get_particle_count(game* g);
	void game_set_dialogs(game* g);
	void game_set_menus(game* g);
	bool game_save(game* g, const char* path);
	void game_reset(game* g);
	void game_init_sfx(game* g);
	void game_play_sfx(game* g, int id);
	void game_unload_sfx(game* g);

#endif
