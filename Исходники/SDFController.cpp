	// pocitanie funkcie pre vsetky trojuholniky, O(n2)
	void CSDFController::Compute(LinkedList<Face>* triangles, Octree* root)
	{
		float min = FLOAT_MAX;
		float max = 0.0;
		
		unsigned int n_rays = 30;
		float angle = 120.0f;
		unsigned int counter = 0;

		//------------------prealocated variables------------------
		Vector4 tangens, normal, binormal;
		Mat4 t_mat;
		std::vector<float> rays;
		std::vector<float> weights;

		// precompute those N rays
		srand (123);											// initial seed for random number generator
		float* rndy = new float[n_rays];
		float* rndx = new float[n_rays];
		for(unsigned int i = 0; i < n_rays; i++)
		{
			rndy[i] = float(rand()%int(angle / 2));
			rndx[i] = float(rand()%(360));
			if(rndy[i] == 0.0)
				rndy[i] = 0.5;
		}

		float dist = FLOAT_MAX;
		float dist2 = FLOAT_MAX;
		float theta = 0.0f;
		bool intersected = false;

		LinkedList<Face>* face_list = NULL;
		LinkedList<Face>::Cell<Face>* intersected_face = NULL;
		//------------------prealocated variables------------------

		LinkedList<Face>::Cell<Face>* current_face = triangles->start;
		while(current_face != NULL)
		{
			// vypocet TNB vektorov a matice
			ComputeTNB(current_face->data, tangens, normal, binormal);
			t_mat = Mat4(tangens, normal, binormal);

			rays.clear();
			weights.clear();
			for(unsigned int i = 0; i < n_rays; i++)
			{
				Vector4 ray = CalcRayFromAngle(rndx[i], rndy[i]) * t_mat;
				ray.Normalize();

				dist = FLOAT_MAX;
				face_list = GetFaceList(triangles, root, current_face->data->center, ray);
				intersected_face = face_list->start;
				while(intersected_face != NULL)
				{
					if(current_face == intersected_face)
					{
						intersected_face = intersected_face->next;
						continue;
					}

					dist2 = FLOAT_MAX;
					intersected = rayIntersectsTriangle(current_face->data->center, ray, intersected_face->data->v[0]->P, intersected_face->data->v[1]->P, intersected_face->data->v[2]->P, dist2);
					if(intersected == true)
					{
						theta = acos( (ray * intersected_face->data->normal) / (ray.Length() * intersected_face->data->normal.Length()) );
						theta = theta * float(180.0 / M_PI);
						//loggger->logInfo(MarshalString("pridany ray s thetou: " + theta));
						if((theta < 90.0f) && (dist2 < dist))
							dist = dist2;
					}

					intersected_face = intersected_face->next;
				}
				if(dist < (FLOAT_MAX - 1.0f))
				{
					//loggger->logInfo(MarshalString("pridany ray s dlzkou: " + dist));
					rays.push_back(dist);
					weights.push_back(180.0f - rndy[i]);
				}
				//if(root != NULL)
					//delete face_list;						// generated list, bez prealokovania
			}
			if(rays.size() > 0)
			{
				current_face->data->ComputeSDFValue(rays, weights);
				if(current_face->data->diameter->value < min)
					min = current_face->data->diameter->value;
				if(current_face->data->diameter->value > max)
					max = current_face->data->diameter->value;
			}
			counter = counter + 1;
			current_face = current_face->next;
		}
		fc_list->Clear();
		oc_list->Clear();
		delete [] rndy;
		delete [] rndx;

		// postprocessing - smoothing and normalization
		//float kernel[] = {1.0,4.0,6.0,4.0,1.0};
		float* kernel = ComputeGaussianKernel(kernel_size);
		current_face = triangles->start;
		while(current_face != NULL)
		{
			Smooth(current_face->data, kernel, kernel_size);
			current_face->data->diameter->Normalize1(min, max, 4.0);
			current_face->data->diameter->Normalize2(0, max, 4.0);
			//tmp->data->diameter->Normalize2(0, diagonal, 4.0);

			current_face = current_face->next;
		}
		delete kernel;
	}