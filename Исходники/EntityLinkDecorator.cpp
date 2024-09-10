        // helper function
        void EntityLinkDecorator::addArrowVerts(Vec4f::List &vList, const Vec3f &pointA, const Vec3f &pointB) {
            if ((pointB - pointA).lengthSquared() < 0.0001f)
                return;

            vList.push_back(Vec4f(pointA, 0.0f));
            vList.push_back(Vec4f(pointB, 1.0f));

#if 0
            // calculate arrowhead
            const Vec3f
                lineVec = pointB - pointA,
                lineDir = lineVec.normalized();
            Vec3f
                lineRight;

            if( fabs( lineDir.dot( Vec3f::PosY )) < 0.9f ) {
                lineRight = -lineDir.crossed( Vec3f::PosY );
            } else {
                lineRight = -lineDir.crossed( Vec3f::PosZ );
            }

            lineRight.normalize();

            const Vec3f
                lineUp = lineDir.crossed( lineRight );

            const Vec3f
                arrowBase		= pointB - lineDir * 16.0f,
                arrowCorner1	= arrowBase + lineUp * 4.0,
                arrowCorner2	= arrowBase + lineRight * 4.0,
                arrowCorner3	= arrowBase - lineUp * 4.0,
                arrowCorner4	= arrowBase - lineRight * 4.0;

            float
                lineLength = lineVec.length(),
                arrowCornerDist = ( lineLength - 16.0f ) / lineLength;

            vList.push_back( Vec4f( pointB, 1.0f ) );
            vList.push_back( Vec4f( arrowCorner1, arrowCornerDist ));
            vList.push_back( Vec4f( pointB, 1.0f ) );
            vList.push_back( Vec4f( arrowCorner2, arrowCornerDist ));
            vList.push_back( Vec4f( pointB, 1.0f ) );
            vList.push_back( Vec4f( arrowCorner3, arrowCornerDist ));
            vList.push_back( Vec4f( pointB, 1.0f ) );
            vList.push_back( Vec4f( arrowCorner4, arrowCornerDist ));

            vList.push_back( Vec4f( arrowCorner1, arrowCornerDist ));
            vList.push_back( Vec4f( arrowCorner2, arrowCornerDist ));
            vList.push_back( Vec4f( arrowCorner2, arrowCornerDist ));
            vList.push_back( Vec4f( arrowCorner3, arrowCornerDist ));
            vList.push_back( Vec4f( arrowCorner3, arrowCornerDist ));
            vList.push_back( Vec4f( arrowCorner4, arrowCornerDist ));
            vList.push_back( Vec4f( arrowCorner4, arrowCornerDist ));
            vList.push_back( Vec4f( arrowCorner1, arrowCornerDist ));
#endif
        }