		void ransac3Dplane_distance(
			const CMatrixTemplateNumeric<T> &allData,
			const vector< CMatrixTemplateNumeric<T> > & testModels,
			const T distanceThreshold,
			unsigned int & out_bestModelIndex,
			vector_size_t & out_inlierIndices )
		{
			ASSERT_( testModels.size()==1 )
			out_bestModelIndex = 0;
			const CMatrixTemplateNumeric<T> &M = testModels[0];

			ASSERT_( size(M,1)==1 && size(M,2)==4 )

			TPlane  plane;
			plane.coefs[0] = M(0,0);
			plane.coefs[1] = M(0,1);
			plane.coefs[2] = M(0,2);
			plane.coefs[3] = M(0,3);

			const size_t N = size(allData,2);
			out_inlierIndices.clear();
			out_inlierIndices.reserve(100);
			for (size_t i=0;i<N;i++)
			{
				const double d = plane.distance( TPoint3D( allData.get_unsafe(0,i),allData.get_unsafe(1,i),allData.get_unsafe(2,i) ) );
				if (d<distanceThreshold)
					out_inlierIndices.push_back(i);
			}
		}