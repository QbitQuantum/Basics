void QuickSort(std::vector<T> &vec)
{
	if (vec.empty()) return;
	srand(unsigned(time(NULL)));
	int idx = rand() % vec.size();
	swap(vec[idx], vec[vec.size() - 1]);
	QSort(vec, 0, vec.size() - 1);
}