void Joystick::setHandlePosition(const cocos2d::Vec2& position)
{
    //将摇杆限制在底盘的范围内
    Vec2 point = this->convertToNodeSpaceAR(position);

    if(point.x*point.x+point.y*point.y > _bgRadius*_bgRadius)
    {
        point.normalize();
        point = point * _bgRadius;
    }

    _handle->setPosition(point);
}