/*!
 * \file tile.cpp
 * \weakgroup tile
 * Author: Veijo Pesonen
 * @{
 */
#include <QImage>

#include "tile.h"


/******************************************************************************/
Tile::Tile(const int xCoord,
        const int yCoord,
        const int zoomLevel,
        const QImage tile): xCoord(xCoord),
                            yCoord(yCoord),
                            zoomLevel(zoomLevel),
                            tile(tile)
{
}


/******************************************************************************/
int Tile::getXCoord() const {
    return this->xCoord;
}


/******************************************************************************/
int Tile::getYCoord() const {
    return this->yCoord;
}


/******************************************************************************/
QImage Tile::getTile() const {
    return this->tile;
}


/******************************************************************************/
int Tile::getZoomLevel() const {
    return this->zoomLevel;
}




/*
 * @}
 */
