//----------------------------------------------------------------------------
void LODTerrain::Simplify ()
{
	if (!mStitched)
	{
		StitchAll();
	}

	const Camera *camera = GraphicsRoot::GetSingleton().GetCamera();

	APoint worldEye = camera->GetPosition();
	AVector worldDir = camera->GetDVector();
	APoint modelEye = WorldTransform.GetMatrix().Inverse() * worldEye;
	AVector modelDir = WorldTransform.GetRotate().Inverse() * worldDir;
	modelDir.Normalize();

	int row, col;
	for (row=0; row<mNumRows; row++)
	{
		for (col=0; col<mNumCols; col++)
		{
			LODTerrainPage *page = DynamicCast<LODTerrainPage>(
				mPages[row][col]);
			page->ResetBlocks();
		}
	}

	for (row=0; row<mNumRows; row++)
	{
		for (col=0; col<mNumCols; col++)
		{
			LODTerrainPage *page = DynamicCast<LODTerrainPage>(mPages[row][col]);
			if (page->IntersectFrustum(camera))
			{
				modelEye = page->WorldTransform.GetMatrix().Inverse()
					* worldEye;
				modelDir = page->WorldTransform.GetMatrix().Inverse()
					* worldDir;

				page->Simplify(modelEye,modelDir,mIsCloseAssumption);
			}
		}
	}
}