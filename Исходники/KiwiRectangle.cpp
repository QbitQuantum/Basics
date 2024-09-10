 bool Rectangle::intersects(Segment const& segment) const noexcept
 {
     return (segment.intersects(Segment(topLeft(),    topRight()))    ||
             segment.intersects(Segment(topRight(),   bottomRight())) ||
             segment.intersects(Segment(bottomLeft(), bottomRight())) ||
             segment.intersects(Segment(topLeft(),    bottomLeft())));
 }