//
// Created by xinitrix on 10/5/26.
//

#ifndef NJAKO_SCNHASHMAP_H
#define NJAKO_SCNHASHMAP_H

#include "hashArray.h"
#include "scene.h"

HA_DECLARE_INTERFACE(scnHashMapIface, scnHashMap, scene)
HA_DECLARE_CONTAINER(scnHashMap, scnHashMap_new, scnHashMapIface, harr)

#endif //NJAKO_SCNHASHMAP_H
