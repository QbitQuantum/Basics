void RadianceTexture() {

   // Loop over the rows and columns of the image and evaluate radiance and
   // covariance per pixel using Monte-Carlo.
   #pragma omp parallel for schedule(dynamic, 1)
   for (int y=0; y<height; y++){
      Random rng(y + height*clock());

      for (int x=0; x<width; x++) {
         int i=(width-x-1)*height+y;

         // Create the RNG and get the sub-pixel sample
         float dx = rng();
         float dy = rng();

         // Generate the pixel direction
         Vector d = cx*((dx + x)/float(width)  - .5) +
                    cy*((dy + y)/float(height) - .5) + cam.d;
         d.Normalize();

         Ray ray(cam.o, d);
         Vector radiance = Radiance(spheres, ray, rng, 0, 1);

         bcg_img[i] = (float(nPasses)*bcg_img[i] + Vector::Dot(radiance, Vector(1,1,1))/3.0f) / float(nPasses+1);
      }
   }

   ++nPasses;
}