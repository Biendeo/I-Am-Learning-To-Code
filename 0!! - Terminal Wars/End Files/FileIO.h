#ifndef FILEIO_H
#define FILEIO_H

void loadMapFileData (game *data, FILE *file);
void loadMapDefaultData (game *data);
void translateMapData (game *data, unsigned char tile, short x, short y);

#endif