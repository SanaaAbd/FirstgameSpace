#pragma once

#ifndef SETTINGS_C

	#define SETTINGS_C
	
	game_settings* game_settings_create()
	{
		game_settings* gs = (game_settings*)malloc(sizeof(game_settings));
		
		game_settings_defaults(gs);
		
		return gs;
	}
	void game_settings_destroy(game_settings* gs)
	{
		free(gs);
	}
	void game_settings_defaults(game_settings* gs)
	{
		gs->mouse_control = false;
		gs->autoshoot = true;
	}
	void game_settings_save(game_settings* gs, const char* path)
	{
		FILE* fp = fopen(path, "w");
		
		fclose(fp);
	}
	void game_settings_load(game_settings* gs, const char* path)
	{
		FILE* fp = fopen(path, "r");
		
		fclose(fp);
	}

#endif
