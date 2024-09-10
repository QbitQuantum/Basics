// define adjacency rules
//
void MyGlWindow::define_adjacency_rules( std::vector< std::pair< std::pair<int,int>, std::pair<int,int> > > &rules )
{
	rules.clear();

	for (int i=0;i<SM_Size();i++) {

		corres c_i = SM_Get(i);

		EdgePlane line_i = _camera->fromWorldFrameToCameraFrame( c_i.line );

		for (int j=0;j<SM_Size();j++) {

			if ( i == j )
				continue;

			corres c_j = SM_Get(j);
		
			EdgePlane line_j = _camera->fromWorldFrameToCameraFrame( c_j.line );

			if ( line_i.angle( line_j ) > SPHERE_TESSELLATION_RESOLUTION )
				continue;

			if ( line_i.overlap( line_j ) < EPS && line_j.overlap( line_i ) < EPS )
				continue;

			Vec3d n1 = line_i._normal;
			Vec3d n2 = line_j._normal;

			Vec3d n = cross(n1,n2);
			if ( len(n) < EPS )
				continue;

			n = norm(n);

			double angle_i_j = Acos(dot(n1,n2));
			
			if ( M_PI - angle_i_j < angle_i_j ) {
				n2 = -n2;
				angle_i_j = M_PI - angle_i_j;
			}

			if ( dot(n,cross(n1,n2)) < 0)
				angle_i_j = - angle_i_j;

			for (int ii = 0; ii < c_i.eps.size(); ii++) {

				Vec3d n_i = c_i.eps[ii]._normal;

				double best_score = M_PI;

				int best_jj = -1;

				for (int jj=0;jj < c_j.eps.size(); jj++) {

					Vec3d n_j = c_j.eps[jj]._normal;

					double angle_ii_jj = Acos(dot(n_i,n_j));
					
					if ( M_PI - angle_ii_jj < angle_ii_jj ) {
						n_j = -n_j;
						angle_ii_jj = M_PI - angle_ii_jj;
					}

					if ( dot(n,cross(n_i,n_j)) < 0)
						angle_ii_jj = - angle_ii_jj;
					
					double score = angle_ii_jj*angle_i_j > 0 ? fabs(angle_ii_jj - angle_i_j) : M_PI;

					if ( score < best_score ) {

						best_score = score;
						best_jj = jj;
					}
				}

				if ( best_jj == -1 )
					continue;

				std::pair<int, int> p1;
				p1.first = i;
				p1.second = ii;
				std::pair<int, int> p2;
				p2.first = j;
				p2.second = best_jj;

				std::pair< std::pair<int,int>, std::pair<int,int> > element;
				element.first = p1;
				element.second = p2;
	
				rules.push_back( element );
			}
		}
	}

	// mutual consistency check
	std::vector< std::pair< std::pair<int,int>, std::pair<int,int> > > consistent_rules;

	for (std::vector< std::pair< std::pair<int,int>, std::pair<int,int> > >::iterator iter = rules.begin(); iter != rules.end(); iter++) {

		bool ok = false;

		for (std::vector< std::pair< std::pair<int,int>, std::pair<int,int> > >::iterator iter2 = rules.begin(); iter2 != rules.end(); iter2++) {

			if ( iter2->first.first == iter->second.first && iter2->first.second == iter->second.second && 
				iter2->second.first == iter->first.first && iter2->second.second == iter->first.second ) {
				ok = true;
				break;
			}
		}

		if ( ok ) {

			std::pair< std::pair<int,int>, std::pair<int,int> > element = *iter;

			std::pair< std::pair<int,int>, std::pair<int,int> > transpose;

			transpose.first.first = element.second.first;
			transpose.first.second = element.second.second;
			transpose.second.first = element.first.first;
			transpose.second.second = element.first.second;

			consistent_rules.push_back( element );
		
			LOG(LEVEL_INFO, "introducing pair (%d,%d) (%d,%d)", element.first.first, element.first.second, element.second.first, element.second.second );
		}
	}

	rules.clear();

	rules = consistent_rules;

	LOG(LEVEL_INFO, "rules done");
}