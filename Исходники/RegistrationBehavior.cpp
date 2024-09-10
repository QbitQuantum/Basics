 double GetIntention(const vctFrm3 & cursorPosition) const {
     vct3 difference;
     difference.DifferenceOf(cursorPosition.Translation(), this->GetAbsoluteTransformation().Translation());
     double distance = difference.Norm();
     const double threshold = 5.0;  // in mm
     if (distance > threshold) {
         return 0.0;
     } else {
         return (1.0 - (distance / threshold));  // normalized between 0 and 1
     }
 }