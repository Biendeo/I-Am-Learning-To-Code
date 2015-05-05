#ifndef DRAWINGUI_H
#define DRAWINGUI_H

void screenSplash();
void mapDraw (game *data);
void drawUnit (game *data, short x, short y, short arrayPos);
void drawField (game *data, short x, short y);
void drawUnitUI (game *data, short x, short y);
void drawFieldUI (game *data, short x, short y);
void drawMoveUI (game *data, short x, short y);
void drawAttackUI (game *data, short attacker, short x, short y);
void drawUnitName (game *data, short selectedUnit);
void drawTileName (game *data, short x, short y);
void drawBattleResult (game *data, short attacker, short defender, float damage, char mode);
void testDrawing (game *data);
void drawMenu (game *data);

#endif