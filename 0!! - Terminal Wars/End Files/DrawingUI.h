#ifndef DRAWINGUI_H
#define DRAWINGUI_H

void screenSplash();
void mapDraw (game *data);
void drawUnit (game *data, short x, short y, short arrayPos);
void drawField (game *data, short x, short y);
void drawUnitUI (game *data, short x, short y);
void drawFieldUI (game *data, short x, short y);
void testDrawing (game *data);
void drawMenu (game *data);

#endif