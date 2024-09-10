   static R3Vector calculate_sink_force(R3Scene* scene, R3Particle* particle)
   {
      R3ParticleSink* sink;
      R3Vector force = R3Vector(0,0,0);  
   	
      for (int i = 0; i < scene->NParticleSinks(); i++)
      {
         sink = scene->ParticleSink(i);
      	
         if (sink->shape->type == R3_SPHERE_SHAPE)
         {
            R3Sphere* sphere = sink->shape->sphere;
            R3Point center = sphere->Center();
            
            R3Vector f = -(particle->position - center);
            double d = f.Length() - sphere->Radius();
            f.Normalize();
         	
            double mag = sink->intensity / (sink->constant_attenuation + 
               						sink->linear_attenuation*d + 
               						sink->quadratic_attenuation*d*d);
            force += f*mag;
         }
         else if (sink->shape->type == R3_MESH_SHAPE)
      	{
      		R3Mesh* mesh = sink->shape->mesh;
      		R3Point center = R3Point(0,0,0);
      		for (unsigned int j = 0; j < mesh->vertices.size(); j++)
      		{
      			center += mesh->vertices[i]->position / mesh->vertices.size();
      		}
      		R3Vector f = -(particle->position - center);
            double d = f.Length();
            f.Normalize();
         	
            double mag = sink->intensity / (sink->constant_attenuation + 
               						sink->linear_attenuation*d + 
               						sink->quadratic_attenuation*d*d);
            force += f*mag;
      	}
      	else if (sink->shape->type == R3_BOX_SHAPE)
      	{
      		R3Box* box = sink->shape->box;
      		R3Point center = R3Point((box->XMax() - box->XMin())/2 + box->XMin(),
      										 (box->YMax() - box->YMin())/2 + box->YMin(),
      										 (box->ZMax() - box->ZMin())/2 + box->ZMin());
      		R3Vector f = -(particle->position - center);
            double d = f.Length();
            f.Normalize();
         	
            double mag = sink->intensity / (sink->constant_attenuation + 
               						sink->linear_attenuation*d + 
               						sink->quadratic_attenuation*d*d);
            force += f*mag;

      	}
      }
      return force;
   }