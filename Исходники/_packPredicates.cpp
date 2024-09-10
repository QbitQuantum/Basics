	notInNotch(const Vector3r& _c, const Vector3r& _edge, const Vector3r& _normal, Real _aperture){
		c=_c;
		edge=_edge; edge.normalize();
		normal=_normal; normal-=edge*edge.dot(normal); normal.normalize();
		inside=edge.cross(normal);
		aperture=_aperture;
		// LOG_DEBUG("edge="<<edge<<", normal="<<normal<<", inside="<<inside<<", aperture="<<aperture);
	}