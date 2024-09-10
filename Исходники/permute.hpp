 void invData(Images& images) const override {
     ColorVal pixel[5];
     for (Image& image : images) {
       for (int p=0; p<ranges->numPlanes(); p++) image.undo_make_constant_plane(p);
       for (uint32_t r=0; r<image.rows(); r++) {
         for (uint32_t c=0; c<image.cols(); c++) {
             for (int p=0; p<ranges->numPlanes(); p++) pixel[p] = image(p,r,c);
             for (int p=0; p<ranges->numPlanes(); p++) image.set(permutation[p],r,c, pixel[p]);
             image.set(permutation[0],r,c, pixel[0]);
             if (!subtract) { for (int p=1; p<ranges->numPlanes(); p++) image.set(permutation[p],r,c, pixel[p]); }
             else { for (int p=1; p<3 && p<ranges->numPlanes(); p++) image.set(permutation[p],r,c, CLAMP(pixel[p] + pixel[0], ranges->min(permutation[p]), ranges->max(permutation[p])));
                    for (int p=3; p<ranges->numPlanes(); p++) image.set(permutation[p],r,c, pixel[p]); }
         }
       }
     }
 }