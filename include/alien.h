#pragma once

#ifndef ALIEN_H

	#define ALIEN_H
	
	#define ALIEN_TYPES 2
	#define ALIEN_TEXTURES 2
	
	typedef enum
	{
		entity_alien_type_saucer,
		entity_alien_type_squid
	} entity_alien_type;
	
	typedef struct
	{
		float x;
		int y;
		int health;
		int damage;
		entity_alien_type type;
		Texture2D textures[ALIEN_TEXTURES];
		int current_texture;
		int texture_cooldown;
		int shoot_cooldown;
		float speed;
		bool disposed;
		Color bullet_color;
		int score_inc;
	} entity_alien;

#endif
