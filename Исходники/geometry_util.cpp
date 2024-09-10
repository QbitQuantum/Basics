 double DistanceFromLineSegment(
     const tf::Vector3& line_start,
     const tf::Vector3& line_end,
     const tf::Vector3& point)
 {    
   return point.distance(ProjectToLineSegment(line_start, line_end, point));
 }