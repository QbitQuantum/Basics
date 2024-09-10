//-----------------------------------------------------------------------------
//! 外接円を計算する
//! @param	[in]	p1	座標1
//! @param	[in]	p2	座標2
//! @param	[in]	p3	座標3
//!	@retval	球構造体
//-----------------------------------------------------------------------------
Sphere&	CascadedShadow::calcCircumscribeCircle(Vector3& p1, Vector3& p2, Vector3& p3)
{

	//---- 外心を求める
	Vector3 center = calcCircleCenter(p1, p2, p3);

#if 1 
	//---- 半径を求める
	// 3辺の長さを計算
	Vector3 A = (p1 - p2);
	Vector3 B = (p2 - p3);
	Vector3 C = (p3 - p1);

	f32 a = A.length();
	f32 b = B.length();
	f32 c = C.length();

	// 余弦定理で角度を求める
	Radian radA = calcLawOfCosines(a, b, c);
	// 正弦定理で半径を求める
	// 2R = a / sinA
	f32 R = (a / sinf(radA)) / 2.0f;
#else
	// 求めた外心から半径を計算する
	f32 R = (center - p1).length();
#endif
	
	// 求まった球の情報を返す
	return Sphere(center, R);
}