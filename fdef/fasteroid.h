#pragma once

#ifndef FASTEROID_H

	#define FASTEROID_H
	
	entity_asteroid* entity_asteroid_create(float x, float y, int type);
	void entity_asteroid_destroy(entity_asteroid* ea);
	void entity_asteroid_set_props_based_on_type(entity_asteroid* ea);
	void entity_asteroid_update(entity_asteroid* ea, game* g);
	void entity_asteroid_paint(entity_asteroid* ea);
	void entity_asteroid_spawn_particle(entity_asteroid* ea, game* g);

#endif
