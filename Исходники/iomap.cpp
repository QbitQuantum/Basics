bool IOMap::loadMap(Map* map, const std::string& identifier)
{
	int64_t start = OTSYS_TIME();

	FileLoader f;
	if (!f.openFile(identifier.c_str(), "OTBM")) {
		std::ostringstream ss;
		ss << "Could not open the file " << identifier << '.';
		setLastErrorString(ss.str());
		return false;
	}

	uint32_t type;
	PropStream propStream;

	NODE root = f.getChildNode(nullptr, type);
	if (!f.getProps(root, propStream)) {
		setLastErrorString("Could not read root property.");
		return false;
	}

	const OTBM_root_header* root_header;
	if (!propStream.readStruct(root_header)) {
		setLastErrorString("Could not read header.");
		return false;
	}

	uint32_t headerVersion = root_header->version;
	if (headerVersion <= 0) {
		//In otbm version 1 the count variable after splashes/fluidcontainers and stackables
		//are saved as attributes instead, this solves alot of problems with items
		//that is changed (stackable/charges/fluidcontainer/splash) during an update.
		setLastErrorString("This map need to be upgraded by using the latest map editor version to be able to load correctly.");
		return false;
	}

	if (headerVersion > 2) {
		setLastErrorString("Unknown OTBM version detected.");
		return false;
	}

	if (root_header->majorVersionItems < 3) {
		setLastErrorString("This map need to be upgraded by using the latest map editor version to be able to load correctly.");
		return false;
	}

	if (root_header->majorVersionItems > Items::dwMajorVersion) {
		setLastErrorString("The map was saved with a different items.otb version, an upgraded items.otb is required.");
		return false;
	}

	if (root_header->minorVersionItems < CLIENT_VERSION_810) {
		setLastErrorString("This map needs to be updated.");
		return false;
	}

	if (root_header->minorVersionItems > Items::dwMinorVersion) {
		std::cout << "[Warning - IOMap::loadMap] This map needs an updated items.otb." << std::endl;
	}

	std::cout << "> Map size: " << root_header->width << "x" << root_header->height << '.' << std::endl;
	map->width = root_header->width;
	map->height = root_header->height;

	NODE nodeMap = f.getChildNode(root, type);
	if (type != OTBM_MAP_DATA) {
		setLastErrorString("Could not read data node.");
		return false;
	}

	if (!f.getProps(nodeMap, propStream)) {
		setLastErrorString("Could not read map data attributes.");
		return false;
	}

	std::string mapDescription;
	std::string tmp;

	uint8_t attribute;
	while (propStream.read<uint8_t>(attribute)) {
		switch (attribute) {
			case OTBM_ATTR_DESCRIPTION:
				if (!propStream.readString(mapDescription)) {
					setLastErrorString("Invalid description tag.");
					return false;
				}
				break;

			case OTBM_ATTR_EXT_SPAWN_FILE:
				if (!propStream.readString(tmp)) {
					setLastErrorString("Invalid spawn tag.");
					return false;
				}

				map->spawnfile = identifier.substr(0, identifier.rfind('/') + 1);
				map->spawnfile += tmp;
				break;

			case OTBM_ATTR_EXT_HOUSE_FILE:
				if (!propStream.readString(tmp)) {
					setLastErrorString("Invalid house tag.");
					return false;
				}

				map->housefile = identifier.substr(0, identifier.rfind('/') + 1);
				map->housefile += tmp;
				break;

			default:
				setLastErrorString("Unknown header node.");
				return false;
		}
	}

	NODE nodeMapData = f.getChildNode(nodeMap, type);
	while (nodeMapData != NO_NODE) {
		if (f.getError() != ERROR_NONE) {
			setLastErrorString("Invalid map node.");
			return false;
		}

		if (type == OTBM_TILE_AREA) {
			if (!f.getProps(nodeMapData, propStream)) {
				setLastErrorString("Invalid map node.");
				return false;
			}

			const OTBM_Destination_coords* area_coord;
			if (!propStream.readStruct(area_coord)) {
				setLastErrorString("Invalid map node.");
				return false;
			}

			int32_t base_x = area_coord->x;
			int32_t base_y = area_coord->y;
			int32_t base_z = area_coord->z;

			NODE nodeTile = f.getChildNode(nodeMapData, type);
			while (nodeTile != NO_NODE) {
				if (f.getError() != ERROR_NONE) {
					setLastErrorString("Could not read node data.");
					return false;
				}

				if (type != OTBM_TILE && type != OTBM_HOUSETILE) {
					setLastErrorString("Unknown tile node.");
					return false;
				}

				if (!f.getProps(nodeTile, propStream)) {
					setLastErrorString("Could not read node data.");
					return false;
				}

				const OTBM_Tile_coords* tile_coord;
				if (!propStream.readStruct(tile_coord)) {
					setLastErrorString("Could not read tile position.");
					return false;
				}

				uint16_t px = base_x + tile_coord->x;
				uint16_t py = base_y + tile_coord->y;
				uint16_t pz = base_z;

				bool isHouseTile = false;
				House* house = nullptr;
				Tile* tile = nullptr;
				Item* ground_item = nullptr;
				uint32_t tileflags = TILESTATE_NONE;

				if (type == OTBM_HOUSETILE) {
					uint32_t houseId;
					if (!propStream.read<uint32_t>(houseId)) {
						std::ostringstream ss;
						ss << "[x:" << px << ", y:" << py << ", z:" << pz << "] Could not read house id.";
						setLastErrorString(ss.str());
						return false;
					}

					house = map->houses.addHouse(houseId);
					if (!house) {
						std::ostringstream ss;
						ss << "[x:" << px << ", y:" << py << ", z:" << pz << "] Could not create house id: " << houseId;
						setLastErrorString(ss.str());
						return false;
					}

					tile = new HouseTile(px, py, pz, house);
					house->addTile(reinterpret_cast<HouseTile*>(tile));
					isHouseTile = true;
				}

				//read tile attributes
				while (propStream.read<uint8_t>(attribute)) {
					switch (attribute) {
						case OTBM_ATTR_TILE_FLAGS: {
							uint32_t flags;
							if (!propStream.read<uint32_t>(flags)) {
								std::ostringstream ss;
								ss << "[x:" << px << ", y:" << py << ", z:" << pz << "] Failed to read tile flags.";
								setLastErrorString(ss.str());
								return false;
							}

							if ((flags & TILESTATE_PROTECTIONZONE) == TILESTATE_PROTECTIONZONE) {
								tileflags |= TILESTATE_PROTECTIONZONE;
							} else if ((flags & TILESTATE_NOPVPZONE) == TILESTATE_NOPVPZONE) {
								tileflags |= TILESTATE_NOPVPZONE;
							} else if ((flags & TILESTATE_PVPZONE) == TILESTATE_PVPZONE) {
								tileflags |= TILESTATE_PVPZONE;
							}

							if ((flags & TILESTATE_NOLOGOUT) == TILESTATE_NOLOGOUT) {
								tileflags |= TILESTATE_NOLOGOUT;
							}
							break;
						}

						case OTBM_ATTR_ITEM: {
							Item* item = Item::CreateItem(propStream);
							if (!item) {
								std::ostringstream ss;
								ss << "[x:" << px << ", y:" << py << ", z:" << pz << "] Failed to create item.";
								setLastErrorString(ss.str());
								return false;
							}

							if (isHouseTile && item->isMoveable()) {
								std::cout << "[Warning - IOMap::loadMap] Moveable item with ID: " << item->getID() << ", in house: " << house->getId() << ", at position [x: " << px << ", y: " << py << ", z: " << pz << "]." << std::endl;
								delete item;
							} else {
								if (item->getItemCount() <= 0) {
									item->setItemCount(1);
								}

								if (tile) {
									tile->internalAddThing(item);
									item->startDecaying();
									item->setLoadedFromMap(true);
								} else if (item->isGroundTile()) {
									delete ground_item;
									ground_item = item;
								} else {
									tile = createTile(ground_item, item, px, py, pz);
									tile->internalAddThing(item);
									item->startDecaying();
									item->setLoadedFromMap(true);
								}
							}
							break;
						}

						default:
							std::ostringstream ss;
							ss << "[x:" << px << ", y:" << py << ", z:" << pz << "] Unknown tile attribute.";
							setLastErrorString(ss.str());
							return false;
					}
				}

				NODE nodeItem = f.getChildNode(nodeTile, type);
				while (nodeItem) {
					if (type != OTBM_ITEM) {
						std::ostringstream ss;
						ss << "[x:" << px << ", y:" << py << ", z:" << pz << "] Unknown node type.";
						setLastErrorString(ss.str());
						return false;
					}

					PropStream stream;
					if (!f.getProps(nodeItem, stream)) {
						setLastErrorString("Invalid item node.");
						return false;
					}

					Item* item = Item::CreateItem(stream);
					if (!item) {
						std::ostringstream ss;
						ss << "[x:" << px << ", y:" << py << ", z:" << pz << "] Failed to create item.";
						setLastErrorString(ss.str());
						return false;
					}

					if (!item->unserializeItemNode(f, nodeItem, stream)) {
						std::ostringstream ss;
						ss << "[x:" << px << ", y:" << py << ", z:" << pz << "] Failed to load item " << item->getID() << '.';
						setLastErrorString(ss.str());
						delete item;
						return false;
					}

					if (isHouseTile && item->isMoveable()) {
						std::cout << "[Warning - IOMap::loadMap] Moveable item with ID: " << item->getID() << ", in house: " << house->getId() << ", at position [x: " << px << ", y: " << py << ", z: " << pz << "]." << std::endl;
						delete item;
					} else {
						if (item->getItemCount() <= 0) {
							item->setItemCount(1);
						}

						if (tile) {
							tile->internalAddThing(item);
							item->startDecaying();
							item->setLoadedFromMap(true);
						} else if (item->isGroundTile()) {
							delete ground_item;
							ground_item = item;
						} else {
							tile = createTile(ground_item, item, px, py, pz);
							tile->internalAddThing(item);
							item->startDecaying();
							item->setLoadedFromMap(true);
						}
					}

					nodeItem = f.getNextNode(nodeItem, type);
				}

				if (!tile) {
					tile = createTile(ground_item, nullptr, px, py, pz);
				}

				tile->setFlag(static_cast<tileflags_t>(tileflags));

				map->setTile(px, py, pz, tile);

				nodeTile = f.getNextNode(nodeTile, type);
			}
		} else if (type == OTBM_TOWNS) {
			NODE nodeTown = f.getChildNode(nodeMapData, type);
			while (nodeTown != NO_NODE) {
				if (type != OTBM_TOWN) {
					setLastErrorString("Unknown town node.");
					return false;
				}

				if (!f.getProps(nodeTown, propStream)) {
					setLastErrorString("Could not read town data.");
					return false;
				}

				uint32_t townId;
				if (!propStream.read<uint32_t>(townId)) {
					setLastErrorString("Could not read town id.");
					return false;
				}

				Town* town = map->towns.getTown(townId);
				if (!town) {
					town = new Town(townId);
					map->towns.addTown(townId, town);
				}

				std::string townName;
				if (!propStream.readString(townName)) {
					setLastErrorString("Could not read town name.");
					return false;
				}

				town->setName(townName);

				const OTBM_Destination_coords* town_coords;
				if (!propStream.readStruct(town_coords)) {
					setLastErrorString("Could not read town coordinates.");
					return false;
				}

				town->setTemplePos(Position(town_coords->x, town_coords->y, town_coords->z));

				nodeTown = f.getNextNode(nodeTown, type);
			}
		} else if (type == OTBM_WAYPOINTS && headerVersion > 1) {
			NODE nodeWaypoint = f.getChildNode(nodeMapData, type);
			while (nodeWaypoint != NO_NODE) {
				if (type != OTBM_WAYPOINT) {
					setLastErrorString("Unknown waypoint node.");
					return false;
				}

				if (!f.getProps(nodeWaypoint, propStream)) {
					setLastErrorString("Could not read waypoint data.");
					return false;
				}

				std::string name;
				if (!propStream.readString(name)) {
					setLastErrorString("Could not read waypoint name.");
					return false;
				}

				const OTBM_Destination_coords* waypoint_coords;
				if (!propStream.readStruct(waypoint_coords)) {
					setLastErrorString("Could not read waypoint coordinates.");
					return false;
				}

				map->waypoints[name] = Position(waypoint_coords->x, waypoint_coords->y, waypoint_coords->z);

				nodeWaypoint = f.getNextNode(nodeWaypoint, type);
			}
		} else {
			setLastErrorString("Unknown map node.");
			return false;
		}

		nodeMapData = f.getNextNode(nodeMapData, type);
	}

	std::cout << "> Map loading time: " << (OTSYS_TIME() - start) / (1000.) << " seconds." << std::endl;
	return true;
}