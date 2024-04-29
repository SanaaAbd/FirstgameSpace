#pragma once

#ifndef FDIALOG_H

	#define FDIALOG_H
	
	dialog* dialog_create();
	void dialog_destroy(dialog* d);
	void dialog_update(dialog* d, game* g);
	void dialog_paint(dialog* d);

#endif
