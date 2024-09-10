IGL_INLINE void igl::copyleft::cgal::assign_scalar(
  const typename CGAL::Epeck::FT & _cgal,
  float& d)
{
  // FORCE evaluation of the exact type otherwise interval might be huge.
  const typename CGAL::Epeck::FT cgal = _cgal.exact();
  const auto interval = CGAL::to_interval(cgal);
  d = interval.first;
  do {
      const float next = nextafter(d, interval.second);
      if (CGAL::abs(cgal-d) < CGAL::abs(cgal-next)) break;
      d = next;
  } while (d < interval.second);
}