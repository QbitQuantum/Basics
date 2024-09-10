void BWJumpBy::update(float t)
{
    // parabolic jump (since v0.8.2)
    if (m_pTarget)
    {
        float frac = fmodf( t * m_nJumps, 1.0f );
        float y = m_height * 4 * frac * (1 - frac);
        
       // float fA = m_height * 4 ;
       // float y =   - frac*frac * fA + fA * frac + 5;
        

        y += m_delta.y * t;
        float x = m_delta.x * t;
#if CC_ENABLE_STACKABLE_ACTIONS
        CCPoint currentPos = m_pTarget->getPosition();

        CCPoint diff = ccpSub( currentPos, m_previousPos );
        m_startPosition = ccpAdd( diff, m_startPosition);

        CCPoint newPos = ccpAdd( m_startPosition, ccp(x,y));
        m_pTarget->setPosition(newPos);
        m_previousPos = newPos;
        
        if(m_bRotHead)
        {
            CCPoint dirPoint = ccpSub( currentPos,newPos );
            float fRadian = atanf(dirPoint.y/dirPoint.x);
            if((dirPoint.y > 0 && dirPoint.x > 0)
               || (dirPoint.y < 0 && dirPoint.x > 0))
            {
                fRadian = M_PI_2 - fRadian;
            }
            else if((dirPoint.y < 0 && dirPoint.x < 0)||
                    (dirPoint.y > 0 && dirPoint.x < 0))
            {
                fRadian = -M_PI_2 - fRadian;
            }
            float m_fRotation = fRadian*180.0/M_PI;
            m_pTarget->setRotation(m_fRotation);
        }
       
#else
        m_pTarget->setPosition(ccpAdd( m_startPosition, ccp(x,y)));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
    }
}