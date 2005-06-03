#ifndef TILE_H
#define TILE_H

#include "macros.h"
#include "map.h"

typedef enum TileType {
	MP_CLEAR,
	MP_RAILWAY,
	MP_STREET,
	MP_HOUSE,
	MP_TREES,
	MP_STATION,
	MP_WATER,
	MP_VOID, // invisible tiles at the SW and SE border
	MP_INDUSTRY,
	MP_TUNNELBRIDGE,
	MP_UNMOVABLE
} TileType;

/* XXX: This should be moved out to a new file (rail.h) along with some other
 * cleanups. I'll do that after 0.4) */
typedef enum {
	RAILTYPE_RAIL   = 0,
	RAILTYPE_MONO   = 1,
	RAILTYPE_MAGLEV = 2,
	RAILTYPE_END,
	RAILTYPE_MASK   = 0x3,
	INVALID_RAILTYPE = 0xFF,
} RailType;


void SetMapExtraBits(TileIndex tile, byte flags);
uint GetMapExtraBits(TileIndex tile);

uint GetTileSlope(TileIndex tile, uint *h);
uint GetTileZ(TileIndex tile);

static inline bool CorrectZ(uint tileh)
{
	/* tile height must be corrected if the north corner is not raised, but
	 * any other corner is. These are the cases 1 till 7 */
	return IS_INT_INSIDE(tileh, 1, 8);
}

static inline uint TileHeight(TileIndex tile)
{
	assert(tile < MapSize());
	return GB(_map_type_and_height[tile], 0, 4);
}

static inline void SetTileHeight(TileIndex tile, uint height)
{
	assert(tile < MapSize());
	assert(height < 16);
	SB(_map_type_and_height[tile], 0, 4, height);
}

static inline uint TilePixelHeight(TileIndex tile)
{
	return TileHeight(tile) * 8;
}

static inline TileType GetTileType(TileIndex tile)
{
	assert(tile < MapSize());
	return GB(_map_type_and_height[tile], 4, 4);
}

static inline void SetTileType(TileIndex tile, TileType type)
{
	assert(tile < MapSize());
	SB(_map_type_and_height[tile], 4, 4, type);
}

static inline bool IsTileType(TileIndex tile, TileType type)
{
	return GetTileType(tile) == type;
}

static inline Owner GetTileOwner(TileIndex tile)
{
	assert(tile < MapSize());
	assert(!IsTileType(tile, MP_HOUSE));
	assert(!IsTileType(tile, MP_VOID));
	assert(!IsTileType(tile, MP_INDUSTRY));

	return _map_owner[tile];
}

static inline bool IsTileOwner(TileIndex tile, Owner owner)
{
	return GetTileOwner(tile) == owner;
}

#endif
