inline boost::math::concepts::std_real_concept fmod(boost::math::concepts::std_real_concept a, boost::math::concepts::std_real_concept b)
{ return fmodl(a.value(), b.value()); }