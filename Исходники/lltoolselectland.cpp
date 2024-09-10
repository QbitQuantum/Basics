void LLToolSelectLand::roundXY(LLVector3d &vec)
{
	vec.mdV[VX] = llround( vec.mdV[VX], (F64)PARCEL_GRID_STEP_METERS );
	vec.mdV[VY] = llround( vec.mdV[VY], (F64)PARCEL_GRID_STEP_METERS );
}