#pragma once

#ifndef PLAYER_H

	#define PLAYER_H
	
	typedef enum
	{
		entity_player_direction_center,
		entity_player_direction_left,
		entity_player_direction_right
	} entity_player_direction;
	
	typedef struct
	{
		float x;
		int health;
		float reload_time;
		Texture2D textures[6];
		int shoot_cooldown;
		int current_texture;
		int texture_cooldown;
		entity_player_direction direction;
		float additional_speed;
		bool dead;
	} entity_player;

#endif
