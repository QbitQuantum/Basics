 TEST(HitPointInterval, ShouldReturnUndefinedFarthestHitPointOnEmptyInterval) {
   HitPointInterval interval;
   const HitPoint& i = interval.max();
   ASSERT_TRUE(i == HitPoint::undefined());
 }