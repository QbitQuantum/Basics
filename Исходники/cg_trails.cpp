/*
===============
CG_CalculateBeamNodeProperties

Fills in trailBeamNode_t.textureCoord
===============
*/
static void CG_CalculateBeamNodeProperties( trailBeam_t *tb )
{
	trailBeamNode_t *i = nullptr;
	trailSystem_t   *ts;
	baseTrailBeam_t *btb;
	float           nodeDistances[ MAX_TRAIL_BEAM_NODES ];
	float           totalDistance = 0.0f, position = 0.0f;
	int             j, numNodes = 0;
	float           TCRange, widthRange, alphaRange;
	vec3_t          colorRange;
	float           fadeAlpha = 1.0f;

	if ( !tb || !tb->nodes )
	{
		return;
	}

	ts = tb->parent;
	btb = tb->class_;

	if ( ts->destroyTime > 0 && btb->fadeOutTime )
	{
		fadeAlpha -= ( float )( cg.time - ts->destroyTime ) / btb->fadeOutTime;

		if ( fadeAlpha < 0.0f )
		{
			fadeAlpha = 0.0f;
		}
	}

	TCRange = tb->class_->backTextureCoord -
			          tb->class_->frontTextureCoord;
widthRange = tb->class_->backWidth -
			             tb->class_->frontWidth;
alphaRange = tb->class_->backAlpha -
			             tb->class_->frontAlpha;
	VectorSubtract( tb->class_->backColor,
	                tb->class_->frontColor, colorRange );

	for ( i = tb->nodes; i && i->next; i = i->next )
{
		nodeDistances[ numNodes++ ] =
		  Distance( i->position, i->next->position );
	}

	for ( j = 0; j < numNodes; j++ )
	{
		totalDistance += nodeDistances[ j ];
	}

	for ( j = 0, i = tb->nodes; i; i = i->next, j++ )
	{
		if ( tb->class_->textureType == TBTT_STRETCH )
		{
			i->textureCoord = tb->class_->frontTextureCoord +
					                  ( ( position / totalDistance ) * TCRange );
		}
		else if ( tb->class_->textureType == TBTT_REPEAT )
	{
			if ( tb->class_->clampToBack )
			{
				i->textureCoord = ( totalDistance - position ) /
				                  tb->class_->repeatLength;
			}
			else
			{
				i->textureCoord = position / tb->class_->repeatLength;
			}
		}

		i->halfWidth = ( tb->class_->frontWidth +
		                 ( ( position / totalDistance ) * widthRange ) ) / 2.0f;
		i->alpha = ( byte )( ( float ) 0xFF * ( tb->class_->frontAlpha +
		                                        ( ( position / totalDistance ) * alphaRange ) ) * fadeAlpha );
		VectorMA( tb->class_->frontColor, ( position / totalDistance ),
		          colorRange, i->color );

		position += nodeDistances[ j ];
	}
}