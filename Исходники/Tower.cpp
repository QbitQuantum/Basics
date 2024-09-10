Floor* Tower::getFloor(int floorId)
{
	Floor* floor = _floors.at(floorId);
	// 楼层缓存初始化
	if(floor == nullptr)
	{
		ValueMap model;
		model["url"] = _floorUrls[cocos2d::Value(floorId).asString()];
		model["id"] = floorId;
		model["name"] = StringUtils::format("floor%d", floorId);
		model["towerId"] = getId();
		floor = Floor::create(model);
		_floors.insert(floorId, floor);
		floor->setTower(this);
	}
	return floor;
}