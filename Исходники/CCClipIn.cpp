void CCClipIn::startWithTarget(CCNode *pTarget) {
    CCAssert(dynamic_cast<CCClippingNode*>(pTarget) != NULL, "CCClipIn target must be a CCClippingNode instance");
    
    CCActionInterval::startWithTarget(pTarget);
    
    // ensure the stencil of clipper is CCDrawNode
    CCClippingNode* clipper = (CCClippingNode*)pTarget;
    CCNode* stencil = clipper->getStencil();
    if(dynamic_cast<CCDrawNode*>(stencil) == NULL) {
        clipper->setStencil(CCDrawNode::create());
    }
    
    // direction radian
    float r = ccpToAngle(m_direction);
    m_cos = cosf(r);
    m_sin = sinf(r);
    
    // max distance along direction
    const CCSize& size = pTarget->getContentSize();
    m_distance = size.width * fabsf(m_cos) + size.height * fabsf(m_sin);
    
    // calculate fixed edge endpoints
    if(r > M_PI_2) {
        float p1Len = size.width * cosf(r - M_PI_2);
        m_p1.x = size.width - p1Len * cosf(r - M_PI_2);
        m_p1.y = -p1Len * sinf(r - M_PI_2);
        float p2Len = size.height * sinf(r - M_PI_2);
        m_p2.x = size.width + p2Len * cosf(r - M_PI_2);
        m_p2.y = p2Len * sinf(r - M_PI_2);
    } else if(r >= 0) {
        float p1Len = size.height * m_cos;
        m_p1.x = p1Len * cosf(r + M_PI_2);
        m_p1.y = p1Len * sinf(r + M_PI_2);
        float p2Len = size.width * m_sin;
        m_p2.x = p2Len * cosf(r - M_PI_2);
        m_p2.y = p2Len * sinf(r - M_PI_2);
    } else if(r < -M_PI_2) {
        float p1Len = size.height * sinf(-r - M_PI_2);
        m_p1.x = size.width + p1Len * cosf(-r - M_PI_2);
        m_p1.y = size.height - p1Len * sinf(-r - M_PI_2);
        float p2Len = size.width * cosf(-r - M_PI_2);
        m_p2.x = size.width - p2Len * cosf(-r - M_PI_2);
        m_p2.y = size.height + p2Len * sinf(-r - M_PI_2);
    } else {
        float p1Len = size.width * sinf(-r);
        m_p1.x = p1Len * cosf(r + M_PI_2);
        m_p1.y = size.height + p1Len * sinf(r + M_PI_2);
        float p2Len = size.height * cosf(-r);
        m_p2.x = -p2Len * cosf(r + M_PI_2);
        m_p2.y = size.height - p2Len * sinf(r + M_PI_2);
    }
}