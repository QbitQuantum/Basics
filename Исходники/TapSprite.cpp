void TapSprite::changeSoldier(int x, int y){
    
    int i;
    if(x){
        i = abs(x);
    }else{
        i = abs(y);
    }
    
    int absx = 0;
    if(x > 0){
        absx = 1;
    }else if (x < 0){
        absx = -1;
    }
    int absy = 0;
    if(y > 0){
        absy = 1;
    }else if (y < 0){
        absy = -1;
    }
    
    int destx = thisx;
    int desty = thisy;
    
    for(int j = 0;j < i;j++){
        if(x > 0){
            destx++;
        }else if(x < 0){
            destx--;
        }
        if(y > 0){
            desty++;
        }else if(y < 0){
            desty--;
        }
        
        CCSize size = this->getTexture()->getContentSize();
        CCSprite* dest = status->getSprite(destx,desty);
        
        CCNode* parent;
        CCSprite* sprite;
        
        parent = dest->getParent();
        parent->removeChild(dest);
        parent->addChild(dest);
        
        sprite = status->getSprite(thisx,thisy);
        parent = sprite->getParent();
        parent->removeChild(sprite);
        parent->addChild(sprite);
        
        CCPointArray* pAry = CCPointArray::create(3);
        pAry->addControlPoint(ccp(0,0));
        dest->stopAllActions();
        dest->setPosition(ccp((size.width * (destx)) + size.width/2 + 5, (size.height * (desty)) + size.height/2));
        if(x && y){
            pAry->addControlPoint(ccp(size.width * (-absx) * 0.75f, size.height * (-absy) * 0.25f ));
        }
        else if(x){
            pAry->addControlPoint(ccp(size.width * 0.5f * (-absx), -size.height * 0.5f ));
        }
        else if(y){
            pAry->addControlPoint(ccp(size.width * 0.5f,size.height * 0.5f *  (-absy)));
        }
        pAry->addControlPoint(ccp(size.width * (-absx),size.height *  (-absy)));
        dest->runAction(CCCardinalSplineBy::create(0.125f, pAry,1.0f));
        
        ((TapSprite*)dest)->setPlace(thisx,thisy);
        
        int tempStatus = status->getSoldier(destx, desty);
        status->setSoldier(status->getSoldier(thisx, thisy),destx, desty);
        status->setSoldier(tempStatus,thisx,thisy);
        
        status->setSprite(status->getSprite(thisx, thisy),destx, desty);
        status->setSprite(dest,thisx,thisy);
        
        thisx = destx;
        thisy = desty;
        
    }
}