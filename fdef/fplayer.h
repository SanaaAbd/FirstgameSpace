#pragma once

#ifndef FPLAYER_H

	#define FPLAYER_H
	
	entity_player* entity_player_create(unsigned int start_pos_x);
	void entity_player_destroy(entity_player* p);
	void entity_player_update(entity_player* p, game* g);
	void entity_player_paint(entity_player* p, int target_y);
	void entity_player_spawn_particle(entity_player* p, game* g);

#endif
