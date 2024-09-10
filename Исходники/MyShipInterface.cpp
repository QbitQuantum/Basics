/*
    @brief  設定した座標に向かって移動
 */
void    MyShipInterface::movePosition( const CCPoint& in_rPos )
{
    MyShipObj*  pObj    = (MyShipObj*)getChildByTag( eTAG_CHILD_OBJ );
    
    CCPoint pos = pObj->getPosition();
    CCPoint vec = in_rPos - pos;
    
    moveDirection( vec.normalize() );
}