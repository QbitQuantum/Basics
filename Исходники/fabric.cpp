void Fabric::outputPointCloud( const char* file ){

  ofstream out( file );
  if( !out.is_open() ) return;

  for( int i=0; i < particles.size(); i++ ){
    
    Particle *x,*y;
    if( particles[i]->links.size() < 2 ) continue;
    x = particles[i]->links[0]->p2;
    y = particles[i]->links[1]->p2;
    Vec3f l = particles[i]->pos;
    Vec3f r = x->pos; 
    
    for( int j=0; j < 20; j++){

      Vec3f tmp = l; 
      for( int d=0; d < 20; d++){ //(int)1000*distance; j++ ){

        float s = .0015f;
        float s2 = s * sqrt(2.0);

        out << tmp.x << " " << tmp.y << " " << tmp.z+s << " 0 0 1" << endl;
        out << tmp.x << " " << tmp.y << " " << tmp.z-s << " 0 0 -1" << endl;
        out << tmp.x << " " << tmp.y+s << " " << tmp.z << " 0 1 0" << endl;
        out << tmp.x << " " << tmp.y-s << " " << tmp.z << " 0 -1 0" << endl;
        out << tmp.x+s << " " << tmp.y << " " << tmp.z << " 1 0 0" << endl;
        out << tmp.x-s << " " << tmp.y << " " << tmp.z << " -1 0 0" << endl;
        tmp.lerp( r , .05f); //distance / 1000.0f );

      }
      l.lerp( y->pos, .05f );
      r.lerp( x->links.back()->p2->pos, .05f );
    }
  }

}