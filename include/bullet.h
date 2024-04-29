#pragma once

#ifndef BULLET_H

	#define BULLET_H
	
	typedef struct
	{
		float x;
		float y;
		float speedx;
		float speedy;
		int damage;
		bool disposed;
	} entity_bullet;

#endif
