#include "Defines.h"

void screenSplash();
void mapDraw (game *data);
int moveCursor (game *data);
void drawUnit (game *data, short x, short y, short arrayPos);
void drawField (game *data, short x, short y);
void drawUnitUI (game *data, short x, short y);
void drawFieldUI (game *data, short x, short y);
short findUnit (game *data, short x, short y);
void testDrawing (game *data);