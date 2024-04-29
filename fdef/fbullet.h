#pragma once

#ifndef FBULLET_H

	#define FBULLET_H
	
	entity_bullet* entity_bullet_create(float x, float y, float xs, float ys, int damage);
	void entity_bullet_destroy(entity_bullet* b);
	void entity_bullet_update(entity_bullet* b, game* g);
	void entity_bullet_paint(entity_bullet* b);

#endif
