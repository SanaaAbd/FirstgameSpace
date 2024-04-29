#pragma once

#ifndef PARTICLE_H

	#define PARTICLE_H
	
	typedef struct
	{
		float x;
		float y;
		float speedx;
		float speedy;
		int lifespan;
		Texture2D texture;
		bool disposed;
		int time;
		unsigned int type;
	} particle;

#endif
