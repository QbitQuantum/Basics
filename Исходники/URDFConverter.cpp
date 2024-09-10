void URDFLinkNode::GetGeometryProperty(bool useVisGeom){
	if(!this->link){
		cout<<"link is NULL!"<<endl;
		return;
	}
	geomScale.setIdentity();
	geomPrimitive = false;
	std::shared_ptr<urdf::Geometry> geom;
	if(useVisGeom && this->link->visual) geom = this->link->visual->geometry;
	else if(!useVisGeom && this->link->collision) geom = this->link->collision->geometry;
	if(geom){
	  if(geom->type == urdf::Geometry::BOX){
		  std::shared_ptr<urdf::Box> box = std::static_pointer_cast<urdf::Box>(geom);
		  geomPrimitive = true;
		  AABB3D b;
		  b.bmin.set(-box->dim.x*0.5,-box->dim.y*0.5,-box->dim.z*0.5);
		  b.bmax = -b.bmin;
		  GeometricPrimitive3D prim(b);
		  AnyGeometry3D geom(prim);
		  stringstream ss;
		  geom.Save(ss);
		  geomData = ss.str();

		}else if(geom->type == urdf::Geometry::CYLINDER){
		  	std::shared_ptr<urdf::Cylinder> cylinder = std::static_pointer_cast<urdf::Cylinder>(geom);
		  	geomPrimitive = true;
			Cylinder3D c;
			c.center.setZero();
			c.axis.set(0,0,1);
			c.radius = cylinder->radius;
			c.height = cylinder->length;
			GeometricPrimitive3D prim(c);
			AnyGeometry3D geom(prim);
		  	stringstream ss;
		  	geom.Save(ss);
		  	geomData = ss.str();
		}else if(geom->type == urdf::Geometry::SPHERE){
			std::shared_ptr<urdf::Sphere> sphere = std::static_pointer_cast<urdf::Sphere>(geom);
			geomPrimitive = true;
			Sphere3D s;
			s.center.setZero();
			s.radius = sphere->radius;
			GeometricPrimitive3D prim(s);
			AnyGeometry3D geom(prim);
		  	stringstream ss;
		  	geom.Save(ss);
		  	geomData = ss.str();
		}
	  else if(geom->type == urdf::Geometry::MESH){
			std::shared_ptr<urdf::Mesh> mesh = std::static_pointer_cast<urdf::Mesh>(geom);
			geomName = mesh->filename.c_str();
			if(geomName.compare(0,10,"package://")==0) {
			  //take off the first 10 characters
			  geomName = URDFConverter::packageRootPath + "/" + geomName.substr(10,string::npos);
			}
			geomScale(0,0) = mesh->scale.x;
			geomScale(1,1) = mesh->scale.y;
			geomScale(2,2) = mesh->scale.z;
			if(URDFConverter::flipYZ) {
			  Matrix4 Ryz; 
			  Ryz.setZero();
			  Ryz(0,0) = 1;
			  Ryz(1,2) = -1;
			  Ryz(2,1) = 1;
			  Ryz(3,3) = 1;
			  geomScale = geomScale * Ryz;
			}
		}
	  else {
	    cout<<"Unknown URDF geometry type "<<(int)geom->type<<endl;
	  }
	}else{
		geomName = "";
		geomScale.setIdentity();
	}
}