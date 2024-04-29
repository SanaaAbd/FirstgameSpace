#pragma once

#ifndef FSETTINGS_H

	#define FSETTINGS_H
	
	game_settings* game_settings_create();
	void game_settings_destroy(game_settings* gs);
	void game_settings_defaults(game_settings* gs);
	void game_settings_save(game_settings* gs, const char* path);
	void game_settings_load(game_settings* gs, const char* path);

#endif
