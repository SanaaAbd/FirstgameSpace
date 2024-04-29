#pragma once

#ifndef ASTEROID_H

	#define ASTEROID_H
	
	typedef struct
	{
		float x;
		float y;
		int health;
		int type;
		float rotation;
		float speed;
		float speedx;
		float rotspeed;
		bool disposed;
		int damage;
		Texture2D texture;
		int score_inc;
		int particle_cooldown;
		bool killed_by_player;
	} entity_asteroid;

#endif
