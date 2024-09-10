bool UnitSquare::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSquare, which is
	// defined on the xy-plane, with vertices (0.5, 0.5, 0), 
	// (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
	// (0, 0, 1).
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.

	Ray3D r;
	r.origin = worldToModel * ray.origin;
	r.dir = worldToModel * ray.dir;

	double t = -r.origin[2] / r.dir[2];
	if (t <= 0) return false;

	double xint = r.origin[0] + t * r.dir[0];
	double yint = r.origin[1] + t * r.dir[1];

	if ((xint >= -0.5) && (xint <= 0.5) && (yint >= -0.5) && (yint <= 0.5)){
		if (ray.intersection.none || t < ray.intersection.t_value) {

			Vector3D n(0,0,1);
			Point3D i(xint, yint, 0.0);

			ray.intersection.t_value = t;
			ray.intersection.point = modelToWorld * i;
			ray.intersection.normal = worldToModel.transpose() * n;
			ray.intersection.none = false;
			return true;

		}
	}	

	return false;
}