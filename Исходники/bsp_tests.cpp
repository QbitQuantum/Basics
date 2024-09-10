static int getInt(int min, int max) {
	if (min > max) std::swap(min, max);
	return randomizer.rand(min, max + 1);
}