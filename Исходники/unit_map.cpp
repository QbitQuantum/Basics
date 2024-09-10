unit_map &unit_map::operator=(const unit_map &that)
{
	unit_map temp(that);
	swap(temp);
	return *this;
}