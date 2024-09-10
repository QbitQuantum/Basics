/**
 * GetSelectionBoxCoeff
 *  returns the topright & bottomleft corner positions of the SelectionBox in (cam->right, cam->up)-space
 */
void CMouseHandler::GetSelectionBoxCoeff(const float3& pos1, const float3& dir1, const float3& pos2, const float3& dir2, float2& topright, float2& btmleft)
{
	float dist = ground->LineGroundCol(pos1, pos1 + dir1 * globalRendering->viewRange * 1.4f, false);
	if(dist < 0) dist = globalRendering->viewRange * 1.4f;
	float3 gpos1 = pos1 + dir1 * dist;

	dist = ground->LineGroundCol(pos2, pos2 + dir2 * globalRendering->viewRange * 1.4f, false);
	if(dist < 0) dist = globalRendering->viewRange * 1.4f;
	float3 gpos2 = pos2 + dir2 * dist;

	const float3 cdir1 = (gpos1 - camera->pos).ANormalize();
	const float3 cdir2 = (gpos2 - camera->pos).ANormalize();

	// prevent DivByZero
	float cdir1_fw = cdir1.dot(camera->forward); if (cdir1_fw == 0.0f) cdir1_fw = 0.0001f;
	float cdir2_fw = cdir2.dot(camera->forward); if (cdir2_fw == 0.0f) cdir2_fw = 0.0001f;

	// one corner of the rectangle
	topright.x = cdir1.dot(camera->right) / cdir1_fw;
	topright.y = cdir1.dot(camera->up)    / cdir1_fw;

	// opposite corner
	btmleft.x = cdir2.dot(camera->right) / cdir2_fw;
	btmleft.y = cdir2.dot(camera->up)    / cdir2_fw;

	// sort coeff so topright really is the topright corner
	if (topright.x < btmleft.x) std::swap(topright.x, btmleft.x);
	if (topright.y < btmleft.y) std::swap(topright.y, btmleft.y);
}