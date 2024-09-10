 BOOST_FOREACH (Contour_handle contour, contours) {
   if (contour->info().object_name() == o.component) {
     ccents.push_back(centroid(contour->polygon()));
   }
 }