void Scale9Sprite::createSlicedSprites()
{
    float width = _originalSize.width;
    float height = _originalSize.height;
    
    Vec2 offsetPosition(ceilf(_offset.x + (_originalSize.width - _spriteRect.size.width) / 2),
                        ceilf(_offset.y + (_originalSize.height - _spriteRect.size.height) / 2));
    
    // If there is no specified center region
    if ( _capInsetsInternal.equals(Rect::ZERO) )
    {
        // log("... cap insets not specified : using default cap insets ...");
        _capInsetsInternal = Rect(width /3, height /3, width /3, height /3);
    }
    
    Rect originalRect=_spriteRect;
    if(_spriteFrameRotated)
        originalRect = Rect(_spriteRect.origin.x - offsetPosition.y,
                            _spriteRect.origin.y - offsetPosition.x,
                            _originalSize.width, _originalSize.height);
    else
        originalRect = Rect(_spriteRect.origin.x - offsetPosition.x,
                            _spriteRect.origin.y - offsetPosition.y,
                            _originalSize.width, _originalSize.height);
    
    float leftWidth = _capInsetsInternal.origin.x;
    float centerWidth = _capInsetsInternal.size.width;
    float rightWidth = originalRect.size.width - (leftWidth + centerWidth);
    
    float topHeight = _capInsetsInternal.origin.y;
    float centerHeight = _capInsetsInternal.size.height;
    float bottomHeight = originalRect.size.height - (topHeight + centerHeight);
    
    // calculate rects
    
    // ... top row
    float x = 0.0;
    float y = 0.0;
    //why do we need pixelRect?
    Rect pixelRect = Rect(offsetPosition.x, offsetPosition.y,
                          _spriteRect.size.width, _spriteRect.size.height);
    
    // top left
    Rect leftTopBoundsOriginal = Rect(x, y, leftWidth, topHeight);
    Rect leftTopBounds = leftTopBoundsOriginal;
    
    // top center
    x += leftWidth;
    Rect centerTopBounds = Rect(x, y, centerWidth, topHeight);
    
    // top right
    x += centerWidth;
    Rect rightTopBounds = Rect(x, y, rightWidth, topHeight);
    
    // ... center row
    x = 0.0;
    y = 0.0;
    y += topHeight;
    
    // center left
    Rect leftCenterBounds = Rect(x, y, leftWidth, centerHeight);
    
    // center center
    x += leftWidth;
    Rect centerBoundsOriginal = Rect(x, y, centerWidth, centerHeight);
    Rect centerBounds = centerBoundsOriginal;
    
    // center right
    x += centerWidth;
    Rect rightCenterBounds = Rect(x, y, rightWidth, centerHeight);
    
    // ... bottom row
    x = 0.0;
    y = 0.0;
    y += topHeight;
    y += centerHeight;
    
    // bottom left
    Rect leftBottomBounds = Rect(x, y, leftWidth, bottomHeight);
    
    // bottom center
    x += leftWidth;
    Rect centerBottomBounds = Rect(x, y, centerWidth, bottomHeight);
    
    // bottom right
    x += centerWidth;
    Rect rightBottomBoundsOriginal = Rect(x, y, rightWidth, bottomHeight);
    Rect rightBottomBounds = rightBottomBoundsOriginal;
    
    if((_capInsetsInternal.origin.x + _capInsetsInternal.size.width) <= _originalSize.width
       || (_capInsetsInternal.origin.y + _capInsetsInternal.size.height) <= _originalSize.height)
        //in general case it is error but for legacy support we will check it
    {
        leftTopBounds = intersectRect(leftTopBounds, pixelRect);
        centerTopBounds = intersectRect(centerTopBounds, pixelRect);
        rightTopBounds = intersectRect(rightTopBounds, pixelRect);
        leftCenterBounds = intersectRect(leftCenterBounds, pixelRect);
        centerBounds = intersectRect(centerBounds, pixelRect);
        rightCenterBounds = intersectRect(rightCenterBounds, pixelRect);
        leftBottomBounds = intersectRect(leftBottomBounds, pixelRect);
        centerBottomBounds = intersectRect(centerBottomBounds, pixelRect);
        rightBottomBounds = intersectRect(rightBottomBounds, pixelRect);
    }
    else
        //it is error but for legacy turn off clip system
        CCLOG("Scale9Sprite capInsetsInternal > originalSize");
    
    Rect rotatedLeftTopBoundsOriginal = leftTopBoundsOriginal;
    Rect rotatedCenterBoundsOriginal = centerBoundsOriginal;
    Rect rotatedRightBottomBoundsOriginal = rightBottomBoundsOriginal;
    
    Rect rotatedCenterBounds = centerBounds;
    Rect rotatedRightBottomBounds = rightBottomBounds;
    Rect rotatedLeftBottomBounds = leftBottomBounds;
    Rect rotatedRightTopBounds = rightTopBounds;
    Rect rotatedLeftTopBounds = leftTopBounds;
    Rect rotatedRightCenterBounds = rightCenterBounds;
    Rect rotatedLeftCenterBounds = leftCenterBounds;
    Rect rotatedCenterBottomBounds = centerBottomBounds;
    Rect rotatedCenterTopBounds = centerTopBounds;
    
    if (!_spriteFrameRotated)
    {
        
        AffineTransform t = AffineTransform::IDENTITY;
        t = AffineTransformTranslate(t, originalRect.origin.x, originalRect.origin.y);
        
        rotatedLeftTopBoundsOriginal = RectApplyAffineTransform(rotatedLeftTopBoundsOriginal, t);
        rotatedCenterBoundsOriginal = RectApplyAffineTransform(rotatedCenterBoundsOriginal, t);
        rotatedRightBottomBoundsOriginal = RectApplyAffineTransform(rotatedRightBottomBoundsOriginal, t);
        
        rotatedCenterBounds = RectApplyAffineTransform(rotatedCenterBounds, t);
        rotatedRightBottomBounds = RectApplyAffineTransform(rotatedRightBottomBounds, t);
        rotatedLeftBottomBounds = RectApplyAffineTransform(rotatedLeftBottomBounds, t);
        rotatedRightTopBounds = RectApplyAffineTransform(rotatedRightTopBounds, t);
        rotatedLeftTopBounds = RectApplyAffineTransform(rotatedLeftTopBounds, t);
        rotatedRightCenterBounds = RectApplyAffineTransform(rotatedRightCenterBounds, t);
        rotatedLeftCenterBounds = RectApplyAffineTransform(rotatedLeftCenterBounds, t);
        rotatedCenterBottomBounds = RectApplyAffineTransform(rotatedCenterBottomBounds, t);
        rotatedCenterTopBounds = RectApplyAffineTransform(rotatedCenterTopBounds, t);
        
        
    }
    else
    {
        // set up transformation of coordinates
        // to handle the case where the sprite is stored rotated
        // in the spritesheet
        // log("rotated");
        
        AffineTransform t = AffineTransform::IDENTITY;
        
        t = AffineTransformTranslate(t, originalRect.size.height+originalRect.origin.x, originalRect.origin.y);
        t = AffineTransformRotate(t, 1.57079633f);
        
        leftTopBoundsOriginal = RectApplyAffineTransform(leftTopBoundsOriginal, t);
        centerBoundsOriginal = RectApplyAffineTransform(centerBoundsOriginal, t);
        rightBottomBoundsOriginal = RectApplyAffineTransform(rightBottomBoundsOriginal, t);
        
        centerBounds = RectApplyAffineTransform(centerBounds, t);
        rightBottomBounds = RectApplyAffineTransform(rightBottomBounds, t);
        leftBottomBounds = RectApplyAffineTransform(leftBottomBounds, t);
        rightTopBounds = RectApplyAffineTransform(rightTopBounds, t);
        leftTopBounds = RectApplyAffineTransform(leftTopBounds, t);
        rightCenterBounds = RectApplyAffineTransform(rightCenterBounds, t);
        leftCenterBounds = RectApplyAffineTransform(leftCenterBounds, t);
        centerBottomBounds = RectApplyAffineTransform(centerBottomBounds, t);
        centerTopBounds = RectApplyAffineTransform(centerTopBounds, t);
        
        rotatedLeftTopBoundsOriginal.origin = leftTopBoundsOriginal.origin;
        rotatedCenterBoundsOriginal.origin = centerBoundsOriginal.origin;
        rotatedRightBottomBoundsOriginal.origin = rightBottomBoundsOriginal.origin;
        
        rotatedCenterBounds.origin = centerBounds.origin;
        rotatedRightBottomBounds.origin = rightBottomBounds.origin;
        rotatedLeftBottomBounds.origin = leftBottomBounds.origin;
        rotatedRightTopBounds.origin = rightTopBounds.origin;
        rotatedLeftTopBounds.origin = leftTopBounds.origin;
        rotatedRightCenterBounds.origin = rightCenterBounds.origin;
        rotatedLeftCenterBounds.origin = leftCenterBounds.origin;
        rotatedCenterBottomBounds.origin = centerBottomBounds.origin;
        rotatedCenterTopBounds.origin = centerTopBounds.origin;
        
        
    }
    
    _topLeftSize = rotatedLeftTopBoundsOriginal.size;
    _centerSize = rotatedCenterBoundsOriginal.size;
    _bottomRightSize = rotatedRightBottomBoundsOriginal.size;
    if(_isPatch9)
    {
        _topLeftSize.width = _topLeftSize.width - 1;
        _topLeftSize.height = _topLeftSize.height - 1;
        _bottomRightSize.width = _bottomRightSize.width - 1;
        _bottomRightSize.height = _bottomRightSize.height - 1;
    }
    
    if(_spriteFrameRotated)
    {
        float offsetX = (rotatedCenterBounds.origin.x + rotatedCenterBounds.size.height/2)
        - (rotatedCenterBoundsOriginal.origin.x + rotatedCenterBoundsOriginal.size.height/2);
        float offsetY = (rotatedCenterBoundsOriginal.origin.y + rotatedCenterBoundsOriginal.size.width/2)
        - (rotatedCenterBounds.origin.y + rotatedCenterBounds.size.width/2);
        _centerOffset.x = -offsetY;
        _centerOffset.y = offsetX;
    }
    else
    {
        float offsetX = (rotatedCenterBounds.origin.x + rotatedCenterBounds.size.width/2)
        - (rotatedCenterBoundsOriginal.origin.x + rotatedCenterBoundsOriginal.size.width/2);
        float offsetY = (rotatedCenterBoundsOriginal.origin.y + rotatedCenterBoundsOriginal.size.height/2)
        - (rotatedCenterBounds.origin.y + rotatedCenterBounds.size.height/2);
        _centerOffset.x = offsetX;
        _centerOffset.y = offsetY;
    }
    
    //shrink the image size when it is 9-patch
    if(_isPatch9)
    {
        float offset = 1.4f;
        //Top left
        if(!_spriteFrameRotated)
        {
            rotatedLeftTopBounds.origin.x+=offset;
            rotatedLeftTopBounds.origin.y+=offset;
            rotatedLeftTopBounds.size.width-=offset;
            rotatedLeftTopBounds.size.height-=offset;
            //Center left
            rotatedLeftCenterBounds.origin.x+=offset;
            rotatedLeftCenterBounds.size.width-=offset;
            //Bottom left
            rotatedLeftBottomBounds.origin.x+=offset;
            rotatedLeftBottomBounds.size.width-=offset;
            rotatedLeftBottomBounds.size.height-=offset;
            //Top center
            rotatedCenterTopBounds.size.height-=offset;
            rotatedCenterTopBounds.origin.y+=offset;
            //Bottom center
            rotatedCenterBottomBounds.size.height-=offset;
            //Top right
            rotatedRightTopBounds.size.width-=offset;
            rotatedRightTopBounds.size.height-=offset;
            rotatedRightTopBounds.origin.y+=offset;
            //Center right
            rotatedRightCenterBounds.size.width-=offset;
            //Bottom right
            rotatedRightBottomBounds.size.width-=offset;
            rotatedRightBottomBounds.size.height-=offset;
        }
        else
        {
            //Top left
            rotatedLeftTopBounds.size.width-=offset;
            rotatedLeftTopBounds.size.height-=offset;
            rotatedLeftTopBounds.origin.y+=offset;
            //Center left
            rotatedLeftCenterBounds.origin.y+=offset;
            rotatedLeftCenterBounds.size.width-=offset;
            //Bottom left
            rotatedLeftBottomBounds.origin.x+=offset;
            rotatedLeftBottomBounds.origin.y+=offset;
            rotatedLeftBottomBounds.size.width-=offset;
            rotatedLeftBottomBounds.size.height-=offset;
            //Top center
            rotatedCenterTopBounds.size.height-=offset;
            //Bottom center
            rotatedCenterBottomBounds.size.height-=offset;
            rotatedCenterBottomBounds.origin.x+=offset;
            //Top right
            rotatedRightTopBounds.size.width-=offset;
            rotatedRightTopBounds.size.height-=offset;
            //Center right
            rotatedRightCenterBounds.size.width-=offset;
            //Bottom right
            rotatedRightBottomBounds.size.width-=offset;
            rotatedRightBottomBounds.size.height-=offset;
            rotatedRightBottomBounds.origin.x+=offset;
        }
    }
    
    // Centre
    if(rotatedCenterBounds.size.width > 0 && rotatedCenterBounds.size.height > 0 )
    {
        _centerSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                  rotatedCenterBounds,
                                                  _spriteFrameRotated);
        _centerSprite->retain();
        this->addProtectedChild(_centerSprite);
    }
    
    // Top
    if(rotatedCenterTopBounds.size.width > 0 && rotatedCenterTopBounds.size.height > 0 )
    {
        _topSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                               rotatedCenterTopBounds,
                                               _spriteFrameRotated);
        _topSprite->retain();
        this->addProtectedChild(_topSprite);
    }
    
    // Bottom
    if(rotatedCenterBottomBounds.size.width > 0 && rotatedCenterBottomBounds.size.height > 0 )
    {
        _bottomSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                  rotatedCenterBottomBounds,
                                                  _spriteFrameRotated);
        _bottomSprite->retain();
        this->addProtectedChild(_bottomSprite);
    }
    
    // Left
    if(rotatedLeftCenterBounds.size.width > 0 && rotatedLeftCenterBounds.size.height > 0 )
    {
        _leftSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                rotatedLeftCenterBounds,
                                                _spriteFrameRotated);
        _leftSprite->retain();
        this->addProtectedChild(_leftSprite);
    }
    
    // Right
    if(rotatedRightCenterBounds.size.width > 0 && rotatedRightCenterBounds.size.height > 0 )
    {
        _rightSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                 rotatedRightCenterBounds,
                                                 _spriteFrameRotated);
        _rightSprite->retain();
        this->addProtectedChild(_rightSprite);
    }
    
    // Top left
    if(rotatedLeftTopBounds.size.width > 0 && rotatedLeftTopBounds.size.height > 0 )
    {
        _topLeftSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                   rotatedLeftTopBounds,
                                                   _spriteFrameRotated);
        _topLeftSprite->retain();
        this->addProtectedChild(_topLeftSprite);
    }
    
    // Top right
    if(rotatedRightTopBounds.size.width > 0 && rotatedRightTopBounds.size.height > 0 )
    {
        _topRightSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                    rotatedRightTopBounds,
                                                    _spriteFrameRotated);
        _topRightSprite->retain();
        this->addProtectedChild(_topRightSprite);
    }
    
    // Bottom left
    if(rotatedLeftBottomBounds.size.width > 0 && rotatedLeftBottomBounds.size.height > 0 )
    {
        _bottomLeftSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                      rotatedLeftBottomBounds,
                                                      _spriteFrameRotated);
        _bottomLeftSprite->retain();
        this->addProtectedChild(_bottomLeftSprite);
    }
    
    // Bottom right
    if(rotatedRightBottomBounds.size.width > 0 && rotatedRightBottomBounds.size.height > 0 )
    {
        _bottomRightSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                       rotatedRightBottomBounds,
                                                       _spriteFrameRotated);
        _bottomRightSprite->retain();
        this->addProtectedChild(_bottomRightSprite);
    }
}