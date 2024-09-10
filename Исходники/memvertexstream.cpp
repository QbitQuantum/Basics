	void MemVertexstream::calcMinmax(math::Vector3f& minxyz,math::Vector3f& maxxyz)
	{
		Vertexiterator viterator(*this);

		minxyz=maxxyz=(viterator.position());

		for (ion_uint32 v=0;v<capacity();++v) {
			const math::Vector3f &vec=viterator.position();

			if (minxyz.x()>vec.x()) minxyz.x()=vec.x();
			if (minxyz.y()>vec.y()) minxyz.y()=vec.y();
			if (minxyz.z()>vec.z()) minxyz.z()=vec.z();

			if (maxxyz.x()<vec.x()) maxxyz.x()=vec.x();
			if (maxxyz.x()<vec.y()) maxxyz.y()=vec.y();
			if (maxxyz.x()<vec.z()) maxxyz.z()=vec.z();
		
			++viterator;
		}
	}