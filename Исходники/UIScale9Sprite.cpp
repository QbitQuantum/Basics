 void Scale9Sprite::createSlicedSprites()
 {
     float w = _originalSize.width;
     float h = _originalSize.height;
     
     Vec2 offsetPosition(ceil(_offset.x + (_originalSize.width - _spriteRect.size.width) / 2), ceil(_offset.y + (_originalSize.height - _spriteRect.size.height) / 2));
     
     // If there is no specified center region
     if ( _capInsetsInternal.equals(Rect::ZERO) )
     {
         // log("... cap insets not specified : using default cap insets ...");
         _capInsetsInternal = Rect(w/3, h/3, w/3, h/3);
     }
     
     Rect originalRect;
     if(_spriteFrameRotated)
         originalRect = Rect(_spriteRect.origin.x - offsetPosition.y, _spriteRect.origin.y - offsetPosition.x, _originalSize.width, _originalSize.height);
     else
         originalRect = Rect(_spriteRect.origin.x - offsetPosition.x, _spriteRect.origin.y - offsetPosition.y, _originalSize.width, _originalSize.height);
     
     float left_w = _capInsetsInternal.origin.x;
     float center_w = _capInsetsInternal.size.width;
     float right_w = originalRect.size.width - (left_w + center_w);
     
     float top_h = _capInsetsInternal.origin.y;
     float center_h = _capInsetsInternal.size.height;
     float bottom_h = originalRect.size.height - (top_h + center_h);
     
     // calculate rects
     
     // ... top row
     float x = 0.0;
     float y = 0.0;
     
     Rect pixelRect = Rect(offsetPosition.x, offsetPosition.y, _spriteRect.size.width, _spriteRect.size.height);
     
     // top left
     Rect lefttopboundsorig = Rect(x, y, left_w, top_h);
     Rect lefttopbounds = lefttopboundsorig;
     
     // top center
     TRANSLATE_X(x, y, left_w);
     Rect centertopbounds = Rect(x, y, center_w, top_h);
     
     // top right
     TRANSLATE_X(x, y, center_w);
     Rect righttopbounds = Rect(x, y, right_w, top_h);
     
     // ... center row
     x = 0.0;
     y = 0.0;
     TRANSLATE_Y(x, y, top_h);
     
     // center left
     Rect leftcenterbounds = Rect(x, y, left_w, center_h);
     
     // center center
     TRANSLATE_X(x, y, left_w);
     Rect centerboundsorig = Rect(x, y, center_w, center_h);
     Rect centerbounds = centerboundsorig;
     
     // center right
     TRANSLATE_X(x, y, center_w);
     Rect rightcenterbounds = Rect(x, y, right_w, center_h);
     
     // ... bottom row
     x = 0.0;
     y = 0.0;
     TRANSLATE_Y(x, y, top_h);
     TRANSLATE_Y(x, y, center_h);
     
     // bottom left
     Rect leftbottombounds = Rect(x, y, left_w, bottom_h);
     
     // bottom center
     TRANSLATE_X(x, y, left_w);
     Rect centerbottombounds = Rect(x, y, center_w, bottom_h);
     
     // bottom right
     TRANSLATE_X(x, y, center_w);
     Rect rightbottomboundsorig = Rect(x, y, right_w, bottom_h);
     Rect rightbottombounds = rightbottomboundsorig;
     
     if((_capInsetsInternal.origin.x + _capInsetsInternal.size.width) <= _originalSize.width
        || (_capInsetsInternal.origin.y + _capInsetsInternal.size.height) <= _originalSize.height)
     //in general case it is error but for legacy support we will check it
     {
         lefttopbounds = intersectRect(lefttopbounds, pixelRect);
         centertopbounds = intersectRect(centertopbounds, pixelRect);
         righttopbounds = intersectRect(righttopbounds, pixelRect);
         leftcenterbounds = intersectRect(leftcenterbounds, pixelRect);
         centerbounds = intersectRect(centerbounds, pixelRect);
         rightcenterbounds = intersectRect(rightcenterbounds, pixelRect);
         leftbottombounds = intersectRect(leftbottombounds, pixelRect);
         centerbottombounds = intersectRect(centerbottombounds, pixelRect);
         rightbottombounds = intersectRect(rightbottombounds, pixelRect);
     }
     else
         //it is error but for legacy turn off clip system
         CCLOG("Scale9Sprite capInsetsInternal > originalSize");
     
     Rect rotatedlefttopboundsorig = lefttopboundsorig;
     Rect rotatedcenterboundsorig = centerboundsorig;
     Rect rotatedrightbottomboundsorig = rightbottomboundsorig;
     
     Rect rotatedcenterbounds = centerbounds;
     Rect rotatedrightbottombounds = rightbottombounds;
     Rect rotatedleftbottombounds = leftbottombounds;
     Rect rotatedrighttopbounds = righttopbounds;
     Rect rotatedlefttopbounds = lefttopbounds;
     Rect rotatedrightcenterbounds = rightcenterbounds;
     Rect rotatedleftcenterbounds = leftcenterbounds;
     Rect rotatedcenterbottombounds = centerbottombounds;
     Rect rotatedcentertopbounds = centertopbounds;
     
     if (!_spriteFrameRotated)
     {
         
         AffineTransform t = AffineTransform::IDENTITY;
         t = AffineTransformTranslate(t, originalRect.origin.x, originalRect.origin.y);
         
         rotatedlefttopboundsorig = RectApplyAffineTransform(rotatedlefttopboundsorig, t);
         rotatedcenterboundsorig = RectApplyAffineTransform(rotatedcenterboundsorig, t);
         rotatedrightbottomboundsorig = RectApplyAffineTransform(rotatedrightbottomboundsorig, t);
         
         rotatedcenterbounds = RectApplyAffineTransform(rotatedcenterbounds, t);
         rotatedrightbottombounds = RectApplyAffineTransform(rotatedrightbottombounds, t);
         rotatedleftbottombounds = RectApplyAffineTransform(rotatedleftbottombounds, t);
         rotatedrighttopbounds = RectApplyAffineTransform(rotatedrighttopbounds, t);
         rotatedlefttopbounds = RectApplyAffineTransform(rotatedlefttopbounds, t);
         rotatedrightcenterbounds = RectApplyAffineTransform(rotatedrightcenterbounds, t);
         rotatedleftcenterbounds = RectApplyAffineTransform(rotatedleftcenterbounds, t);
         rotatedcenterbottombounds = RectApplyAffineTransform(rotatedcenterbottombounds, t);
         rotatedcentertopbounds = RectApplyAffineTransform(rotatedcentertopbounds, t);
         
         
     } else {
         // set up transformation of coordinates
         // to handle the case where the sprite is stored rotated
         // in the spritesheet
         // log("rotated");
         
         AffineTransform t = AffineTransform::IDENTITY;
         
         t = AffineTransformTranslate(t, originalRect.size.height+originalRect.origin.x, originalRect.origin.y);
         t = AffineTransformRotate(t, 1.57079633f);
         
         lefttopboundsorig = RectApplyAffineTransform(lefttopboundsorig, t);
         centerboundsorig = RectApplyAffineTransform(centerboundsorig, t);
         rightbottomboundsorig = RectApplyAffineTransform(rightbottomboundsorig, t);
         
         centerbounds = RectApplyAffineTransform(centerbounds, t);
         rightbottombounds = RectApplyAffineTransform(rightbottombounds, t);
         leftbottombounds = RectApplyAffineTransform(leftbottombounds, t);
         righttopbounds = RectApplyAffineTransform(righttopbounds, t);
         lefttopbounds = RectApplyAffineTransform(lefttopbounds, t);
         rightcenterbounds = RectApplyAffineTransform(rightcenterbounds, t);
         leftcenterbounds = RectApplyAffineTransform(leftcenterbounds, t);
         centerbottombounds = RectApplyAffineTransform(centerbottombounds, t);
         centertopbounds = RectApplyAffineTransform(centertopbounds, t);
         
         rotatedlefttopboundsorig.origin = lefttopboundsorig.origin;
         rotatedcenterboundsorig.origin = centerboundsorig.origin;
         rotatedrightbottomboundsorig.origin = rightbottomboundsorig.origin;
         
         rotatedcenterbounds.origin = centerbounds.origin;
         rotatedrightbottombounds.origin = rightbottombounds.origin;
         rotatedleftbottombounds.origin = leftbottombounds.origin;
         rotatedrighttopbounds.origin = righttopbounds.origin;
         rotatedlefttopbounds.origin = lefttopbounds.origin;
         rotatedrightcenterbounds.origin = rightcenterbounds.origin;
         rotatedleftcenterbounds.origin = leftcenterbounds.origin;
         rotatedcenterbottombounds.origin = centerbottombounds.origin;
         rotatedcentertopbounds.origin = centertopbounds.origin;
         
         
     }
     
     _topLeftSize = rotatedlefttopboundsorig.size;
     _centerSize = rotatedcenterboundsorig.size;
     _bottomRightSize = rotatedrightbottomboundsorig.size;
     
     if(_spriteFrameRotated)
     {
         float offsetx = (rotatedcenterbounds.origin.x + rotatedcenterbounds.size.height/2) - (rotatedcenterboundsorig.origin.x + rotatedcenterboundsorig.size.height/2);
         float offsety = (rotatedcenterboundsorig.origin.y + rotatedcenterboundsorig.size.width/2)- (rotatedcenterbounds.origin.y + rotatedcenterbounds.size.width/2);
         _centerOffset.x = -offsety;
         _centerOffset.y = offsetx;
     }
     else
     {
         float offsetx = (rotatedcenterbounds.origin.x + rotatedcenterbounds.size.width/2) - (rotatedcenterboundsorig.origin.x + rotatedcenterboundsorig.size.width/2);
         float offsety = (rotatedcenterboundsorig.origin.y + rotatedcenterboundsorig.size.height/2)- (rotatedcenterbounds.origin.y + rotatedcenterbounds.size.height/2);
         _centerOffset.x = offsetx;
         _centerOffset.y = offsety;
     }
     
     // Centre
     if(rotatedcenterbounds.size.width > 0 && rotatedcenterbounds.size.height > 0 )
     {
         _centre = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedcenterbounds, _spriteFrameRotated);
         _centre->retain();
         this->addProtectedChild(_centre);
     }
     
     // Top
     if(rotatedcentertopbounds.size.width > 0 && rotatedcentertopbounds.size.height > 0 )
     {
         _top = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedcentertopbounds, _spriteFrameRotated);
         _top->retain();
         this->addProtectedChild(_top);
     }
     
     // Bottom
     if(rotatedcenterbottombounds.size.width > 0 && rotatedcenterbottombounds.size.height > 0 )
     {
         _bottom = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedcenterbottombounds, _spriteFrameRotated);
         _bottom->retain();
         this->addProtectedChild(_bottom);
     }
     
     // Left
     if(rotatedleftcenterbounds.size.width > 0 && rotatedleftcenterbounds.size.height > 0 )
     {
         _left = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedleftcenterbounds, _spriteFrameRotated);
         _left->retain();
         this->addProtectedChild(_left);
     }
     
     // Right
     if(rotatedrightcenterbounds.size.width > 0 && rotatedrightcenterbounds.size.height > 0 )
     {
         _right = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedrightcenterbounds, _spriteFrameRotated);
         _right->retain();
         this->addProtectedChild(_right);
     }
     
     // Top left
     if(rotatedlefttopbounds.size.width > 0 && rotatedlefttopbounds.size.height > 0 )
     {
         _topLeft = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedlefttopbounds, _spriteFrameRotated);
         _topLeft->retain();
         this->addProtectedChild(_topLeft);
     }
     
     // Top right
     if(rotatedrighttopbounds.size.width > 0 && rotatedrighttopbounds.size.height > 0 )
     {
         _topRight = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedrighttopbounds, _spriteFrameRotated);
         _topRight->retain();
         this->addProtectedChild(_topRight);
     }
     
     // Bottom left
     if(rotatedleftbottombounds.size.width > 0 && rotatedleftbottombounds.size.height > 0 )
     {
         _bottomLeft = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedleftbottombounds, _spriteFrameRotated);
         _bottomLeft->retain();
         this->addProtectedChild(_bottomLeft);
     }
     
     // Bottom right
     if(rotatedrightbottombounds.size.width > 0 && rotatedrightbottombounds.size.height > 0 )
     {
         _bottomRight = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedrightbottombounds, _spriteFrameRotated);
         _bottomRight->retain();
         this->addProtectedChild(_bottomRight);
     }
 }