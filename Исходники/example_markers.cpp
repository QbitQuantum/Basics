void Example_markers::on_marker_facing_changed(Papyrus::MarkerPosition which, Papyrus::Marker::Facing facing)
{
  m_line->marker(which)->set_facing(facing);
}