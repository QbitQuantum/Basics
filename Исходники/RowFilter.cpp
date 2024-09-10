RowFilter::Comparison RowFilter::getComparison(const std::string& comp) const
{
	Comparisons::const_iterator it = _comparisons.find(toUpper(comp));
	if (it == _comparisons.end())
		throw NotFoundException("Comparison not found", comp);

	return it->second;
}