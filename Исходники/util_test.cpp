void render( int width, int height, Point campos, EulerRotation camangle, std::vector<SceneObject>& scenedesc, Bitmap& bmp) {
  double fov = 90;

  double factor = (double(height)/2)/tan(fov*M_PI/360.0);

  Vector lightdir = Vector(0.0,-2.0,-1.0);
  lightdir.normalize_l2();

  // Construct a ray for each pixel.
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {

      Color skycol(0x9E,0xE2,0xEA);

      Color col = skycol;

      // Sets up ray origin and direction in view space, 
      // image plane is at z = -1.
      Vector imagePlane;

      imagePlane[_X_] = (-double(width)/2 + j + 0.5)/factor;
      imagePlane[_Z_] = (-double(height)/2 + i + 0.5)/factor;
      imagePlane[_Y_] = -1;

      imagePlane = imagePlane.rotate(camangle);

      // TODO: Convert ray to world space and call 
      // shadeRay(ray) to generate pixel color.  
      
      Ray ray;
      // initialize ray and convert to world coords
      ray.origin = campos;
      ray.dir = imagePlane;
      ray.dir.normalize_l2();

      cast_ray( ray, scenedesc );

      double maxdist = 40;

      double occulddist = 0.1;

      if(ray.intersected) {
        Vector normal = -ray.gradient;
        normal.normalize_l2();

        double diffuse = fmax(normal.dot(-lightdir),0.0);

        Vector c = -(2.0 * normal.dot(lightdir) * normal - lightdir);

        double specular = fmax(ray.dir.dot(c),0.0);
        specular = pow(specular,10.0);

        // only cast if diffuse is nonzero
        // if(diffuse!=0){
        //   Ray lightray;
        //   lightray.origin = ray.intsec;// - 0.1*normal;
        //   lightray.dir = lightdir;
        //   cast_ray(lightray, scenedesc);

        //   if(lightray.intersected){
        //     diffuse = 0;
        //     specular = 0;
        //   }// } else {
        //   //   double umbra = clamp(8*lightray.mindist, 0, 1);
        //   //   diffuse *= umbra;
        //   //   specular *= umbra;
        //   // }
        // }


        // Vector normal2 = (2.0*normal/normal.linf() + Vector(1.0,1.0,1.0))/2.0;
        // Color normalcol;
        // normalcol[0] = normal2[0];
        // normalcol[1] = normal2[1];
        // normalcol[2] = normal2[2];

        // double ambient = fmax(f(ray.intsec - occulddist*normal) / occulddist, 0.0);
        // ambient = 1-pow(1-ambient,2.0);

        //only apply ambient when diffuse is low
        // ambient = fmax(ambient,diffuse);

        // col = ambient*0.1*Color(0.7,0.65,0.6) + diffuse*0.8 * Color(0.7,0.65,0.6) + 
          // pow(specular,50.0)*0.5 * Color(1.0,1.0,1.0);


        col = diffuse*Color(0.6,0.6,0.6) + specular*Color(1.0,1.0,1.0);

        double fog = (ray.intsec-campos).l2()/maxdist;
        fog = 1-pow(1-fog,2.0);

        col = fog * skycol + (1-fog) * col;

      }
      double sun = pow(fmax(ray.dir.dot(lightdir),0.0),200);
      col = col + sun*Color(1.0,1.0,0.8);

      col.clamp();
      bmp(i,j) = col;

      if(j%100 == 0){
        int percent = 100.0*(1.0*i*width + j) / (height*width);
        std::cerr << "\r"<< std::setw(3) << std::setfill('0') << percent << "% completed: ";

        std::cerr  << std::string(percent/2, '|');

        std::cerr.flush();
      }
    }
  }
}