void    MyBulletInterface::_update( float in_dt )
{
    unsigned int  state   = stateMachine_.getState();
    
    MyBulletObj*    pObj    = (MyBulletObj*)getChildByTag( eTAG_CHILD_NODE_OBJ );
    CCAssert( pObj, "" );

    CCPoint chainPos    = CCPointZero;
    if ( pAttachChainNode_ ) {
        chainPos    = pAttachChainNode_->getPosition();
    }

    if ( state == eSTATE_ATK ) {
        
        //  攻撃ステート、連結座標から一定離れた連結座標に戻るようにする。
        unsigned int    subState    = stateMachine_.getChildState(0);

        {
            //  attackメソッドで作成した移動方向に移動
            if( moveVec_.equals(CCPointZero) == false ) {
                CCPoint pos = pObj->getPosition();
                
                if ( subState == 0 ) {
                    //  加速度計算で動きをつける。
                    atkMoveTime_    += in_dt;
                    pos = pos + ( moveVec_ * (moveAccale_ * atkMoveTime_) );
                    
                    CCPoint lengthMove  = pos - chainPos;

                    bool    bAtkEnd = false;
                    //  鎖の位置から特定距離までしか移動できない。
                    if ( bAtkEnd == false ) {
                        if ( chainLength_ <= lengthMove.getLength() ) {
                            pos = chainPos + lengthMove.normalize() * chainLength_;
                            //  停止する
                            stateMachine_.setChildState( 0, 1 );
                        }
                        
                        pObj->setPosition( pos );
                    }
                }
                else if ( subState == 1 ) {
                    stopTimeAtkMove_   -= in_dt;
                    if ( stopTimeAtkMove_ <= 0 ) {
                        //  中心座標に戻るようにする。
                        stateMachine_.setState( eSTATE_COME_BACK );
                    }
                }
            }
            else {
                CCAssert( 0, "MyBullet is atk miss" );
            }
        }
    }
    else if ( state == eSTATE_ATK_ROT ) {
        //  回転移動攻撃
        atkRotAngle_ += atkRotSpeed_;
        
        bool        bEnd    = false;
        
        int childNowState   = stateMachine_.getChildState( 0 );
        if ( childNowState == 0 ) {
            atkRotRadius_ += atkRotAddRadius_;
            
            if( chainLength_ <= atkRotRadius_ ) {
                atkRotRadius_   = chainLength_;
                
                stateMachine_.setChildState( 0 , 1 );
            }
        }
        else if ( childNowState == 1 ) {

            atkRotRadius_ -= atkRotAddRadius_;
            if ( ( atkRotAddRadius_ <= 0.f ) && ( atkRotRadius_ <= 10 ) ) {
                atkRotRadius_   = 10;
                bEnd    = true;
            }
        }

        CCPoint pos = CCPoint::forAngle( atkRotAngle_ ) * atkRotRadius_;
        pObj->setPosition( pos + chainPos );

        //  指定した半径か時間になったら終了
        if( bEnd ) {
            stateMachine_.setState( eSTATE_COME_BACK );
        }
    }
    else if ( state == eSTATE_DEF ) {
        pObj->setPosition( chainPos );
    }
    else if ( state == eSTATE_HOLD ) {
    }
    else if ( state == eSTATE_COME_BACK ) {
        CCPoint pos = pObj->getPosition();

        //  連結座標は変更される可能性があるので、常に移動方向を計算
        moveVec_    = chainPos - pos;
        if ( moveVec_.getLength() <= 10 ) {
            //  連結座標から一定の距離に到達したら防御ステートに変更
            def();
        }
        else {
            pos = pos + (moveVec_.normalize() * moveSpeed_);
            pObj->setPosition( pos );
        }
    }
}