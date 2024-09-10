void 
	SpatialGrid::getVoxelRange(
	const MBoundingBox& box,
	gridPoint3<int>& minIndices,
	gridPoint3<int>& maxIndices 
	) const
	//
	//	Description:
	//
	//		Given a bounding box, compute the min and max voxel
	//		indices (in x, y, z) of the cells that intersect the box.
	//
{
	//	get bbox corners
	//
	const MPoint& minPt = box.min();
	const MPoint& maxPt = box.max();

	//	return indices for min/max corners
	//
	getVoxelCoords( minPt, minIndices, NULL );
	getVoxelCoords( maxPt, maxIndices, NULL );
}