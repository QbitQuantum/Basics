void GamePointObject::checkCollisionsAgainstObjects( const Vector3& start, const Vector3& delta, const Vector<GameObjectDistance>& objects, CollisionInfo* cinfo )
{
	if ( m_collideFlags & CollisionInfo::COLLIDE_OBJECT )
	{
		for ( int i = 0 ; i < objects.size() ; ++i )
		{
			GameObject* obj = objects[i].object;
			if ( obj == m_objectToIgnore )
				continue;

			GameCharacter* character = dynamic_cast<GameCharacter*>( obj );
			if ( character )
			{
				if ( character->rootCollisionBox().findLineBoxIntersection(start,delta,0) )
				{
					for ( int k = 0 ; k < character->boneCollisionBoxes() ; ++k )
					{
						const BoneCollisionBox& box = character->getBoneCollisionBox(k);

						float t;
						if ( box.findLineBoxIntersection(start,delta,&t) )
						{
							Vector3 end = start + delta*t;
							Vector3 cpoint = end;
							*cinfo = CollisionInfo( end, obj->cell(), obj->cell(), 0, obj->forward(), cpoint, obj, 0 );
							return;
						}
					}
				}
				continue;
			}

			GameDynamicObject* dynamicObject = dynamic_cast<GameDynamicObject*>( obj );
			if ( dynamicObject )
			{
				if ( !dynamicObject->hidden() && 
					Intersection::findLineSphereIntersection(start, delta, dynamicObject->position(), dynamicObject->boundSphere(), 0) )
				{
					Matrix4x4 tm = dynamicObject->transform();
					Matrix4x4 invtm = tm.inverse();
					Vector3 bspStart = invtm.transform( start );
					Vector3 bspDelta = invtm.rotate( delta );

					float t = 1.f;
					const BSPPolygon* cpoly = 0;
					GameBSPTree* bsptree = dynamicObject->bspTree();
					BSPCollisionUtil::findLineIntersection( bsptree->root(), bspStart, bspDelta, CollisionInfo::COLLIDE_GEOMETRY_SOLID, &t, &cpoly );

					if ( t < 1.f )
					{
						Vector3 end = start + delta * t;
						Vector4 pl = cpoly->plane();
						Vector3 cnormal = tm.rotate( Vector3(pl.x,pl.y,pl.z) );
						*cinfo = CollisionInfo( end, dynamicObject->cell(), dynamicObject->cell(), cpoly, cnormal, end, dynamicObject, bsptree );
					}
				}
				continue;
			}
		}
	}
}