#pragma once

#ifndef FPARTICLE_H

	#define FPARTICLE_H
	
	particle* particle_create(float x, float y, float speedx, float speedy, int lifespan, unsigned int type);
	void particle_destroy(particle* p);
	void particle_update(particle* p);
	void particle_paint(particle* p);

#endif
