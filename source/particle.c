#pragma once

#ifndef PARTICLE_C

	#define PARTICLE_C
	
	#define PARTICLE_WIDTH 8
	#define PARTICLE_HEIGHT 8
	
	particle* particle_create(float x, float y, float speedx, float speedy, int lifespan, unsigned int type)
	{
		particle* p = (particle*)malloc(sizeof(particle));
		
		p->x = x;
		p->y = y;
		p->speedx = speedx;
		p->speedy = speedy;
		p->lifespan = lifespan;
		p->disposed = false;
		p->time = 0;
		p->type = type;
		
		char* toLoad = (char*)malloc((strlen("res/particleXX.png") + 1) * sizeof(char));
		sprintf(toLoad, "res/particle%d.png", p->type);
		p->texture = LoadTexture(toLoad);
		free(toLoad);
		
		return p;
	}
	void particle_destroy(particle* p)
	{
		UnloadTexture(p->texture);
		
		free(p);
	}
	void particle_update(particle* p)
	{
		if (p->time < p->lifespan)
		{
			p->x += p->speedx;
			p->y += p->speedy;
			
			p->time++;
		} else
			p->disposed = true;
	}
	void particle_paint(particle* p)
	{
		DrawTexture(p->texture, (int)p->x, (int)p->y, WHITE);
	}

#endif
