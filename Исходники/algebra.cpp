template <class T> const T& AbstractGroup<T>::Subtract(const Element &a, const Element &b) const
{
	// make copy of a in case Inverse() overwrites it
	Element a1(a);
	return Add(a1, Inverse(b));
}