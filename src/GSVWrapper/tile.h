/*
 * Author Jarno Tuovinen
 */
/*!
 * \file tile.h
 * \defgroup tile Tile
 * \ingroup panorama
 *
 * @{
 */
#ifndef TILE_H
#define TILE_H

#include <QImage>

/******************************************************************************/
/*!
 * \ingroup tile
 * \brief Object for storing a single tile of a panorama.
 *
 * \sa xmlparser
 */
/******************************************************************************/
class Tile
{
public:
    /*! \ingroup tile
     * \brief The constructor. Stores a tile, the zoom-level and coordinates in
     *     the whole panorama.
     * \param xCoord X-coordinate in a panorama
     * \param yCoord Y-coordinate in a panorama
     * \param zoomLevel Zoom-level of a panorama
     * \sa panorama
     */
    Tile(const int xCoord,
         const int yCoord,
         const int zoomLevel,
         const QImage tile); //!< A constructor to be used

    /*! \ingroup tile
     * \brief Returns the X-coordinate of a tile.
     * \return X-coordinate
     */
    int getXCoord() const; //!< Return x-coordinate of the tile


    /*! \ingroup tile
     * \brief Returns the Y-coordinate of a tile.
     * \return Y-coordinate
     */
    int getYCoord() const;

    /*! \ingroup tile
     * \brief Returns the tile as an image.
     * \return Tile image
     */
    QImage getTile() const;


    /*! \ingroup tile
     * \brief Returns the zoom-level of a tile.
     * \return Zoom-level
     */
    int getZoomLevel() const;

//private: // TODO: Uncomment from final version

    const int xCoord;
    const int yCoord;
    const int zoomLevel;
    const QImage tile;
};

#endif // TILE_H
/*!
 * @}
 */
