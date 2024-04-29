#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <raylib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600
#define CAPTION "Space Invader"
#define FPS 60

static bool debug = false;
static bool force_quit = false;

#include "ext_lib/gall/array_list.c"
#include "source/util.c"

#include "include/player.h"
#include "include/bullet.h"
#include "include/alien.h"
#include "include/alien_bullet.h"
#include "include/button.h"
#include "include/asteroid.h"
#include "include/particle.h"
#include "include/mmenu.h"
#include "include/dialog.h"
#include "include/settings.h"
#include "include/checkbox.h"
#include "include/game.h"



#include "fdef/fplayer.h"
#include "fdef/fbullet.h"
#include "fdef/falien.h"
#include "fdef/falien_bullet.h"
#include "fdef/fbutton.h"
#include "fdef/fasteroid.h"
#include "fdef/fparticle.h"
#include "fdef/fgame.h"
#include "fdef/fmmenu.h"
#include "fdef/fdialog.h"
#include "fdef/fsettings.h"
#include "fdef/fcheckbox.h"

#include "source/particle.c"
#include "source/player.c"
#include "source/alien.c"
#include "source/asteroid.c"
#include "source/bullet.c"
#include "source/alien_bullet.c"
#include "source/button.c"
#include "source/game.c"
#include "source/dialog.c"
#include "source/mmenu.c"
#include "source/settings.c"
#include "source/checkbox.c"

// DEFINITION

int main(int argc, char** argv);
void update();
void paint();
void init();
void deinit();
void game_logic_function1(); // Prototype for the assembly function
void game_logic_function2(); // Prototype for the assembly function

// IMPLEMENTATION

game* _game;
Image window_icon;





int main(int argc, char** argv)
{
    
     
	// disable raylib console spam, as this can get really long as we progress
	SetTraceLogLevel(LOG_ERROR);
	
	InitWindow(WIDTH, HEIGHT, CAPTION);
	InitAudioDevice();
	SetTargetFPS(FPS);
	SetExitKey(0);
	
	window_icon = LoadImage("res/player.png");
	
	
	init();
	
	while (!WindowShouldClose())
	{
		update();
		
		if (force_quit)
			break;
		
		BeginDrawing();
		
			paint();
		
		EndDrawing();
	}
	
	CloseWindow();

	deinit();
	
	return 0;
}
void init()
{
	srand(time(0));
	_game = game_create();
	_game->player = entity_player_create(WIDTH / 2 - PLAYER_WIDTH / 2);
	
	// init the menu
	int playButtonWidth = MeasureText("PLAY", 160); // Increase font size
    int playButtonHeight = 160; // Adjust height
    int playButtonX = WIDTH / 2 - playButtonWidth / 2;
    int playButtonY = 250; // Lower the button

    array_list_push(_game->buttons,
                    button_create("PLAY", playButtonX, playButtonY, playButtonHeight, 0));
	
}
void deinit()
{
	UnloadImage(window_icon);
	game_destroy(_game);
}
void set_proper_checkboxes()
{
	for (int i = 0; i < _game->checkboxes->length; i++)
	{
		checkbox* c = (checkbox*)array_list_get(_game->checkboxes, i);
								
		switch (c->id)
		{
			default: break;
			case 0: // autoshoot
			{
				c->value = _game->options->autoshoot;
			} break;
			case 1: // mouse control
			{
				c->value = _game->options->mouse_control;
			} break;
		}
	}
}
void prepare_new_level()
{
	game_erase_all(_game);
	game_set_level_type(_game);
	if (_game->ltype != level_type_asteroid)
		game_spawn_aliens(_game);
	_game->level++;
	_game->empty_cooldown = GAME_EMPTY_COOLDOWN;
	
	game_save(_game, "pixab_c.lvl");
}

extern void assembly_function_1();
extern void assembly_function_2();

void update()
{
	switch (_game->state)
	{
		default:
		{
		}; break;
		case state_game:
		{
			_game->_bg1y += BACKGROUND_SPEED;
			_game->_bg2y += BACKGROUND_SPEED;
			
			if (_game->_bg1y > HEIGHT)
				_game->_bg1y = -HEIGHT;
			if (_game->_bg2y > HEIGHT)
				_game->_bg2y = -HEIGHT;
				
			if (!_game->paused && _game->level_dialogs[_game->level] == -1)
			{

			entity_player_update(_game->player, _game);

			for (int i = 0; i < _game->bullets->length; i++)
			{
				entity_bullet* bpointer = (entity_bullet*)array_list_get(_game->bullets, i);
				if (bpointer != NULL)
					if (!bpointer->disposed)
						entity_bullet_update(bpointer, _game);
			}
			for (int i = 0; i < _game->alien_bullets->length; i++)
			{
				entity_alien_bullet* bpointer = (entity_alien_bullet*)array_list_get(_game->alien_bullets, i);
				if (bpointer != NULL)
					if (!bpointer->disposed)
						entity_alien_bullet_update(bpointer, _game->player, _game);
			}
			for (int i = 0; i < _game->entities->length; i++)
			{
				entity_alien* balien = (entity_alien*)array_list_get(_game->entities, i);
				if (balien != NULL)
					if (!balien->disposed)	
						entity_alien_update(balien, _game->player, _game);
			}
			for (int i = 0; i < _game->particles->length; i++)
			{
				particle* pparticle = (particle*)array_list_get(_game->particles, i);
				if (pparticle != NULL)
					if (!pparticle->disposed)
						particle_update(pparticle);
			}
			if (game_get_alien_count(_game) <= 0 &&
				game_get_particle_count(_game) <= 0 &&
				_game->ltype != level_type_asteroid)
			{
				if (_game->empty_cooldown > 0)
					_game->empty_cooldown--;
				
				if (_game->empty_cooldown <= 0)
				{
					prepare_new_level();
				}
			}
			if (_game->player->dead)
			{
				mmenu_update(_game->menu_death, _game);
				
				for (int i = 0; i < _game->menu_death->buttons->length; i++)
				{
					button* b = (button*)array_list_get(_game->menu_death->buttons, i);
					
					if (b->clicked)
					{
						switch (b->id)
						{
							case 0: // RESPAWN
							{
								game_destroy(_game);
				
								_game = game_create();
								_game->player = entity_player_create(WIDTH / 2 - PLAYER_WIDTH / 2);

								_game->state = state_game;
							}; break;
							case 1: // QUIT
							{
								force_quit = true;
							}; break;
						}
					}
				}
			}
			for (int i = 0; i < _game->asteroids->length; i++)
			{
				entity_asteroid* ea = (entity_asteroid*)array_list_get(_game->asteroids, i);

				if (!ea->disposed)
					entity_asteroid_update(ea, _game);
			}
			if (_game->ltype == level_type_asteroid)
			{
				// the cooldowns
				if (_game->asteroidTimeCap > 0)
					_game->asteroidTimeCap--;
				if (_game->asteroidSpawnCooldown > 0)
					_game->asteroidSpawnCooldown--;
					
				if (_game->asteroidTimeCap <= 0 && game_get_asteroid_count(_game) <= 0)
				{
					prepare_new_level();
				}
				if (_game->asteroidSpawnCooldown <= 0 && _game->asteroidTimeCap > 100)
				{
					_game->asteroidSpawnCooldown = util_random(GAME_ASC_MIN, GAME_ASC_MAX);
					
					int rx = util_random(0, WIDTH - ASTEROID_WIDTH);
					int ry = -(util_random(ASTEROID_HEIGHT, ASTEROID_HEIGHT * 2));
					
					game_add_asteroid(_game, (float)rx, (float)ry);
				}
			}
			if (IsKeyPressed(KEY_F3))
				debug = !debug;
			} // END OF PAUSEABLE GAME LOOP
			if (IsKeyPressed(KEY_ESCAPE))
				_game->paused = !_game->paused;
			if (_game->paused)
			{
				mmenu_update(_game->menu_pause, _game);
				
				for (int i = 0; i < _game->menu_pause->buttons->length; i++)
				{
					button* b = (button*)array_list_get(_game->menu_pause->buttons, i);
					
					if (b->clicked)
					{
						switch (b->id)
						{
							case 2: // UNPAUSE
							{
								_game->paused = false;
							} break;
							case 3: // MENU
							{
								_game->state = state_menu;
							}; break;
						}
					}
				}
			}
			if (_game->level_dialogs[_game->level] != -1)
			{
				// TODO: display the dialogs
				
				dialog* currentD = ((dialog*)(array_list_get(_game->dialogs, _game->level_dialogs[_game->level])));
				
				dialog_update(currentD, _game);
			}
			for (int i = 0; i < _game->buttons_ingame->length; i++)
			{
				button* b = (button*)array_list_get(_game->buttons_ingame, i);
				
				button_update(b);
				
				if (b->clicked)
				{
					switch (b->id)
					{
						case 0:
						{
							_game->paused = !_game->paused;
						} break;
						default:
						{
						} break;
					}
				}
			}
		} break;
		case state_menu:
		{
			_game->_bg1y += BACKGROUND_SPEED;
			_game->_bg2y += BACKGROUND_SPEED;
			
			if (_game->_bg1y > HEIGHT)
				_game->_bg1y = -HEIGHT;
			if (_game->_bg2y > HEIGHT)
				_game->_bg2y = -HEIGHT;
			
			for (int i = 0; i < _game->buttons->length; i++)
			{
				button* bp = (button*)array_list_get(_game->buttons, i);
				button_update(bp);
				
				if (bp->clicked)
				{
					switch (bp->id)
					{
						default: {} break;
						case 0:
						{
							_game->state = state_game;
						} break;
						case 1:
						{
							_game->state = state_options;
						} break;
						case 2:
						{
							_game->state = state_about;
						} break;
						case 3:
						{
							CloseWindow();
							deinit();
							exit(0);
						} break;
					}
				}
			}
		} break;
		case state_about:
		{
			_game->_bg1y += BACKGROUND_SPEED;
			_game->_bg2y += BACKGROUND_SPEED;
			
			if (_game->_bg1y > HEIGHT)
				_game->_bg1y = -HEIGHT;
			if (_game->_bg2y > HEIGHT)
				_game->_bg2y = -HEIGHT;
			
			for (int i = 0; i < _game->buttons_about->length; i++)
			{
				button* bp = (button*)array_list_get(_game->buttons_about, i);
				button_update(bp);
				
				if (bp->clicked)
				{
					switch (bp->id)
					{
						default: {} break;
						case 0:
						{
							_game->state = state_menu;
						} break;
						
					}
				}
			}
		} break;
		case state_options:
		{
			_game->_bg1y += BACKGROUND_SPEED;
			_game->_bg2y += BACKGROUND_SPEED;
			
			if (_game->_bg1y > HEIGHT)
				_game->_bg1y = -HEIGHT;
			if (_game->_bg2y > HEIGHT)
				_game->_bg2y = -HEIGHT;
				
			for (int i = 0; i < _game->buttons_opt->length; i++)
			{
				button* b = (button*)array_list_get(_game->buttons_opt, i);
				
				button_update(b);
				
				if (b->clicked)
				{
					switch (b->id)
					{
						default:
						{
						} break;
						case 0: // quit
						{
							// set the options
							for (int i = 0; i < _game->checkboxes->length; i++)
							{
								checkbox* c = (checkbox*)array_list_get(_game->checkboxes, i);
								
								switch (c->id)
								{
									default: break;
									case 0: // autoshoot
									{
										_game->options->autoshoot = c->value;
									} break;
									case 1: // mouse control
									{
										_game->options->mouse_control = c->value;
									} break;
								}
							}
							
							_game->state = state_menu;
						} break;
						case 1: // reset progress
						{
							game_reset(_game);
						} break;
						case 2: // reset options
						{
							game_settings_defaults(_game->options);
							set_proper_checkboxes();
						} break;
					}
				}
			}
			for (int i = 0; i < _game->checkboxes->length; i++)
			{
				checkbox* c = (checkbox*)array_list_get(_game->checkboxes, i);
				
				checkbox_update(c, _game);
			}
		} break;
	}
}
void paint()
{
	ClearBackground(BLACK);
	
	switch (_game->state)
	{
		default:
		{
		} break;
		case state_game:
		{
			// draw the animated background
			DrawTexture(_game->background, 0, _game->_bg1y, WHITE);
			DrawTexture(_game->background, 0, _game->_bg2y, WHITE);
			
			for (int i = 0; i < _game->bullets->length; i++)
			{
				entity_bullet* bpointer = (entity_bullet*)array_list_get(_game->bullets, i);
				if (bpointer != NULL)
					if (!bpointer->disposed)
						entity_bullet_paint(bpointer);
			}
			for (int i = 0; i < _game->alien_bullets->length; i++)
			{
				entity_alien_bullet* bpointer = (entity_alien_bullet*)array_list_get(_game->alien_bullets, i);
				if (bpointer != NULL)
					if (!bpointer->disposed)
						entity_alien_bullet_paint(bpointer);
			}
			for (int i = 0; i < _game->entities->length; i++)
			{
				entity_alien* balien = (entity_alien*)array_list_get(_game->entities, i);
				if (balien != NULL)
					if (!balien->disposed)
						entity_alien_paint(balien);
			}
			for (int i = 0; i < _game->asteroids->length; i++)
			{
				entity_asteroid* ea = (entity_asteroid*)array_list_get(_game->asteroids, i);

				if (!ea->disposed)
				{
					entity_asteroid_paint(ea);
				}
			}
			
			entity_player_paint(_game->player, HEIGHT - 75);
			
			for (int i = 0; i < _game->particles->length; i++)
			{
				particle* pparticle = (particle*)array_list_get(_game->particles, i);
				if (pparticle != NULL)
					if (!pparticle->disposed)
						particle_paint(pparticle);
			}
			for (int i = 0; i < _game->buttons_ingame->length; i++)
			{
				button* b = (button*)array_list_get(_game->buttons_ingame, i);
				
				button_paint(b);
			}
			
			DrawRectangle(10, 10, _game->player->health * PLAYER_HEALTH_PIXEL, 7, RED);
			
			// draw the level
			char* toPrint = (char*)malloc(5 * sizeof(char));
			sprintf(toPrint, "%d", _game->level);
			DrawText(toPrint, 10, 20, 15, WHITE);
			free(toPrint);
			
			// draw the score
			toPrint = (char*)malloc(5 * sizeof(char));
			sprintf(toPrint, "%d", _game->score);
			DrawText(toPrint, WIDTH - (20 * strlen(toPrint)), 10, 30, WHITE);
			free(toPrint);
			
			
			
			if (_game->level_dialogs[_game->level] != -1)
			{				
				dialog* currentD = ((dialog*)(array_list_get(_game->dialogs, _game->level_dialogs[_game->level])));
				
				dialog_paint(currentD);
			}
			
			// always at the end when unpaused
			if (_game->player->dead)
				mmenu_paint(_game->menu_death);
				
			// always at the end at any time
			if (_game->paused)
				mmenu_paint(_game->menu_pause);
		} break;
		case state_menu:
		{
			// draw the animated background
			DrawTexture(_game->background, 0, _game->_bg1y, WHITE);
			DrawTexture(_game->background, 0, _game->_bg2y, WHITE);
			
			
			
			// draw the buttons
			for (int i = 0; i < _game->buttons->length; i++)
				button_paint((button*)array_list_get(_game->buttons, i));
		} break;
		
		case state_options:
		{
			// draw the animated background
			DrawTexture(_game->background, 0, _game->_bg1y, WHITE);
			DrawTexture(_game->background, 0, _game->_bg2y, WHITE);
			
			
				
			{
				int bx = 5;
				int by = 120;
				int size = 20;
				Color col = LIGHTGRAY;
				
				DrawText("Autoshoot:", bx, by, size, col);
				DrawText("Mouse control:", bx, by + (size * 2), size, col);
			}
			
			for (int i = 0; i < _game->buttons_opt->length; i++)
			{
				button* b = (button*)array_list_get(_game->buttons_opt, i);
				
				button_paint(b);
			}
			for (int i = 0; i < _game->checkboxes->length; i++)
			{
				checkbox* c = (checkbox*)array_list_get(_game->checkboxes, i);
				
				checkbox_paint(c);
			}
		} break;
	}
}
