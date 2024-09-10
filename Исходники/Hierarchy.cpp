/// Finds <tt>contour</tt>'s parent given another contour <tt>ancestor</tt>
/// that is guaranteed to contain <tt>contour</tt>.
const Contour_handle Hierarchy::find_parent(Contour_handle contour, Contour_handle ancestor) const
{
  // Call find_parent with one of the vertices
  Point_2 point = *(contour->polygon().vertices_begin());
  return find_parent(point, ancestor);
}