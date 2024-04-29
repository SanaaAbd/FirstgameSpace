#pragma once

#ifndef ALIEN_BULLET_H

	#define ALIEN_BULLET_H
	
	typedef struct
	{
		float x;
		float y;
		float speedx;
		float speedy;
		int damage;
		bool disposed;
		Color colour;
	} entity_alien_bullet;

#endif
