/*
 */
/*!
 * \file panorama.cpp
 * \weakgroup panorama
 *
 * @{
 */
#include "panorama.h"

#include <QDebug>

/******************************************************************************/
Panorama::Panorama()
{
    for (int z = 0; z < 6; z++) {
        for (int x = 0; x < 26; x++) {
            for (int y = 0; y < 13; y++) {
                tiles[z][x][y] = 0;
            }
        }
    }
}

/******************************************************************************/
Panorama::~Panorama()
{
    clear();
}

/******************************************************************************/
bool Panorama::checkCoords(int xCoord, int yCoord, int zoomLevel)
{
    bool ok = true;

    switch(zoomLevel) {
    case 0:
        if (xCoord >= 0 && xCoord <= 0 && yCoord >= 0 && yCoord <= 0) break;
        else ok = false;
        break;
    case 1:
        if (xCoord >= 0 && xCoord <= 1 && yCoord >= 0 && yCoord <= 0) break;
        else ok = false;
        break;
    case 2:
        if (xCoord >= 0 && xCoord <= 3 && yCoord >= 0 && yCoord <= 1) break;
        else ok = false;
        break;
    case 3:
        if (xCoord >= 0 && xCoord <= 5 && yCoord >= 0 && yCoord <= 2) break;
        else ok = false;
        break;
    case 4:
        if (xCoord >= 0 && xCoord <= 12 && yCoord >= 0 && yCoord <= 6) break;
        else ok = false;
        break;
    case 5:
        if (xCoord >= 0 && xCoord <= 25 && yCoord >= 0 && yCoord <= 12) break;
        else ok = false;
        break;
    default:
        ok = false;
        break;
    }

    return ok;
}

/******************************************************************************/
/*!
  * Check zoom level.
  * \return true if zoom level is full.
  * \return false if every zoom level is not ready.
  */
/******************************************************************************/
bool Panorama::isZoomLevelFull(int zoomLevel)
{
    if(zoomLevel < 0) {
        zoomLevel = 0;
        qDebug() << "Warning: Invalid zoom level. Forced zoom level to 0.";
    }
    if(zoomLevel > 5) {
        zoomLevel = 5;
        qDebug() << "Warning: Invalid zoom level. Forced zoom level to 5.";
    }

    int xMin = 0;
    int xMax = 0;
    int yMin = 0;
    int yMax = 0;
    int tileCount = 0;
    int tileMax = 0;

    switch(zoomLevel) {
    case 0:
        xMax = 1;
        yMax = 1;
        break;
    case 1:
        xMax = 2;
        yMax = 1;
        break;
    case 2:
        xMax = 4;
        yMax = 2;
        break;
    case 3:
        xMax = 6;
        yMax = 3;
        break;
    case 4:
        xMax = 13;
        yMax = 7;
        break;
    case 5:
        xMax = 26;
        yMax = 13;
        break;
    default: // Should never happen
        break;
    }

    tileMax = (xMin + xMax) * (yMin + yMax);

    for (int x = 0; x < xMax; x++) {
        for (int y = 0; y < yMax; y++) {
            if(tiles[zoomLevel][x][y] != 0)
                tileCount++;
        }
    }

    if(tileCount == tileMax)
        return true;
    else
        return false;
}

/******************************************************************************/
/*! \brief Add tile to panorama.
  * Add tile to panorama. Gets coordinates from given tile and
  * saves it to appropriate place.
  * \param tile Reference to tile.
  * \return 0 if everything went well.
  * \return Something else when some error occured.
  */
/******************************************************************************/
int Panorama::addTile(Tile &tile)
{
    int x = tile.getXCoord();
    int y = tile.getYCoord();
    int z = tile.getZoomLevel();

    if (checkCoords(x, y, z)) {
        if(tiles[z][x][y] != 0) {
            qDebug() << "Warning: Overwriting tile.";
            delete tiles[z][x][y];
        }
        tiles[z][x][y] = &tile;
    } else {
        QString error = QString("Panorama::addTile(): Invalid coordinates: zoomLevel = %1, xCoord = %2, yCoord = %3").arg(z).arg(x).arg(y);
        qDebug() << error;
        return -1; // error
    }

    if(isZoomLevelFull(z))
        emit zoomLevelReady(z);

    return 0; // ok
}

/******************************************************************************/
/*!
  * Return particular tile.
  * \param xCoord X-coordinate.
  * \param yCoord Y-coordinate.
  * \param zoomLevel Zoom level.
  * \return Pointer to tile if its found.
  * \return 0 if tile is not found.
  */
/******************************************************************************/
Tile *Panorama::getTile(int xCoord,
             int yCoord,
             int zoomLevel)
{
    Tile* tile = 0;
    if (checkCoords(xCoord, yCoord, zoomLevel)) {
        tile = tiles[zoomLevel][xCoord][yCoord];
    } else {
        QString error = QString("Panorama::getTile(): Invalid coordinates: zoomLevel = %1, xCoord = %2, yCoord = %3").arg(zoomLevel).arg(xCoord).arg(yCoord);
        qDebug() << error;
    }
    return tile;
}

/******************************************************************************/
/*!
  * Clear all tiles in this panorama.
  */
/******************************************************************************/
void Panorama::clear()
{
    for (int z = 0; z < 6; z++) {
        for (int x = 0; x < 26; x++) {
            for (int y = 0; y < 13; y++) {
                if(tiles[z][x][y] != 0)
                    delete tiles[z][x][y];
                tiles[z][x][y] = 0;
            }
        }
    }
}

/*!
 * @}
 */
