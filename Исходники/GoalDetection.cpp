// Finds the distance to post
// Tunes the BBox using higher resolution foveas
RRCoord GoalDetection::findDistanceToPost(VisionFrame &frame,
                                          const Fovea& fovea,
                                          BBox& goal,
                                          int numPosts,
                                          PostInfo& p) {

   bool trustDistance = true;
   float differenceThreshold = 1.7;

   // **** Try finding the distance using kinematics of the base ****
   findBaseOfPost(frame, goal);

   const CameraToRR *convRR = &frame.cameraToRR;
   Point base = Point((goal.a.x()+goal.b.x())/2, goal.b.y());
   RRCoord rr = convRR->convertToRR(base, false);
   float kdistance = rr.distance();
   
   // **** Try using the width the find the distance ****
   // Calculate width distance at 3 points and take median
   std::map<float, float> distances;
   for (float h = 0.89; h < 1; h += 0.05) {
      float d = widthDistanceToPost(frame, goal, h);
      distances.insert(std::make_pair(d,h));
   }
   std::map<float, float>::iterator i = distances.begin();
   if (distances.size() > 1) ++i;
   float wdistance = widthDistanceToPost(frame, goal, i->second, true);

   // **** Decide which distance to use ****
   // Kinematics is usually more accurate, so use it unless we know it's wrong

   // If post ends at bottom of image, probably not the bottom, so use width
   bool width = false;
   if (fovea.top && goal.b.y() > (TOP_IMAGE_ROWS-10)) {
      width = true;
   }

   // If still yellow below the base, probably missed the bottom, so use width
   // Only for 1 post though
   if (numPosts == 1) {
      Point fTop = fovea.mapImageToFovea(goal.a);
      Point fBot = fovea.mapImageToFovea(goal.b);
      const YHistogram &yhistogram = fovea.yhistogram;
      int height = (fBot.y() - fTop.y()) / 4; // set max scan size
      int endPoint = std::min(fovea.bb.height(), fBot.y() + height);
      int noYellow = fBot.y();

      for (int i = fBot.y(); i < endPoint; ++i) {
         int current = yhistogram._counts[i][cGOAL_YELLOW];
         if (current < 10) noYellow = i;
      }
      if (noYellow == fBot.y()) trustDistance = false;
   }
   
   // Decided to use width distance
   if (width) {
      if (wdistance < 1500) rr.distance() = wdistance;
      else trustDistance = false;
//      differenceThreshold = 1.7;
   }

   // Check that kinematics and width distances are similar
   else if (kdistance < 2500) {
   }

   else if (((kdistance / wdistance) > differenceThreshold) ||
       ((wdistance / kdistance) > differenceThreshold)) {
      trustDistance = false;
   }

   // Check distance is reasonable
   if (rr.distance() > 12000) {
      trustDistance = false;
      rr.distance() = 12000;
   }

   // Set variables in PostInfo
   p.rr = rr;
   p.kDistance = kdistance;
   p.wDistance = wdistance;
   p.trustDistance = trustDistance;
   p.imageCoords = goal;

   return rr;
}