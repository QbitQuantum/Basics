void Lens3D::update(float time)
{
    CC_UNUSED_PARAM(time);
    if (_dirty)
    {
        int i, j;
        
        for (i = 0; i < _gridSize.width + 1; ++i)
        {
            for (j = 0; j < _gridSize.height + 1; ++j)
            {
                Vec3 v = getOriginalVertex(Vec2(i, j));
                Vec2 vect = _position - Vec2(v.x, v.y);
                float r = vect.getLength();
                
                if (r < _radius)
                {
                    r = _radius - r;
                    float pre_log = r / _radius;
                    if ( pre_log == 0 ) 
                    {
                        pre_log = 0.001f;
                    }

                    float l = logf(pre_log) * _lensEffect;
                    float new_r = expf( l ) * _radius;
                    
                    if (vect.getLength() > 0)
                    {
                        vect.normalize();
                        Vec2 new_vect = vect * new_r;
                        v.z += (_concave ? -1.0f : 1.0f) * new_vect.getLength() * _lensEffect;
                    }
                }
                
                setVertex(Vec2(i, j), v);
            }
        }
        
        _dirty = false;
    }
}