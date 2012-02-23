
#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"

// La classe screen, dont tous les membres sont statiques, regroupe
// les fonctions d'affichage à l'écran

class screen {

	public :
	static void print(char *string);
	static void scrollup(unsigned int n);
	static void move_cursor (u8 x, u8 y);
	static void show_cursor (void);
	static void putcar(uchar);
	static void set_attr(char);

	private:
	static char kX;
	static char kY;
	static char kattr;
};

#endif
