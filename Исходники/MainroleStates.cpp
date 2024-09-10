void MainroleAttack::execute(Mainrole* stateOwner, double dt) {
	if(!stateOwner->getTargetSprite() || stateOwner->getTargetSprite()->getDead()) { // 如果敌人已经死亡
		return stateOwner->getStateMachine()->changeState(MainroleStand::instance());	
	}
	stateOwner->detectEnemyOval(stateOwner->getTargetSprite()); // 检测敌人是否在攻击范围
	if(stateOwner->getIsRoleInAttack()) { // 如果敌人还在攻击范围
        CCPoint toTarget = stateOwner->getTargetSprite()->getPosition() - stateOwner->getPosition();
		stateOwner->setDirect(stateOwner->getClosestDirect(toTarget.normalize()));
		stateOwner->runActionFight(dt);
	}
	else { // 如果敌人不在攻击范围
		return stateOwner->getStateMachine()->changeState(MainrolePursuit::instance());	
	}
}