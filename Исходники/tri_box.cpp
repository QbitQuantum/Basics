///
//	PointTriangleIntersection()
//
//		Test if 3D point is inside 3D triangle 
static
int PointTriangleIntersection(const vector3& p, const TRI& t)
{
	int		sign12,sign23,sign31;
	vector3 vect12,vect23,vect31,vect1h,vect2h,vect3h;
	vector3 cross12_1p,cross23_2p,cross31_3p;

	///
	//	First, a quick bounding-box test:                               
	//  If P is outside triangle bbox, there cannot be an intersection. 
	//
	if (p.x() > MAX3(t.m_P[0].x(), t.m_P[1].x(), t.m_P[2].x())) return(OUTSIDE);  
	if (p.y() > MAX3(t.m_P[0].y(), t.m_P[1].y(), t.m_P[2].y())) return(OUTSIDE);
	if (p.z() > MAX3(t.m_P[0].z(), t.m_P[1].z(), t.m_P[2].z())) return(OUTSIDE);
	if (p.x() < MIN3(t.m_P[0].x(), t.m_P[1].x(), t.m_P[2].x())) return(OUTSIDE);
	if (p.y() < MIN3(t.m_P[0].y(), t.m_P[1].y(), t.m_P[2].y())) return(OUTSIDE);
	if (p.z() < MIN3(t.m_P[0].z(), t.m_P[1].z(), t.m_P[2].z())) return(OUTSIDE);

	///
	//	For each triangle side, make a vector out of it by subtracting vertexes; 
	//	make another vector from one vertex to point P.                          
	//  The crossproduct of these two vectors is orthogonal to both and the      
	//  signs of its X,Y,Z components indicate whether P was to the inside or    
	//  to the outside of this triangle side.                                    
	//
	SUB(t.m_P[0], t.m_P[1], vect12);
	SUB(t.m_P[0], p,		  vect1h);	
	CROSS(vect12, vect1h, cross12_1p)
	sign12 = SIGN3(cross12_1p);      /* Extract X,Y,Z signs as 0..7 or 0...63 integer */

	SUB(t.m_P[1], t.m_P[2], vect23)
	SUB(t.m_P[1],    p, vect2h);
	CROSS(vect23, vect2h, cross23_2p)
	sign23 = SIGN3(cross23_2p);

	SUB(t.m_P[2], t.m_P[0], vect31)
	SUB(t.m_P[2],    p, vect3h);
	CROSS(vect31, vect3h, cross31_3p)
	sign31 = SIGN3(cross31_3p);

	///
	//	If all three crossproduct vectors agree in their component signs, /
	//  then the point must be inside all three.                           
	//  P cannot be OUTSIDE all three sides simultaneously.                
	//
	return (((sign12 & sign23 & sign31) == 0) ? OUTSIDE : INSIDE);
}