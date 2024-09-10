/*
================
idBrittleFracture::DropShard
================
*/
void idBrittleFracture::DropShard( shard_t* shard, const idVec3& point, const idVec3& dir, const float impulse, const int time )
{
	int i, j, clipModelId;
	float dist, f;
	idVec3 dir2, origin;
	idMat3 axis;
	shard_t* neighbour;
	
	// don't display decals on dropped shards
	shard->decals.DeleteContents( true );
	
	// remove neighbour pointers of neighbours pointing to this shard
	for( i = 0; i < shard->neighbours.Num(); i++ )
	{
		neighbour = shard->neighbours[i];
		for( j = 0; j < neighbour->neighbours.Num(); j++ )
		{
			if( neighbour->neighbours[j] == shard )
			{
				neighbour->neighbours.RemoveIndex( j );
				break;
			}
		}
	}
	
	// remove neighbour pointers
	shard->neighbours.Clear();
	
	// remove the clip model from the static physics object
	clipModelId = shard->clipModel->GetId();
	physicsObj.SetClipModel( NULL, 1.0f, clipModelId, false );
	
	origin = shard->clipModel->GetOrigin();
	axis = shard->clipModel->GetAxis();
	
	// set the dropped time for fading
	shard->droppedTime = time;
	
	dir2 = origin - point;
	dist = dir2.Normalize();
	f = dist > maxShatterRadius ? 1.0f : idMath::Sqrt( idMath::Fabs( dist - minShatterRadius ) ) * ( 1.0f / idMath::Sqrt( idMath::Fabs( maxShatterRadius - minShatterRadius ) ) );
	
	// setup the physics
	shard->physicsObj.SetSelf( this );
	shard->physicsObj.SetClipModel( shard->clipModel, density );
	shard->physicsObj.SetMass( shardMass );
	shard->physicsObj.SetOrigin( origin );
	shard->physicsObj.SetAxis( axis );
	shard->physicsObj.SetBouncyness( bouncyness );
	shard->physicsObj.SetFriction( 0.6f, 0.6f, friction );
	shard->physicsObj.SetGravity( gameLocal.GetGravity() );
	shard->physicsObj.SetContents( CONTENTS_RENDERMODEL );
	shard->physicsObj.SetClipMask( MASK_SOLID | CONTENTS_MOVEABLECLIP );
	shard->physicsObj.ApplyImpulse( 0, origin, impulse * linearVelocityScale * dir );
	shard->physicsObj.SetAngularVelocity( dir.Cross( dir2 ) * ( f * angularVelocityScale ) );
	
	shard->clipModel->SetId( clipModelId );
	
	BecomeActive( TH_PHYSICS );
}