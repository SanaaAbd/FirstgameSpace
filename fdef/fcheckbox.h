#pragma once

#ifndef FCHECKBOX_H

	#define FCHECKBOX_H
	
	checkbox* checkbox_create(int id, int x, int y);
	void checkbox_destroy(checkbox* c);
	void checkbox_update(checkbox* c, game* g);
	void checkbox_paint(checkbox* c);

#endif
