//  ドラッグ発生時のコールバック
void    MyShipFacade::onDraggingStart(
                                CCPoint& in_rStartPos,
                                CCPoint& in_rTouchPos,
                                CCPoint& in_rDelta )
{
    MyBulletInterface* pBulletObj  = (MyBulletInterface*)getChildByTag(eTAG_OBJ_BULLET);

    if( pBulletObj->getState() == MyBulletInterface::eSTATE_HOLD ) {
        float   speed   = 10;
        pBulletObj->attack( in_rDelta.normalize(), speed );
        
        touchPos_   = CCPointZero;
    }
}