void PathCmp::search (Eigen::Vector2f targetPos_) {
    _level = LogicSystem::getInstance()->getLevel();
    for (auto it = _openList.begin(); it != _openList.end(); ++ it) {
        if (*it != nullptr)
            delete *it;
    }
    _openList.clear();

    for (auto it = _closedList.begin(); it != _closedList.end(); ++ it) {
        if (*it != nullptr)
            delete *it;
    }
    _closedList.clear();
    _shortestPath.clear();

    auto posCmp = getEntity()->GET_CMP(PositionComponent);
    _srcIdx = _level->posToTileIndex(posCmp->getPosition());
    _tarIdx = _level->posToTileIndex(targetPos_);
    if (_srcIdx == _tarIdx)
        return;

    if (_level->isTileObstacle(_tarIdx.x(), _tarIdx.y()))
        return;

    PathNode* srcNode = new PathNode(_srcIdx);
    calcCostH(srcNode);
    _openList.push_back(srcNode);
    do {
        PathNode* curNode = _openList[0];
        _closedList.push_back(curNode);
        _openList.erase(_openList.begin());

        if (curNode->getIndex() == _tarIdx) {
            PathNode* walkNode = curNode;
            _shortestPath.clear();
            do {
                Eigen::Vector2f pos;
                pos.x() = _level->tileIndexXToPosX(walkNode->getIndex().x());
                pos.y() = _level->tileIndexYToPosY(walkNode->getIndex().y());
                _shortestPath.push_front(pos);
                walkNode = walkNode->getParent();
            } while (walkNode);
            for (auto it = _openList.begin(); it != _openList.end(); ++ it) {
                if (*it != nullptr)
                    delete *it;
            }
            _openList.clear();
            for (auto it = _closedList.begin(); it != _closedList.end(); ++ it) {
                if (*it != nullptr)
                    delete *it;
            }
            _closedList.clear();
            break;
        }

        putAdjacentTiles(curNode);
        for (auto it = _adjacentTiles.begin(); it != _adjacentTiles.end(); ++ it) {
            bool isInClosedList = false;
            for (int i = 0; i < _closedList.size(); ++ i)
                if ((*it) == _closedList[i]->getIndex())
                    isInClosedList = true;
            if (isInClosedList) continue;

            auto node = new PathNode(*it);
            int costGToAdd = calcCostG(node, curNode);
            std::vector<PathNode *>::iterator opit = _openList.begin();
            while (opit != _openList.end()) {
                if ((*opit)->getIndex() == node->getIndex())
                    break;
                ++ opit;
            }

            // already on openlist
            if (opit!= _openList.end()) {
                delete node;
                node = (*opit);
                if (curNode->getCostG() + costGToAdd < node->getCostG())
                    node->setCostG(curNode->getCostG() + costGToAdd);
            } else {
                node->setParent(curNode);
                node->setCostG(curNode->getCostG() + costGToAdd);
                calcCostH(node);
                addOpenList(node);
            }
        }
    } while (_openList.size() > 0);
}