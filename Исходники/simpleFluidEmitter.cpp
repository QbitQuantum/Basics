void 
simpleFluidEmitter::volumeFluidEmitter(
	MFnFluid& 		fluid,
	const MMatrix&	fluidWorldMatrix,
	int 			plugIndex,
	MDataBlock& 	block,
	double 			dt,
	double			conversion,
	double			dropoff
)
//==============================================================================
//
//	Method:	
//
//		simpleFluidEmitter::volumeFluidEmitter
//
//	Description:
//
//		Emits fluid from points distributed over the surface of the 
//		emitter's owner object.
//
//	Parameters:
//
//		fluid:				fluid into which we are emitting
//		fluidWorldMatrix:	object->world matrix for the fluid
//		plugIndex:			identifies which fluid connected to the emitter
//							we are emitting into
//		block:				datablock for the emitter, to retrieve attribute
//							values
//		dt:					time delta for this frame
//		conversion:			mapping from UI emission rates to internal units
//		dropoff:			specifies how much emission rate drops off as
//							we move away from the local y-axis of the 
//							volume emitter shape.
//
//==============================================================================
{
	//	get emitter position and relevant matrices 
	//	
	MPoint emitterPos = getWorldPosition();
	MMatrix emitterWorldMatrix = getWorldMatrix();
	MMatrix fluidInverseWorldMatrix = fluidWorldMatrix.inverse();
	
	//	get emission rates for density, fuel, heat, and emission color
	//	
	double densityEmit = fluidDensityEmission( block );
	double fuelEmit = fluidFuelEmission( block );
	double heatEmit = fluidHeatEmission( block );
	bool doEmitColor = fluidEmitColor( block );
	MColor emitColor = fluidColor( block );
	
	//	rate modulation based on frame time, user value conversion factor, and
	//	standard emitter "rate" value (not actually exposed in most fluid
	//	emitters, but there anyway).
	//
	double theRate = getRate(block) * dt * conversion;
	
	//	get voxel dimensions and sizes (object space)
	//
	double size[3];
	unsigned int res[3];
	fluid.getDimensions( size[0], size[1], size[2] );
	fluid.getResolution( res[0], res[1], res[2] );

	//	voxel sizes
	double dx = size[0] / res[0];
	double dy = size[1] / res[1];
	double dz = size[2] / res[2];
	
	// 	voxel centers
	double Ox = -size[0]/2;
	double Oy = -size[1]/2;
	double Oz = -size[2]/2;	

	//	find the voxels that intersect the bounding box of the volume
	//	primitive associated with the emitter
	//
	MBoundingBox bbox;
	if( !volumePrimitiveBoundingBox( bbox ) )
	{
		//	shouldn't happen
		//
		return;
	}
	
	//	transform volume primitive into fluid space
	//
	bbox.transformUsing( emitterWorldMatrix );
	bbox.transformUsing( fluidInverseWorldMatrix );
	MPoint lowCorner = bbox.min();
	MPoint highCorner = bbox.max();

	//	get fluid voxel coord range of bounding box
	//
	::int3 lowCoords;
	::int3 highCoords;
	fluid.toGridIndex( lowCorner, lowCoords );
	fluid.toGridIndex( highCorner, highCoords );
	
	int i;
	for ( i = 0; i < 3; i++ )
	{
		if ( lowCoords[i] < 0 ) {
			lowCoords[i] = 0;
		} else if ( lowCoords[i] > ((int)res[i])-1 ) {
			lowCoords[i] = ((int)res[i])-1;
		}

		if ( highCoords[i] < 0 ) {
			highCoords[i] = 0;
		} else if ( highCoords[i] > ((int)res[i])-1 ) {
			highCoords[i] = ((int)res[i])-1;
		}
		
	}

	//	figure out the emitter size relative to the voxel size, and compute
	//	a per-voxel sampling rate that uses 1 sample/voxel for emitters that
	//	are >= 2 voxels big in all dimensions.  For smaller emitters, use up
	//	to 8 samples per voxel.
	//
	double emitterVoxelSize[3];
	emitterVoxelSize[0] = (highCorner[0]-lowCorner[0])/dx;
	emitterVoxelSize[1] = (highCorner[1]-lowCorner[1])/dy;
	emitterVoxelSize[2] = (highCorner[2]-lowCorner[2])/dz;
		
	double minVoxelSize = MIN(emitterVoxelSize[0],MIN(emitterVoxelSize[1],emitterVoxelSize[2]));
	if( minVoxelSize < 1.0 )
	{
		minVoxelSize = 1.0;
	}
	int maxSamples = 8;
	int numSamples = (int)(8.0/(minVoxelSize*minVoxelSize*minVoxelSize) + 0.5);
	if( numSamples < 1 ) numSamples = 1;
	if( numSamples > maxSamples ) numSamples = maxSamples;
	
	//	non-jittered, just use one sample in the voxel center.  Should replace
	//	with uniform sampling pattern.
	//
	bool jitter = fluidJitter(block);
	if( !jitter )
	{
		numSamples = 1;
	}
	
	//	for each voxel that could potentially intersect the volume emitter
	//	primitive, take some samples in the voxel.  For those inside the
	//	volume, compute their dropoff relative to the primitive's local y-axis,
	//	and emit an appropriate amount into the voxel.
	//
	for( i = lowCoords[0]; i <= highCoords[0]; i++ )
	{
		double x = Ox + (i+0.5)*dx;
			
		for( int j = lowCoords[1]; j < highCoords[1]; j++ )
		{
			double y = Oy + (j+0.5)*dy;

			for( int k = lowCoords[2]; k < highCoords[2]; k++ )
			{
				double z = Oz + (k+0.5)*dz;
				
				for ( int si = 0; si < numSamples; si++) {
					
					//	compute voxel sample point (object space)
					//
					double rx, ry, rz;
					if(jitter) {
						rx = x + dx*(randgen() - 0.5);
						ry = y + dy*(randgen() - 0.5);
						rz = z + dz*(randgen() - 0.5);
					} else {
						rx = x;
						ry = y;
						rz = z;
					}
					
					//	to world space
					MPoint pt( rx, ry, rz );
					pt *= fluidWorldMatrix;

					//	test to see if point is inside volume primitive
					//
					if( volumePrimitivePointInside( pt, emitterWorldMatrix ) )
					{
						//	compute dropoff
						//
						double dist = pt.distanceTo( emitterPos );
						double distDrop = dropoff * (dist*dist);
						double newVal = (theRate * exp( -distDrop )) / (double)numSamples;
						
						//	emit into arrays
						//
						if( newVal != 0.0 )
						{
							fluid.emitIntoArrays( (float) newVal, i, j, k, (float)densityEmit, (float)heatEmit, (float)fuelEmit, doEmitColor, emitColor );
						}
					}
				}
			}
		}
	}
}