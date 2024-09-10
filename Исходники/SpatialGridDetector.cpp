bool AABB::overlaps( const AABB& other ) const
{
  // Temporary sanity check: internal code shouldn't compare an AABB to itself
  assert( &other != this );

  // Attempt to find a separating axis
  if( ( this->max() < other.min() ).any() ) { return false; }
  if( ( other.max() < this->min() ).any() ) { return false; }

  // If no separating axis exists, the AABBs overlap
  return true;
}