/*!
 * \file panorama.h
 * \defgroup panorama Panorama
 * @{
 */

#ifndef PANORAMA_H
#define PANORAMA_H

#include <QObject>
#include <QString>

#include "tile.h"

/******************************************************************************/
/*!
  * \ingroup panorama
  * \brief Panorama class contains every tile of one panorama and metadata.
  * \note This class is used with only one zoom level although it contains array
  *       with 6 zoom levels.
*/
/******************************************************************************/
class Panorama: public QObject
{
    Q_OBJECT

public:
    Panorama(); //!< A constructor.
    ~Panorama(); //!< A destructor.

    int addTile(Tile &tile);
    Tile *getTile(int xCoord,
                  int yCoord,
                  int zoomLevel);

    void clear();

private:
    bool checkCoords(int xCoord, int yCoord, int zoomLevel);
    bool isZoomLevelFull(int zoomLevel);

    Tile *tiles[6][26][13];

signals:
    void zoomLevelReady(int zoomLevel); //!< Emitted when zoomlevel is ready
};

#endif // PANORAMA_H
/*!
 * @}
 */
