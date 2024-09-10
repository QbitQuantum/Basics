float
example_state_view::
pointer_radius(int index, bool old) const
noexcept
{
	using std::sqrt;
	using std::pow;
	return float(sqrt(
		pow(ndc_pointer_x(index, old), 2)+
		pow(ndc_pointer_y(index, old), 2)
	));
}