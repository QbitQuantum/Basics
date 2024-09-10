void RAS_CalcTexMatrix(RAS_TexVert p[3],MT_Point3& origin,MT_Vector3& udir,MT_Vector3& vdir)
{
// precondition: 3 vertices are non-colinear

	MT_Vector3 vec1 = p[1].xyz()-p[0].xyz();
	MT_Vector3 vec2 = p[2].xyz()-p[0].xyz();
	MT_Vector3 normal = vec1.cross(vec2);
	normal.normalize();

	// determine which coordinate we drop, ie. max coordinate in the normal
	

	int ZCOORD = normal.closestAxis();
	int XCOORD = (ZCOORD+1)%3;
	int YCOORD = (ZCOORD+2)%3;
		
	// ax+by+cz+d=0
	MT_Scalar d = -p[0].xyz().dot(normal);
	

	MT_Matrix3x3 mat3(	p[0].getUV1()[0],p[0].getUV1()[1],	1,
						p[1].getUV1()[0],p[1].getUV1()[1],	1,
						p[2].getUV1()[0],p[2].getUV1()[1],	1);


	MT_Matrix3x3 mat3inv = mat3.inverse();

	MT_Vector3 p123x(p[0].xyz()[XCOORD],p[1].xyz()[XCOORD],p[2].xyz()[XCOORD]);
	MT_Vector3 resultx = mat3inv*p123x;
	MT_Vector3 p123y(p[0].xyz()[YCOORD],p[1].xyz()[YCOORD],p[2].xyz()[YCOORD]);
	MT_Vector3 resulty = mat3inv*p123y;

	// normal[ZCOORD] is not zero, because it's chosen to be maximal (absolute), and normal has length 1, 
	// so at least on of the coords is <> 0

	//droppedvalue udir.dot(normal) =0
	MT_Scalar droppedu = -(resultx.x()*normal[XCOORD]+resulty.x()*normal[YCOORD])/normal[ZCOORD];
	udir[XCOORD] = resultx.x();
	udir[YCOORD] = resulty.x();
	udir[ZCOORD] = droppedu;
	MT_Scalar droppedv = -(resultx.y()*normal[XCOORD]+resulty.y()*normal[YCOORD])/normal[ZCOORD];
	vdir[XCOORD] = resultx.y();
	vdir[YCOORD] = resulty.y();
	vdir[ZCOORD] = droppedv;
	// droppedvalue b = -(ax+cz+d)/y;
	MT_Scalar droppedvalue = -((resultx.z()*normal[XCOORD] + resulty.z()*normal[YCOORD]+d))/normal[ZCOORD];
	origin[XCOORD] = resultx.z();
	origin[YCOORD] = resulty.z();
	origin[ZCOORD] = droppedvalue;
	

}