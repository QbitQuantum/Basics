const kmMat4& Node::getNodeToParentTransform() const
{
    if (_transformDirty)
    {
        // Translate values
        float x = _position.x;
        float y = _position.y;
        float z = _positionZ;

        if (_ignoreAnchorPointForPosition)
        {
            x += _anchorPointInPoints.x;
            y += _anchorPointInPoints.y;
        }

        // Rotation values
		// Change rotation code to handle X and Y
		// If we skew with the exact same value for both x and y then we're simply just rotating
        float cx = 1, sx = 0, cy = 1, sy = 0;
        if (_rotationZ_X || _rotationZ_Y)
        {
            float radiansX = -CC_DEGREES_TO_RADIANS(_rotationZ_X);
            float radiansY = -CC_DEGREES_TO_RADIANS(_rotationZ_Y);
            cx = cosf(radiansX);
            sx = sinf(radiansX);
            cy = cosf(radiansY);
            sy = sinf(radiansY);
        }

        bool needsSkewMatrix = ( _skewX || _skewY );


        // optimization:
        // inline anchor point calculation if skew is not needed
        // Adjusted transform calculation for rotational skew
        if (! needsSkewMatrix && !_anchorPointInPoints.equals(Point::ZERO))
        {
            x += cy * -_anchorPointInPoints.x * _scaleX + -sx * -_anchorPointInPoints.y * _scaleY;
            y += sy * -_anchorPointInPoints.x * _scaleX +  cx * -_anchorPointInPoints.y * _scaleY;
        }


        // Build Transform Matrix
        // Adjusted transform calculation for rotational skew
        kmScalar mat[] = {
                        cy * _scaleX,   sy * _scaleX,   0,          0,
                        -sx * _scaleY,  cx * _scaleY,   0,          0,
                        0,              0,              _scaleZ,    0,
                        x,              y,              z,          1 };
        
        kmMat4Fill(&_transform, mat);

        // XXX
        // FIX ME: Expensive operation.
        // FIX ME: It should be done together with the rotationZ
        if(_rotationY) {
            kmMat4 rotY;
            kmMat4RotationY(&rotY,CC_DEGREES_TO_RADIANS(_rotationY));
            kmMat4Multiply(&_transform, &_transform, &rotY);
        }
        if(_rotationX) {
            kmMat4 rotX;
            kmMat4RotationX(&rotX,CC_DEGREES_TO_RADIANS(_rotationX));
            kmMat4Multiply(&_transform, &_transform, &rotX);
        }

        // XXX: Try to inline skew
        // If skew is needed, apply skew and then anchor point
        if (needsSkewMatrix)
        {
            kmMat4 skewMatrix = { 1, (float)tanf(CC_DEGREES_TO_RADIANS(_skewY)), 0, 0,
                                  (float)tanf(CC_DEGREES_TO_RADIANS(_skewX)), 1, 0, 0,
                                  0,  0,  1, 0,
                                  0,  0,  0, 1};

            kmMat4Multiply(&_transform, &_transform, &skewMatrix);

            // adjust anchor point
            if (!_anchorPointInPoints.equals(Point::ZERO))
            {
                // XXX: Argh, kmMat needs a "translate" method.
                // XXX: Although this is faster than multiplying a vec4 * mat4
                _transform.mat[12] += _transform.mat[0] * -_anchorPointInPoints.x + _transform.mat[4] * -_anchorPointInPoints.y;
                _transform.mat[13] += _transform.mat[1] * -_anchorPointInPoints.x + _transform.mat[5] * -_anchorPointInPoints.y;
            }
        }

        if (_useAdditionalTransform)
        {
            kmMat4Multiply(&_transform, &_transform, &_additionalTransform);
        }

        _transformDirty = false;
    }

    return _transform;
}