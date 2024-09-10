/*
===================
R_AddSingleModel

May be run in parallel.

Here is where dynamic models actually get instantiated, and necessary
interaction surfaces get created. This is all done on a sort-by-model
basis to keep source data in cache (most likely L2) as any interactions
and shadows are generated, since dynamic models will typically be lit by
two or more lights.
===================
*/
void R_AddSingleModel( viewEntity_t* vEntity )
{
	// we will add all interaction surfs here, to be chained to the lights in later serial code
	vEntity->drawSurfs = NULL;
	vEntity->staticShadowVolumes = NULL;
	vEntity->dynamicShadowVolumes = NULL;
	
	// globals we really should pass in...
	const viewDef_t* viewDef = tr.viewDef;
	
	idRenderEntityLocal* entityDef = vEntity->entityDef;
	const renderEntity_t* renderEntity = &entityDef->parms;
	const idRenderWorldLocal* world = entityDef->world;
	
	if( viewDef->isXraySubview && entityDef->parms.xrayIndex == 1 )
	{
		return;
	}
	else if( !viewDef->isXraySubview && entityDef->parms.xrayIndex == 2 )
	{
		return;
	}
	
	SCOPED_PROFILE_EVENT( renderEntity->hModel == NULL ? "Unknown Model" : renderEntity->hModel->Name() );
	
	// calculate the znear for testing whether or not the view is inside a shadow projection
	const float znear = ( viewDef->renderView.cramZNear ) ? ( r_znear.GetFloat() * 0.25f ) : r_znear.GetFloat();
	
	// if the entity wasn't seen through a portal chain, it was added just for light shadows
	const bool modelIsVisible = !vEntity->scissorRect.IsEmpty();
	const bool addInteractions = modelIsVisible && ( !viewDef->isXraySubview || entityDef->parms.xrayIndex == 2 );
	const int entityIndex = entityDef->index;
	
	//---------------------------
	// Find which of the visible lights contact this entity
	//
	// If the entity doesn't accept light or cast shadows from any surface,
	// this can be skipped.
	//
	// OPTIMIZE: world areas can assume all referenced lights are used
	//---------------------------
	int	numContactedLights = 0;
	static const int MAX_CONTACTED_LIGHTS = 128;
	viewLight_t* contactedLights[MAX_CONTACTED_LIGHTS];
	idInteraction* staticInteractions[MAX_CONTACTED_LIGHTS];
	
	if( renderEntity->hModel == NULL ||
			renderEntity->hModel->ModelHasInteractingSurfaces() ||
			renderEntity->hModel->ModelHasShadowCastingSurfaces() )
	{
		SCOPED_PROFILE_EVENT( "Find lights" );
		for( viewLight_t* vLight = viewDef->viewLights; vLight != NULL; vLight = vLight->next )
		{
			if( vLight->scissorRect.IsEmpty() )
			{
				continue;
			}
			if( vLight->entityInteractionState != NULL )
			{
				// new code path, everything was done in AddLight
				if( vLight->entityInteractionState[entityIndex] == viewLight_t::INTERACTION_YES )
				{
					contactedLights[numContactedLights] = vLight;
					staticInteractions[numContactedLights] = world->interactionTable[vLight->lightDef->index * world->interactionTableWidth + entityIndex];
					if( ++numContactedLights == MAX_CONTACTED_LIGHTS )
					{
						break;
					}
				}
				continue;
			}
			
			const idRenderLightLocal* lightDef = vLight->lightDef;
			
			if( !lightDef->globalLightBounds.IntersectsBounds( entityDef->globalReferenceBounds ) )
			{
				continue;
			}
			
			if( R_CullModelBoundsToLight( lightDef, entityDef->localReferenceBounds, entityDef->modelRenderMatrix ) )
			{
				continue;
			}
			
			if( !modelIsVisible )
			{
				// some lights have their center of projection outside the world
				if( lightDef->areaNum != -1 )
				{
					// if no part of the model is in an area that is connected to
					// the light center (it is behind a solid, closed door), we can ignore it
					bool areasConnected = false;
					for( areaReference_t* ref = entityDef->entityRefs; ref != NULL; ref = ref->ownerNext )
					{
						if( world->AreasAreConnected( lightDef->areaNum, ref->area->areaNum, PS_BLOCK_VIEW ) )
						{
							areasConnected = true;
							break;
						}
					}
					if( areasConnected == false )
					{
						// can't possibly be seen or shadowed
						continue;
					}
				}
				
				// check more precisely for shadow visibility
				idBounds shadowBounds;
				R_ShadowBounds( entityDef->globalReferenceBounds, lightDef->globalLightBounds, lightDef->globalLightOrigin, shadowBounds );
				
				// this doesn't say that the shadow can't effect anything, only that it can't
				// effect anything in the view
				if( idRenderMatrix::CullBoundsToMVP( viewDef->worldSpace.mvp, shadowBounds ) )
				{
					continue;
				}
			}
			contactedLights[numContactedLights] = vLight;
			staticInteractions[numContactedLights] = world->interactionTable[vLight->lightDef->index * world->interactionTableWidth + entityIndex];
			if( ++numContactedLights == MAX_CONTACTED_LIGHTS )
			{
				break;
			}
		}
	}
	
	// if we aren't visible and none of the shadows stretch into the view,
	// we don't need to do anything else
	if( !modelIsVisible && numContactedLights == 0 )
	{
		return;
	}
	
	//---------------------------
	// create a dynamic model if the geometry isn't static
	//---------------------------
	idRenderModel* model = R_EntityDefDynamicModel( entityDef );
	if( model == NULL || model->NumSurfaces() <= 0 )
	{
		return;
	}
	
	// add the lightweight blood decal surfaces if the model is directly visible
	if( modelIsVisible )
	{
		assert( !vEntity->scissorRect.IsEmpty() );
		
		if( entityDef->decals != NULL && !r_skipDecals.GetBool() )
		{
			entityDef->decals->CreateDeferredDecals( model );
			
			unsigned int numDrawSurfs = entityDef->decals->GetNumDecalDrawSurfs();
			for( unsigned int i = 0; i < numDrawSurfs; i++ )
			{
				drawSurf_t* decalDrawSurf = entityDef->decals->CreateDecalDrawSurf( vEntity, i );
				if( decalDrawSurf != NULL )
				{
					decalDrawSurf->linkChain = NULL;
					decalDrawSurf->nextOnLight = vEntity->drawSurfs;
					vEntity->drawSurfs = decalDrawSurf;
				}
			}
		}
		
		if( entityDef->overlays != NULL && !r_skipOverlays.GetBool() )
		{
			entityDef->overlays->CreateDeferredOverlays( model );
			
			unsigned int numDrawSurfs = entityDef->overlays->GetNumOverlayDrawSurfs();
			for( unsigned int i = 0; i < numDrawSurfs; i++ )
			{
				drawSurf_t* overlayDrawSurf = entityDef->overlays->CreateOverlayDrawSurf( vEntity, model, i );
				if( overlayDrawSurf != NULL )
				{
					overlayDrawSurf->linkChain = NULL;
					overlayDrawSurf->nextOnLight = vEntity->drawSurfs;
					vEntity->drawSurfs = overlayDrawSurf;
				}
			}
		}
	}
	
	//---------------------------
	// copy matrix related stuff for back-end use
	// and setup a render matrix for faster culling
	//---------------------------
	vEntity->modelDepthHack = renderEntity->modelDepthHack;
	vEntity->weaponDepthHack = renderEntity->weaponDepthHack;
	vEntity->skipMotionBlur = renderEntity->skipMotionBlur;
	
	memcpy( vEntity->modelMatrix, entityDef->modelMatrix, sizeof( vEntity->modelMatrix ) );
	R_MatrixMultiply( entityDef->modelMatrix, viewDef->worldSpace.modelViewMatrix, vEntity->modelViewMatrix );
	
	idRenderMatrix viewMat;
	idRenderMatrix::Transpose( *( idRenderMatrix* )vEntity->modelViewMatrix, viewMat );
	idRenderMatrix::Multiply( viewDef->projectionRenderMatrix, viewMat, vEntity->mvp );
	if( renderEntity->weaponDepthHack )
	{
		idRenderMatrix::ApplyDepthHack( vEntity->mvp );
	}
	if( renderEntity->modelDepthHack != 0.0f )
	{
		idRenderMatrix::ApplyModelDepthHack( vEntity->mvp, renderEntity->modelDepthHack );
	}
	
	// local light and view origins are used to determine if the view is definitely outside
	// an extruded shadow volume, which means we can skip drawing the end caps
	idVec3 localViewOrigin;
	R_GlobalPointToLocal( vEntity->modelMatrix, viewDef->renderView.vieworg, localViewOrigin );
	
	//---------------------------
	// add all the model surfaces
	//---------------------------
	for( int surfaceNum = 0; surfaceNum < model->NumSurfaces(); surfaceNum++ )
	{
		const modelSurface_t* surf = model->Surface( surfaceNum );
		
		// for debugging, only show a single surface at a time
		if( r_singleSurface.GetInteger() >= 0 && surfaceNum != r_singleSurface.GetInteger() )
		{
			continue;
		}
		
		srfTriangles_t* tri = surf->geometry;
		if( tri == NULL )
		{
			continue;
		}
		if( tri->numIndexes == 0 )
		{
			continue;		// happens for particles
		}
		const idMaterial* shader = surf->shader;
		if( shader == NULL )
		{
			continue;
		}
		if( !shader->IsDrawn() )
		{
			continue;		// collision hulls, etc
		}
		
		// RemapShaderBySkin
		if( entityDef->parms.customShader != NULL )
		{
			// this is sort of a hack, but causes deformed surfaces to map to empty surfaces,
			// so the item highlight overlay doesn't highlight the autosprite surface
			if( shader->Deform() )
			{
				continue;
			}
			shader = entityDef->parms.customShader;
		}
		else if( entityDef->parms.customSkin )
		{
			shader = entityDef->parms.customSkin->RemapShaderBySkin( shader );
			if( shader == NULL )
			{
				continue;
			}
			if( !shader->IsDrawn() )
			{
				continue;
			}
		}
		
		// optionally override with the renderView->globalMaterial
		if( tr.primaryRenderView.globalMaterial != NULL )
		{
			shader = tr.primaryRenderView.globalMaterial;
		}
		
		SCOPED_PROFILE_EVENT( shader->GetName() );
		
		// debugging tool to make sure we have the correct pre-calculated bounds
		if( r_checkBounds.GetBool() )
		{
			for( int j = 0; j < tri->numVerts; j++ )
			{
				int k;
				for( k = 0; k < 3; k++ )
				{
					if( tri->verts[j].xyz[k] > tri->bounds[1][k] + CHECK_BOUNDS_EPSILON
							|| tri->verts[j].xyz[k] < tri->bounds[0][k] - CHECK_BOUNDS_EPSILON )
					{
						common->Printf( "bad tri->bounds on %s:%s\n", entityDef->parms.hModel->Name(), shader->GetName() );
						break;
					}
					if( tri->verts[j].xyz[k] > entityDef->localReferenceBounds[1][k] + CHECK_BOUNDS_EPSILON
							|| tri->verts[j].xyz[k] < entityDef->localReferenceBounds[0][k] - CHECK_BOUNDS_EPSILON )
					{
						common->Printf( "bad referenceBounds on %s:%s\n", entityDef->parms.hModel->Name(), shader->GetName() );
						break;
					}
				}
				if( k != 3 )
				{
					break;
				}
			}
		}
		
		// view frustum culling for the precise surface bounds, which is tighter
		// than the entire entity reference bounds
		// If the entire model wasn't visible, there is no need to check the
		// individual surfaces.
		const bool surfaceDirectlyVisible = modelIsVisible && !idRenderMatrix::CullBoundsToMVP( vEntity->mvp, tri->bounds );
		
		// RB: added check wether GPU skinning is available at all
		const bool gpuSkinned = ( tri->staticModelWithJoints != NULL && r_useGPUSkinning.GetBool() && glConfig.gpuSkinningAvailable );
		// RB end
		
		//--------------------------
		// base drawing surface
		//--------------------------
		drawSurf_t* baseDrawSurf = NULL;
		if( surfaceDirectlyVisible )
		{
			// make sure we have an ambient cache and all necessary normals / tangents
			if( !vertexCache.CacheIsCurrent( tri->indexCache ) )
			{
				tri->indexCache = vertexCache.AllocIndex( tri->indexes, ALIGN( tri->numIndexes * sizeof( triIndex_t ), INDEX_CACHE_ALIGN ) );
			}
			
			if( !vertexCache.CacheIsCurrent( tri->ambientCache ) )
			{
				// we are going to use it for drawing, so make sure we have the tangents and normals
				if( shader->ReceivesLighting() && !tri->tangentsCalculated )
				{
					assert( tri->staticModelWithJoints == NULL );
					R_DeriveTangents( tri );
					
					// RB: this was hit by parametric particle models ..
					//assert( false );	// this should no longer be hit
					// RB end
				}
				tri->ambientCache = vertexCache.AllocVertex( tri->verts, ALIGN( tri->numVerts * sizeof( idDrawVert ), VERTEX_CACHE_ALIGN ) );
			}
			
			// add the surface for drawing
			// we can re-use some of the values for light interaction surfaces
			baseDrawSurf = ( drawSurf_t* )R_FrameAlloc( sizeof( *baseDrawSurf ), FRAME_ALLOC_DRAW_SURFACE );
			baseDrawSurf->frontEndGeo = tri;
			baseDrawSurf->space = vEntity;
			baseDrawSurf->scissorRect = vEntity->scissorRect;
			baseDrawSurf->extraGLState = 0;
			baseDrawSurf->renderZFail = 0;
			
			R_SetupDrawSurfShader( baseDrawSurf, shader, renderEntity );
			
			// Check for deformations (eyeballs, flares, etc)
			const deform_t shaderDeform = shader->Deform();
			if( shaderDeform != DFRM_NONE )
			{
				drawSurf_t* deformDrawSurf = R_DeformDrawSurf( baseDrawSurf );
				if( deformDrawSurf != NULL )
				{
					// any deforms may have created multiple draw surfaces
					for( drawSurf_t* surf = deformDrawSurf, * next = NULL; surf != NULL; surf = next )
					{
						next = surf->nextOnLight;
						
						surf->linkChain = NULL;
						surf->nextOnLight = vEntity->drawSurfs;
						vEntity->drawSurfs = surf;
					}
				}
			}
			
			// Most deform source surfaces do not need to be rendered.
			// However, particles are rendered in conjunction with the source surface.
			if( shaderDeform == DFRM_NONE || shaderDeform == DFRM_PARTICLE || shaderDeform == DFRM_PARTICLE2 )
			{
				// copy verts and indexes to this frame's hardware memory if they aren't already there
				if( !vertexCache.CacheIsCurrent( tri->ambientCache ) )
				{
					tri->ambientCache = vertexCache.AllocVertex( tri->verts, ALIGN( tri->numVerts * sizeof( tri->verts[0] ), VERTEX_CACHE_ALIGN ) );
				}
				if( !vertexCache.CacheIsCurrent( tri->indexCache ) )
				{
					tri->indexCache = vertexCache.AllocIndex( tri->indexes, ALIGN( tri->numIndexes * sizeof( tri->indexes[0] ), INDEX_CACHE_ALIGN ) );
				}
				
				R_SetupDrawSurfJoints( baseDrawSurf, tri, shader );
				
				baseDrawSurf->numIndexes = tri->numIndexes;
				baseDrawSurf->ambientCache = tri->ambientCache;
				baseDrawSurf->indexCache = tri->indexCache;
				baseDrawSurf->shadowCache = 0;
				
				baseDrawSurf->linkChain = NULL;		// link to the view
				baseDrawSurf->nextOnLight = vEntity->drawSurfs;
				vEntity->drawSurfs = baseDrawSurf;
			}
		}
		
		//----------------------------------------
		// add all light interactions
		//----------------------------------------
		for( int contactedLight = 0; contactedLight < numContactedLights; contactedLight++ )
		{
			viewLight_t* vLight = contactedLights[contactedLight];
			const idRenderLightLocal* lightDef = vLight->lightDef;
			const idInteraction* interaction = staticInteractions[contactedLight];
			
			// check for a static interaction
			surfaceInteraction_t* surfInter = NULL;
			if( interaction > INTERACTION_EMPTY && interaction->staticInteraction )
			{
				// we have a static interaction that was calculated accurately
				assert( model->NumSurfaces() == interaction->numSurfaces );
				surfInter = &interaction->surfaces[surfaceNum];
			}
			else
			{
				// try to do a more precise cull of this model surface to the light
				if( R_CullModelBoundsToLight( lightDef, tri->bounds, entityDef->modelRenderMatrix ) )
				{
					continue;
				}
			}
			
			// "invisible ink" lights and shaders (imp spawn drawing on walls, etc)
			if( shader->Spectrum() != lightDef->lightShader->Spectrum() )
			{
				continue;
			}
			
			// Calculate the local light origin to determine if the view is inside the shadow
			// projection and to calculate the triangle facing for dynamic shadow volumes.
			idVec3 localLightOrigin;
			R_GlobalPointToLocal( vEntity->modelMatrix, lightDef->globalLightOrigin, localLightOrigin );
			
			//--------------------------
			// surface light interactions
			//--------------------------
			
			dynamicShadowVolumeParms_t* dynamicShadowParms = NULL;
			
			if( addInteractions && surfaceDirectlyVisible && shader->ReceivesLighting() )
			{
				// static interactions can commonly find that no triangles from a surface
				// contact the light, even when the total model does
				if( surfInter == NULL || surfInter->lightTrisIndexCache > 0 )
				{
					// create a drawSurf for this interaction
					drawSurf_t* lightDrawSurf = ( drawSurf_t* )R_FrameAlloc( sizeof( *lightDrawSurf ), FRAME_ALLOC_DRAW_SURFACE );
					
					if( surfInter != NULL )
					{
						// optimized static interaction
						lightDrawSurf->numIndexes = surfInter->numLightTrisIndexes;
						lightDrawSurf->indexCache = surfInter->lightTrisIndexCache;
					}
					else
					{
						// throw the entire source surface at it without any per-triangle culling
						lightDrawSurf->numIndexes = tri->numIndexes;
						lightDrawSurf->indexCache = tri->indexCache;
						
						// optionally cull the triangles to the light volume
						if( r_cullDynamicLightTriangles.GetBool() )
						{
						
							vertCacheHandle_t lightIndexCache = vertexCache.AllocIndex( NULL, ALIGN( lightDrawSurf->numIndexes * sizeof( triIndex_t ), INDEX_CACHE_ALIGN ) );
							if( vertexCache.CacheIsCurrent( lightIndexCache ) )
							{
								lightDrawSurf->indexCache = lightIndexCache;
								
								dynamicShadowParms = ( dynamicShadowVolumeParms_t* )R_FrameAlloc( sizeof( dynamicShadowParms[0] ), FRAME_ALLOC_SHADOW_VOLUME_PARMS );
								
								dynamicShadowParms->verts = tri->verts;
								dynamicShadowParms->numVerts = tri->numVerts;
								dynamicShadowParms->indexes = tri->indexes;
								dynamicShadowParms->numIndexes = tri->numIndexes;
								dynamicShadowParms->silEdges = tri->silEdges;
								dynamicShadowParms->numSilEdges = tri->numSilEdges;
								dynamicShadowParms->joints = gpuSkinned ? tri->staticModelWithJoints->jointsInverted : NULL;
								dynamicShadowParms->numJoints = gpuSkinned ? tri->staticModelWithJoints->numInvertedJoints : 0;
								dynamicShadowParms->triangleBounds = tri->bounds;
								dynamicShadowParms->triangleMVP = vEntity->mvp;
								dynamicShadowParms->localLightOrigin = localLightOrigin;
								dynamicShadowParms->localViewOrigin = localViewOrigin;
								idRenderMatrix::Multiply( vLight->lightDef->baseLightProject, entityDef->modelRenderMatrix, dynamicShadowParms->localLightProject );
								dynamicShadowParms->zNear = znear;
								dynamicShadowParms->lightZMin = vLight->scissorRect.zmin;
								dynamicShadowParms->lightZMax = vLight->scissorRect.zmax;
								dynamicShadowParms->cullShadowTrianglesToLight = false;
								dynamicShadowParms->forceShadowCaps = false;
								dynamicShadowParms->useShadowPreciseInsideTest = false;
								dynamicShadowParms->useShadowDepthBounds = false;
								dynamicShadowParms->tempFacing = NULL;
								dynamicShadowParms->tempCulled = NULL;
								dynamicShadowParms->tempVerts = NULL;
								dynamicShadowParms->indexBuffer = NULL;
								dynamicShadowParms->shadowIndices = NULL;
								dynamicShadowParms->maxShadowIndices = 0;
								dynamicShadowParms->numShadowIndices = NULL;
								dynamicShadowParms->lightIndices = ( triIndex_t* )vertexCache.MappedIndexBuffer( lightIndexCache );
								dynamicShadowParms->maxLightIndices = lightDrawSurf->numIndexes;
								dynamicShadowParms->numLightIndices = &lightDrawSurf->numIndexes;
								dynamicShadowParms->renderZFail = NULL;
								dynamicShadowParms->shadowZMin = NULL;
								dynamicShadowParms->shadowZMax = NULL;
								dynamicShadowParms->shadowVolumeState = & lightDrawSurf->shadowVolumeState;
								
								lightDrawSurf->shadowVolumeState = SHADOWVOLUME_UNFINISHED;
								
								dynamicShadowParms->next = vEntity->dynamicShadowVolumes;
								vEntity->dynamicShadowVolumes = dynamicShadowParms;
							}
						}
					}
					lightDrawSurf->ambientCache = tri->ambientCache;
					lightDrawSurf->shadowCache = 0;
					lightDrawSurf->frontEndGeo = tri;
					lightDrawSurf->space = vEntity;
					lightDrawSurf->material = shader;
					lightDrawSurf->extraGLState = 0;
					lightDrawSurf->scissorRect = vLight->scissorRect; // interactionScissor;
					lightDrawSurf->sort = 0.0f;
					lightDrawSurf->renderZFail = 0;
					lightDrawSurf->shaderRegisters = baseDrawSurf->shaderRegisters;
					
					R_SetupDrawSurfJoints( lightDrawSurf, tri, shader );
					
					// Determine which linked list to add the light surface to.
					// There will only be localSurfaces if the light casts shadows and
					// there are surfaces with NOSELFSHADOW.
					if( shader->Coverage() == MC_TRANSLUCENT )
					{
						lightDrawSurf->linkChain = &vLight->translucentInteractions;
					}
					else if( !lightDef->parms.noShadows && shader->TestMaterialFlag( MF_NOSELFSHADOW ) )
					{
						lightDrawSurf->linkChain = &vLight->localInteractions;
					}
					else
					{
						lightDrawSurf->linkChain = &vLight->globalInteractions;
					}
					lightDrawSurf->nextOnLight = vEntity->drawSurfs;
					vEntity->drawSurfs = lightDrawSurf;
				}
			}
			
			//--------------------------
			// surface shadows
			//--------------------------
			
			if( !shader->SurfaceCastsShadow() )
			{
				continue;
			}
			if( !lightDef->LightCastsShadows() )
			{
				continue;
			}
			if( tri->silEdges == NULL )
			{
				continue;		// can happen for beam models (shouldn't use a shadow casting material, though...)
			}
			
			// if the static shadow does not have any shadows
			if( surfInter != NULL && surfInter->numShadowIndexes == 0 && !r_useShadowMapping.GetBool() )
			{
				continue;
			}
			
			// some entities, like view weapons, don't cast any shadows
			if( entityDef->parms.noShadow )
			{
				continue;
			}
			
			// No shadow if it's suppressed for this light.
			if( entityDef->parms.suppressShadowInLightID && entityDef->parms.suppressShadowInLightID == lightDef->parms.lightId )
			{
				continue;
			}
			
			// RB begin
			if( r_useShadowMapping.GetBool() )
			{
				//if( addInteractions && surfaceDirectlyVisible && shader->ReceivesLighting() )
				{
					// static interactions can commonly find that no triangles from a surface
					// contact the light, even when the total model does
					if( surfInter == NULL || surfInter->lightTrisIndexCache > 0 )
					{
						// create a drawSurf for this interaction
						drawSurf_t* shadowDrawSurf = ( drawSurf_t* )R_FrameAlloc( sizeof( *shadowDrawSurf ), FRAME_ALLOC_DRAW_SURFACE );
						
						if( surfInter != NULL )
						{
							// optimized static interaction
							shadowDrawSurf->numIndexes = surfInter->numLightTrisIndexes;
							shadowDrawSurf->indexCache = surfInter->lightTrisIndexCache;
						}
						else
						{
							// make sure we have an ambient cache and all necessary normals / tangents
							if( !vertexCache.CacheIsCurrent( tri->indexCache ) )
							{
								tri->indexCache = vertexCache.AllocIndex( tri->indexes, ALIGN( tri->numIndexes * sizeof( triIndex_t ), INDEX_CACHE_ALIGN ) );
							}
							
							// throw the entire source surface at it without any per-triangle culling
							shadowDrawSurf->numIndexes = tri->numIndexes;
							shadowDrawSurf->indexCache = tri->indexCache;
						}
						
						if( !vertexCache.CacheIsCurrent( tri->ambientCache ) )
						{
							// we are going to use it for drawing, so make sure we have the tangents and normals
							if( shader->ReceivesLighting() && !tri->tangentsCalculated )
							{
								assert( tri->staticModelWithJoints == NULL );
								R_DeriveTangents( tri );
								
								// RB: this was hit by parametric particle models ..
								//assert( false );	// this should no longer be hit
								// RB end
							}
							tri->ambientCache = vertexCache.AllocVertex( tri->verts, ALIGN( tri->numVerts * sizeof( idDrawVert ), VERTEX_CACHE_ALIGN ) );
						}
						
						shadowDrawSurf->ambientCache = tri->ambientCache;
						shadowDrawSurf->shadowCache = 0;
						shadowDrawSurf->frontEndGeo = tri;
						shadowDrawSurf->space = vEntity;
						shadowDrawSurf->material = shader;
						shadowDrawSurf->extraGLState = 0;
						shadowDrawSurf->scissorRect = vLight->scissorRect; // interactionScissor;
						shadowDrawSurf->sort = 0.0f;
						shadowDrawSurf->renderZFail = 0;
						//shadowDrawSurf->shaderRegisters = baseDrawSurf->shaderRegisters;
						
						R_SetupDrawSurfJoints( shadowDrawSurf, tri, shader );
						
						// determine which linked list to add the shadow surface to
						
						//shadowDrawSurf->linkChain = shader->TestMaterialFlag( MF_NOSELFSHADOW ) ? &vLight->localShadows : &vLight->globalShadows;
						
						shadowDrawSurf->linkChain = &vLight->globalShadows;
						shadowDrawSurf->nextOnLight = vEntity->drawSurfs;
						
						vEntity->drawSurfs = shadowDrawSurf;
						
					}
				}
				
				
				continue;
			}
			// RB end
			
			if( lightDef->parms.prelightModel && lightDef->lightHasMoved == false &&
					entityDef->parms.hModel->IsStaticWorldModel() && !r_skipPrelightShadows.GetBool() )
			{
				// static light / world model shadow interacitons
				// are always captured in the prelight shadow volume
				continue;
			}
			
			// If the shadow is drawn (or translucent), but the model isn't, we must include the shadow caps
			// because we may be able to see into the shadow volume even though the view is outside it.
			// This happens for the player world weapon and possibly some animations in multiplayer.
			const bool forceShadowCaps = !addInteractions || r_forceShadowCaps.GetBool();
			
			drawSurf_t* shadowDrawSurf = ( drawSurf_t* )R_FrameAlloc( sizeof( *shadowDrawSurf ), FRAME_ALLOC_DRAW_SURFACE );
			
			if( surfInter != NULL )
			{
				shadowDrawSurf->numIndexes = 0;
				shadowDrawSurf->indexCache = surfInter->shadowIndexCache;
				shadowDrawSurf->shadowCache = tri->shadowCache;
				shadowDrawSurf->scissorRect = vLight->scissorRect;		// default to the light scissor and light depth bounds
				shadowDrawSurf->shadowVolumeState = SHADOWVOLUME_DONE;	// assume the shadow volume is done in case r_skipStaticShadows is set
				
				if( !r_skipStaticShadows.GetBool() )
				{
					staticShadowVolumeParms_t* staticShadowParms = ( staticShadowVolumeParms_t* )R_FrameAlloc( sizeof( staticShadowParms[0] ), FRAME_ALLOC_SHADOW_VOLUME_PARMS );
					
					staticShadowParms->verts = tri->staticShadowVertexes;
					staticShadowParms->numVerts = tri->numVerts * 2;
					staticShadowParms->indexes = surfInter->shadowIndexes;
					staticShadowParms->numIndexes = surfInter->numShadowIndexes;
					staticShadowParms->numShadowIndicesWithCaps = surfInter->numShadowIndexes;
					staticShadowParms->numShadowIndicesNoCaps = surfInter->numShadowIndexesNoCaps;
					staticShadowParms->triangleBounds = tri->bounds;
					staticShadowParms->triangleMVP = vEntity->mvp;
					staticShadowParms->localLightOrigin = localLightOrigin;
					staticShadowParms->localViewOrigin = localViewOrigin;
					staticShadowParms->zNear = znear;
					staticShadowParms->lightZMin = vLight->scissorRect.zmin;
					staticShadowParms->lightZMax = vLight->scissorRect.zmax;
					staticShadowParms->forceShadowCaps = forceShadowCaps;
					staticShadowParms->useShadowPreciseInsideTest = r_useShadowPreciseInsideTest.GetBool();
					staticShadowParms->useShadowDepthBounds = r_useShadowDepthBounds.GetBool();
					staticShadowParms->numShadowIndices = & shadowDrawSurf->numIndexes;
					staticShadowParms->renderZFail = & shadowDrawSurf->renderZFail;
					staticShadowParms->shadowZMin = & shadowDrawSurf->scissorRect.zmin;
					staticShadowParms->shadowZMax = & shadowDrawSurf->scissorRect.zmax;
					staticShadowParms->shadowVolumeState = & shadowDrawSurf->shadowVolumeState;
					
					shadowDrawSurf->shadowVolumeState = SHADOWVOLUME_UNFINISHED;
					
					staticShadowParms->next = vEntity->staticShadowVolumes;
					vEntity->staticShadowVolumes = staticShadowParms;
				}
				
			}
			else
			{
				// When CPU skinning the dynamic shadow verts of a dynamic model may not have been copied to buffer memory yet.
				if( !vertexCache.CacheIsCurrent( tri->shadowCache ) )
				{
					assert( !gpuSkinned );	// the shadow cache should be static when using GPU skinning
					// Extracts just the xyz values from a set of full size drawverts, and
					// duplicates them with w set to 0 and 1 for the vertex program to project.
					// This is constant for any number of lights, the vertex program takes care
					// of projecting the verts to infinity for a particular light.
					tri->shadowCache = vertexCache.AllocVertex( NULL, ALIGN( tri->numVerts * 2 * sizeof( idShadowVert ), VERTEX_CACHE_ALIGN ) );
					idShadowVert* shadowVerts = ( idShadowVert* )vertexCache.MappedVertexBuffer( tri->shadowCache );
					idShadowVert::CreateShadowCache( shadowVerts, tri->verts, tri->numVerts );
				}
				
				const int maxShadowVolumeIndexes = tri->numSilEdges * 6 + tri->numIndexes * 2;
				
				shadowDrawSurf->numIndexes = 0;
				shadowDrawSurf->indexCache = vertexCache.AllocIndex( NULL, ALIGN( maxShadowVolumeIndexes * sizeof( triIndex_t ), INDEX_CACHE_ALIGN ) );
				shadowDrawSurf->shadowCache = tri->shadowCache;
				shadowDrawSurf->scissorRect = vLight->scissorRect;		// default to the light scissor and light depth bounds
				shadowDrawSurf->shadowVolumeState = SHADOWVOLUME_DONE;	// assume the shadow volume is done in case the index cache allocation failed
				
				// if the index cache was successfully allocated then setup the parms to create a shadow volume in parallel
				if( vertexCache.CacheIsCurrent( shadowDrawSurf->indexCache ) && !r_skipDynamicShadows.GetBool() )
				{
				
					// if the parms were not already allocated for culling interaction triangles to the light frustum
					if( dynamicShadowParms == NULL )
					{
						dynamicShadowParms = ( dynamicShadowVolumeParms_t* )R_FrameAlloc( sizeof( dynamicShadowParms[0] ), FRAME_ALLOC_SHADOW_VOLUME_PARMS );
					}
					else
					{
						// the shadow volume will be rendered first so when the interaction surface is drawn the triangles have been culled for sure
						*dynamicShadowParms->shadowVolumeState = SHADOWVOLUME_DONE;
					}
					
					dynamicShadowParms->verts = tri->verts;
					dynamicShadowParms->numVerts = tri->numVerts;
					dynamicShadowParms->indexes = tri->indexes;
					dynamicShadowParms->numIndexes = tri->numIndexes;
					dynamicShadowParms->silEdges = tri->silEdges;
					dynamicShadowParms->numSilEdges = tri->numSilEdges;
					dynamicShadowParms->joints = gpuSkinned ? tri->staticModelWithJoints->jointsInverted : NULL;
					dynamicShadowParms->numJoints = gpuSkinned ? tri->staticModelWithJoints->numInvertedJoints : 0;
					dynamicShadowParms->triangleBounds = tri->bounds;
					dynamicShadowParms->triangleMVP = vEntity->mvp;
					dynamicShadowParms->localLightOrigin = localLightOrigin;
					dynamicShadowParms->localViewOrigin = localViewOrigin;
					idRenderMatrix::Multiply( vLight->lightDef->baseLightProject, entityDef->modelRenderMatrix, dynamicShadowParms->localLightProject );
					dynamicShadowParms->zNear = znear;
					dynamicShadowParms->lightZMin = vLight->scissorRect.zmin;
					dynamicShadowParms->lightZMax = vLight->scissorRect.zmax;
					dynamicShadowParms->cullShadowTrianglesToLight = r_cullDynamicShadowTriangles.GetBool();
					dynamicShadowParms->forceShadowCaps = forceShadowCaps;
					dynamicShadowParms->useShadowPreciseInsideTest = r_useShadowPreciseInsideTest.GetBool();
					dynamicShadowParms->useShadowDepthBounds = r_useShadowDepthBounds.GetBool();
					dynamicShadowParms->tempFacing = NULL;
					dynamicShadowParms->tempCulled = NULL;
					dynamicShadowParms->tempVerts = NULL;
					dynamicShadowParms->indexBuffer = NULL;
					dynamicShadowParms->shadowIndices = ( triIndex_t* )vertexCache.MappedIndexBuffer( shadowDrawSurf->indexCache );
					dynamicShadowParms->maxShadowIndices = maxShadowVolumeIndexes;
					dynamicShadowParms->numShadowIndices = & shadowDrawSurf->numIndexes;
					// dynamicShadowParms->lightIndices may have already been set for the interaction surface
					// dynamicShadowParms->maxLightIndices may have already been set for the interaction surface
					// dynamicShadowParms->numLightIndices may have already been set for the interaction surface
					dynamicShadowParms->renderZFail = & shadowDrawSurf->renderZFail;
					dynamicShadowParms->shadowZMin = & shadowDrawSurf->scissorRect.zmin;
					dynamicShadowParms->shadowZMax = & shadowDrawSurf->scissorRect.zmax;
					dynamicShadowParms->shadowVolumeState = & shadowDrawSurf->shadowVolumeState;
					
					shadowDrawSurf->shadowVolumeState = SHADOWVOLUME_UNFINISHED;
					
					// if the parms we not already linked for culling interaction triangles to the light frustum
					if( dynamicShadowParms->lightIndices == NULL )
					{
						dynamicShadowParms->next = vEntity->dynamicShadowVolumes;
						vEntity->dynamicShadowVolumes = dynamicShadowParms;
					}
					
					tr.pc.c_createShadowVolumes++;
				}
			}
			
			assert( vertexCache.CacheIsCurrent( shadowDrawSurf->shadowCache ) );
			assert( vertexCache.CacheIsCurrent( shadowDrawSurf->indexCache ) );
			
			shadowDrawSurf->ambientCache = 0;
			shadowDrawSurf->frontEndGeo = NULL;
			shadowDrawSurf->space = vEntity;
			shadowDrawSurf->material = NULL;
			shadowDrawSurf->extraGLState = 0;
			shadowDrawSurf->sort = 0.0f;
			shadowDrawSurf->shaderRegisters = NULL;
			
			R_SetupDrawSurfJoints( shadowDrawSurf, tri, NULL );
			
			// determine which linked list to add the shadow surface to
			shadowDrawSurf->linkChain = shader->TestMaterialFlag( MF_NOSELFSHADOW ) ? &vLight->localShadows : &vLight->globalShadows;
			shadowDrawSurf->nextOnLight = vEntity->drawSurfs;
			vEntity->drawSurfs = shadowDrawSurf;
		}
	}
}