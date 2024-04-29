#pragma once

#ifndef FALIEN_H

	#define FALIEN_H
	
	entity_alien* entity_alien_create(entity_alien_type type, const float x, const int y);
	void entity_alien_destroy(entity_alien* ea);
	void entity_alien_set_props_based_on_type(entity_alien* ea);
	void entity_alien_scale_textures(entity_alien* ea, int w, int h);
	void entity_alien_update(entity_alien* ea, entity_player* plr, game* g);
	void entity_alien_paint(entity_alien* ea);
	void entity_alien_spawn_particle(entity_alien* ea, game* g);

#endif
