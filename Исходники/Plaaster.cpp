int Plaaster::shoot(Vec3f pos)
{
	int count=0;
    for (int i=0;i< triangles.size();i++)
    {
        if (triangles[i]->center.x > pos.x -70 && triangles[i]->center.x < pos.x +70  )
        {
            if (triangles[i]->center.z > pos.y -70 && triangles[i]->center.z < pos.y +70  )
            {
                
              
                Vec2f a = Vec2f(triangles[i]->center.x ,triangles[i]->center.z);
                float dist =a.distance(Vec2f(pos.x,pos.y ));
                Vec2f dir =a-Vec2f(pos.x,pos.y );
                dir.normalize();
                
               //if (dist < 70)
                {
                    count ++;
                    
                    
                PlaasterParticle *p = triangles[i]->particle;
                    p->reset(100-dist ,dir);
                particles.push_back(p);
                
            triangles.erase(triangles.begin()+i );
            //    cinder::app::console()<< "delete";
                }
            i--;
            }
        }
    
    }
    //cinder::app::console()<< count <<endl; ;
    updateMainMesh();
	
	return count;

}