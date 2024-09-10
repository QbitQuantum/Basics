TETraceResult PathFinder::naviByPath(double dt) {
	// 如果目标点无效,则不走
	if(getTarget().equals(INVALID_POINT)) {
		//stopAllActions();
		setTarget(INVALID_POINT);
		return eTraceResultFailure;
	}
	// 如果下一个路径点在地图外或是墙,则不走(应该不会出现这种情况)
	CCPoint targetTilePos = _map->realPosToTilePos(getTarget());
	if(int(targetTilePos.x + targetTilePos.y) == -2 || _map->getTileType(targetTilePos) == emWall) {
		//stopAllActions();
		setTarget(INVALID_POINT);
		return eTraceResultFailure;
	}
	// 如果已经到达目标点,则寻找下一个目标点
	if(getPosition().getDistanceSq(getTarget()) < 1) {
		//CCLog("reach half way pos");
		//stopAllActions();
		if(_currPathNode == _shortestPath.size() - 1) { // 如果目标点是最后一个,则寻路结束
			//stopAllActions();
			setTarget(INVALID_POINT);
			return eTraceResultSuccess;
		}
		else { // 如果目标点后面还有,则继续
			//CCLog("go to next pos");
			++_currPathNode;
			_target = _map->getNaviGraph().getNode(_shortestPath[_currPathNode]).getCenterPos();
			CCPoint toTarget = getTarget() - getPosition();
			setDirect(_map->getClosestDirect(toTarget.normalize()));
		}
	}
	// 根据不同的方向,执行不同的动作
	TEActionState actionState = _walkAnimations->runDirect(this, getDirect(), dt);
	// 走向目标点
	CCPoint tilePos = _map->realPosToTilePos(getPosition());
	int tileZorder = tilePos.x + tilePos.y;
	setZOrder(tileZorder);
	CCPoint toTarget = getTarget() - getPosition();
	toTarget = toTarget.normalize();
	setPosition(getPosition() + toTarget * _speed * dt);
	return eTraceResultHalfway;
}