#pragma once

#ifndef FALIEN_BULLET_H

	#define FALIEN_BULLET_H
	
	entity_alien_bullet* entity_alien_bullet_create(float x, float y, float xs, float ys, int damage, Color c);
	void entity_alien_bullet_destroy(entity_alien_bullet* b);
	void entity_alien_bullet_update(entity_alien_bullet* b, entity_player* plr, game* g);
	void entity_alien_bullet_paint(entity_alien_bullet* b);

#endif
