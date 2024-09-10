/*
 * gdip_region_transform_tree:
 * @tree: a GpPathTree
 * @matrix: the GpMatrix to apply to the tree
 *
 * Recursively apply the @matrix to the @tree.
 */
GpStatus
gdip_region_transform_tree (GpPathTree *tree, GpMatrix *matrix)
{
	if (tree->path) {
		return GdipTransformPath (tree->path, matrix);
	} else {
		GpStatus status;
		status = gdip_region_transform_tree (tree->branch1, matrix);
		if (status == Ok)
			status = gdip_region_transform_tree (tree->branch2, matrix);
		return status;
	}
}