void Leukocyte::updateLeukocyte(float dt, const Leukocyte *other)
{
    static int lockFrame = 0;
    float currentScale = this->getCurrentScale();
    
    if (currentState == LeukocyteState::LOCK) {
        lockFrame++;
        
        if (lockFrame >= PLAYER_MOVING_LOCK_FRAME) {
            lockFrame = 0;

            currentState = LeukocyteState::STOP;
        }
    }
    else {
        Vec2 playerPos = this->getPosition();
        float distance = playerLastTouchPos.distance(playerPos);
        
        // 距離がしきい値以下なら加速度を再計算して速度固定
        if (distance <= ATTRACTED_DISTANCE * (1.0f / currentScale) && currentState == LeukocyteState::MOVE && !isCPU) {
            playerAccelerate =  this->getCurrentPlayerAccelerateToTouchPosition();
            playerVelocity = sqrt(3.0f * MAX_VELOCITY * (1.0f / currentScale)) * playerAccelerate.getNormalized();
        }
        else {
            if (currentState == LeukocyteState::DASH) {
                if (playerVelocity.getLengthSq() > MAX_VELOCITY * (1.0f / currentScale)) {
                    playerAccelerate = this->getCurrentPlayerAccelerateToTouchPosition();
                    Vec2 addedVelocity = playerVelocity - playerAccelerate * 10 * dt * (1.0f / currentScale);
                    if (addedVelocity.getLengthSq() > playerVelocity.getLengthSq()) {
                        addedVelocity = playerVelocity + playerAccelerate * 10 * dt * (1.0f / currentScale);
                    }
                    playerVelocity = addedVelocity;
                }
                else {
                    currentState = LeukocyteState::MOVE;
                }
            }
            else {
                // 加速度から速度計算
                playerAccelerate = this->getCurrentPlayerAccelerateToTouchPosition();
                Vec2 addedVelocity = playerVelocity + playerAccelerate * dt * (1.0f / currentScale);
                
                // max値を超えない場合のみプレイヤーの速度を更新する
                playerVelocity = addedVelocity;
                
                if (playerVelocity.getLengthSq() > MAX_VELOCITY * (1.0f / currentScale)) {
                    Vec2 normalizedPlayerVelocity = playerVelocity.getNormalized();
                    playerVelocity = sqrt(MAX_VELOCITY * (1.0f / currentScale)) * normalizedPlayerVelocity;
                }
            }
        }
        
        if (currentState != LeukocyteState::ATTACKED &&
            currentState != LeukocyteState::DASH)
        {
            currentState = playerVelocity.length() > 0.0f ? LeukocyteState::MOVE : LeukocyteState::STOP;
        }
        
        // 壁際反射判定
        Vec2 updatedPos   = playerPos + playerVelocity;
        auto playerSprite = this->getChildByName<Sprite*>("player");
        Size playerSize   = Size(currentScale * playerSprite->getContentSize().width, currentScale * playerSprite->getContentSize().height);
        
        Size visibleSize = Director::getInstance()->getVisibleSize();
        if (updatedPos.x - playerSize.width / 2 < 0 || updatedPos.x + playerSize.width / 2 > visibleSize.width) {
            SimpleAudioEngine::getInstance()->playEffect(SE_HIT_WALL);
            
            playerVelocity.x *= -1.0f;
            if (currentState == LeukocyteState::DASH) {
                playerVelocity = sqrt(MAX_VELOCITY * (1.0f / currentScale)) * playerVelocity.getNormalized();
                currentState = LeukocyteState::MOVE;
            }
        }
        if (updatedPos.y - playerSize.height / 2 < 0 || updatedPos.y + playerSize.height / 2 > visibleSize.height) {
            SimpleAudioEngine::getInstance()->playEffect(SE_HIT_WALL);
            
            playerVelocity.y *= -1.0f;
            if (currentState == LeukocyteState::DASH) {
                playerVelocity = sqrt(MAX_VELOCITY * (1.0f / currentScale)) * playerVelocity.getNormalized();
                currentState = LeukocyteState::MOVE;
            }
        }
        
        // 他プレイヤー衝突判定
        if (other) {
            if (other->isCollideByOtherLeukocyte(updatedPos, this->getCollideRadius())) {
                // 半径和からプレイヤー間距離を引いた値が補正値
                float sumRadius = this->getCollideRadius() + other->getCollideRadius();
                float distance  = updatedPos.distance(other->getPosition());
                Vec2 adjustVec  = (sumRadius - distance) * (other->getPosition() - updatedPos).getNormalized();
                
                if (playerVelocity.getLength() > other->getPlayerVelocity().getLength()) {
                    this->setPosition(updatedPos - adjustVec);
                }
            }
            else {
                this->setPosition(playerPos + playerVelocity);
            }
        }
        else {
            // プレイヤー座標を更新する
            this->setPosition(playerPos + playerVelocity);
        }
        
        // 目標地点との距離がしきい値以下なら到着
        if (currentState != LeukocyteState::ATTACKED && !isCPU) {
            updatedPos = this->getPosition();
            float updated_distance = updatedPos.distance(playerLastTouchPos);
            
            if (updated_distance <= REACHED_DISTANCE) {
                this->setPosition(playerLastTouchPos);
                playerVelocity   = Vec2::ZERO;
                playerAccelerate = Vec2::ZERO;
                
                if (currentState == LeukocyteState::MOVE) {
                    currentState = LeukocyteState::LOCK;
                    dashGauge = 0;

                    float duration = Director::getInstance()->getAnimationInterval() * PLAYER_MOVING_LOCK_FRAME;
                    Blink* blink = Blink::create(duration, 3);
                    this->runAction(blink);
                }
            }
        }
        
        playerPrevFrameTouchPos = playerLastTouchPos;
        
        dashProgress->setPercentage(float(dashGauge) / PLAYER_DASH_CHARGE_MAX * 100.0f);
    }
    
    // 成長に合わせて壁に埋まる場合があるので補正
    Vec2 currentPosition = this->getPosition();
    Vec2 newPosition = Utility::getAdjustedPositionFromWall(currentPosition, this->getLeukocyteSize());
    if (currentPosition != newPosition) {
        this->setPosition(newPosition);
    }
    
    // decrease chain frame
    if (this->chainLeftFrame > 0 && !this->isLockChainLeftFrame) {
        this->chainLeftFrame--;
        if (this->chainLeftFrame <= 0) {
            this->chainCount = 0;
            this->sendData(JSONPacker::ActionType::TOUCH);
        }
    }
    
    // CPU logic
    if (this->isCPU) {
        this->updateForCPU();
    }
}