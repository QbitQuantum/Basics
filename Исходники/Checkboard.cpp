	inline const C3DVECTOR2 BumpInt(const C3DVECTOR2& rkIn) const
	{
		C3DVECTOR2 kFloorVec(FloorF(rkIn.x * 0.5f), FloorF(rkIn.y * 0.5f));
		return C3DVECTOR2(kFloorVec.x + MaxF(rkIn.x - 2.0f * kFloorVec.x - 1.0f, 0.0f), 
						  kFloorVec.y + MaxF(rkIn.y - 2.0f * kFloorVec.y - 1.0f, 0.0f));
	}