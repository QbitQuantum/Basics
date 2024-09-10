btVector3 btConvexShape::localGetSupportVertexWithoutMarginNonVirtual (const btVector3& localDir) const
{
	switch (m_shapeType)
	{
    case SPHERE_SHAPE_PROXYTYPE:
	{
		return btVector3(0,0,0);
    }
	case BOX_SHAPE_PROXYTYPE:
	{
		btBoxShape* convexShape = (btBoxShape*)this;
		const btVector3& halfExtents = convexShape->getImplicitShapeDimensions();

#if defined( __APPLE__ ) && (defined( BT_USE_SSE )||defined( BT_USE_NEON ))
    #if defined( BT_USE_SSE )
            return btVector3( _mm_xor_ps( _mm_and_ps( localDir.mVec128, (__m128){-0.0f, -0.0f, -0.0f, -0.0f }), halfExtents.mVec128 ));
    #elif defined( BT_USE_NEON )
            return btVector3( (float32x4_t) (((uint32x4_t) localDir.mVec128 & (uint32x4_t){ 0x80000000, 0x80000000, 0x80000000, 0x80000000}) ^ (uint32x4_t) halfExtents.mVec128 ));
    #else
        #error unknown vector arch
    #endif
#else
		return btVector3(btFsels(localDir.x(), halfExtents.x(), -halfExtents.x()),
			btFsels(localDir.y(), halfExtents.y(), -halfExtents.y()),
			btFsels(localDir.z(), halfExtents.z(), -halfExtents.z()));
#endif
	}
	case TRIANGLE_SHAPE_PROXYTYPE:
	{
		btTriangleShape* triangleShape = (btTriangleShape*)this;
		btVector3 dir(localDir.getX(),localDir.getY(),localDir.getZ());
		btVector3* vertices = &triangleShape->m_vertices1[0];
        btVector3 dots = dir.dot3(vertices[0], vertices[1], vertices[2]);
		btVector3 sup = vertices[dots.maxAxis()];
		return btVector3(sup.getX(),sup.getY(),sup.getZ());
	}
	case CYLINDER_SHAPE_PROXYTYPE:
	{
		btCylinderShape* cylShape = (btCylinderShape*)this;
		//mapping of halfextents/dimension onto radius/height depends on how cylinder local orientation is (upAxis)

		btVector3 halfExtents = cylShape->getImplicitShapeDimensions();
		btVector3 v(localDir.getX(),localDir.getY(),localDir.getZ());
		int cylinderUpAxis = cylShape->getUpAxis();
		int XX(1),YY(0),ZZ(2);

		switch (cylinderUpAxis)
		{
		case 0:
		{
			XX = 1;
			YY = 0;
			ZZ = 2;
		}
		break;
		case 1:
		{
			XX = 0;
			YY = 1;
			ZZ = 2;	
		}
		break;
		case 2:
		{
			XX = 0;
			YY = 2;
			ZZ = 1;
			
		}
		break;
		default:
			btAssert(0);
		break;
		};

		btScalar radius = halfExtents[XX];
		btScalar halfHeight = halfExtents[cylinderUpAxis];

		btVector3 tmp;
		btScalar d ;

		btScalar s = btSqrt(v[XX] * v[XX] + v[ZZ] * v[ZZ]);
		if (s != btScalar(0.0))
		{
			d = radius / s;  
			tmp[XX] = v[XX] * d;
			tmp[YY] = v[YY] < 0.0 ? -halfHeight : halfHeight;
			tmp[ZZ] = v[ZZ] * d;
			return btVector3(tmp.getX(),tmp.getY(),tmp.getZ());
		} else {
			tmp[XX] = radius;
			tmp[YY] = v[YY] < 0.0 ? -halfHeight : halfHeight;
			tmp[ZZ] = btScalar(0.0);
			return btVector3(tmp.getX(),tmp.getY(),tmp.getZ());
		}
	}
	case CAPSULE_SHAPE_PROXYTYPE:
	{
		btVector3 vec0(localDir.getX(),localDir.getY(),localDir.getZ());

		btCapsuleShape* capsuleShape = (btCapsuleShape*)this;
		btScalar halfHeight = capsuleShape->getHalfHeight();
		int capsuleUpAxis = capsuleShape->getUpAxis();

		btScalar radius = capsuleShape->getRadius();
		btVector3 supVec(0,0,0);

		btScalar maxDot(btScalar(-BT_LARGE_FLOAT));

		btVector3 vec = vec0;
		btScalar lenSqr = vec.length2();
		if (lenSqr < btScalar(0.0001))
		{
			vec.setValue(1,0,0);
		} else
		{
			btScalar rlen = btScalar(1.) / btSqrt(lenSqr );
			vec *= rlen;
		}
		btVector3 vtx;
		btScalar newDot;
		{
			btVector3 pos(0,0,0);
			pos[capsuleUpAxis] = halfHeight;

			//vtx = pos +vec*(radius);
			vtx = pos +vec*(radius) - vec * capsuleShape->getMarginNV();
			newDot = vec.dot(vtx);
			

			if (newDot > maxDot)
			{
				maxDot = newDot;
				supVec = vtx;
			}
		}
		{
			btVector3 pos(0,0,0);
			pos[capsuleUpAxis] = -halfHeight;

			//vtx = pos +vec*(radius);
			vtx = pos +vec*(radius) - vec * capsuleShape->getMarginNV();
			newDot = vec.dot(vtx);
			if (newDot > maxDot)
			{
				maxDot = newDot;
				supVec = vtx;
			}
		}
		return btVector3(supVec.getX(),supVec.getY(),supVec.getZ());	
	}
	case CONVEX_POINT_CLOUD_SHAPE_PROXYTYPE:
	{
		btConvexPointCloudShape* convexPointCloudShape = (btConvexPointCloudShape*)this;
		btVector3* points = convexPointCloudShape->getUnscaledPoints ();
		int numPoints = convexPointCloudShape->getNumPoints ();
		return convexHullSupport (localDir, points, numPoints,convexPointCloudShape->getLocalScalingNV());
	}
	case CONVEX_HULL_SHAPE_PROXYTYPE:
	{
		btConvexHullShape* convexHullShape = (btConvexHullShape*)this;
		btVector3* points = convexHullShape->getUnscaledPoints();
		int numPoints = convexHullShape->getNumPoints ();
		return convexHullSupport (localDir, points, numPoints,convexHullShape->getLocalScalingNV());
	}
    default:
#ifndef __SPU__
		return this->localGetSupportingVertexWithoutMargin (localDir);
#else
		btAssert (0);
#endif
	}

	// should never reach here
	btAssert (0);
	return btVector3 (btScalar(0.0f), btScalar(0.0f), btScalar(0.0f));
}