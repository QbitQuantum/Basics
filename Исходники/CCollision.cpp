//-----------------------------------------------------------------------------
bool CCollision::CollisionTriangleSphere( const CVector3D &v0,const CVector3D &v1,const CVector3D &v2,const CVector3D &center,float radius ,CVector3D *cross,float *length)
{
   
     CVector3D V1(v1-v0);
	 CVector3D V2(v2-v1);
	 CVector3D N(CVector3D::Cross(V1,V2).GetNormalize());
	 
	 CVector3D V = center - v0;
	 //平面と点の距離を求める
	 float Dist = CVector3D::Dot(V,N);
  
	//球の半径より離れている場合は接触無し
	 if(abs(Dist) > radius) return false;

	 //点から平面上に垂直に下ろした地点を求める
	 CVector3D Point =  center - ( N * Dist );
	 
	 
	 //上記の点が三角形ポリゴン内なら接触している
	 if(TriangleIntersect( Point, v0, v1, v2 , N)) {
		if(cross) *cross = Point;
		if(length) *length = Dist;
		return true;
	}



	 //各辺に球がかすっている可能性がある
	 //１辺ごとに球と辺の最短距離を求める

	 //最短距離
	 float l;
	 //最短接触地点
	 CVector3D c;
	 
	 //距離比較用
	 float LengthSq;



	 //辺１(v0→v1)
	 Point = PointOnLineSegmentNearestPoint( v0, v1, center );
	 LengthSq = (center - Point).LengthSq();
	 l  = LengthSq;
	 c = Point;

	 //辺２(v1→v2)
	 Point = PointOnLineSegmentNearestPoint( v1, v2, center );
	 LengthSq = (center - Point).LengthSq();
	 if(l>LengthSq) {
		 l = LengthSq;
		 c = Point;
	 }
	 
	 //辺３(v2→v0)
	 Point = PointOnLineSegmentNearestPoint( v2, v0, center );
	 LengthSq = (center - Point).LengthSq();
	 if(l>LengthSq) {
		 l = LengthSq;
		 c = Point;
	 }


	 l = sqrt(l);
	 //最短距離を確定
	 if(length) *length = l;
	 //最短地点を確定
	 if(cross) *cross = c;
	
    return (l<=radius);
}