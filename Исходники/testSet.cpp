int main(void) {
	Set<int> a = { 1, 2, 3 };
	Set<int> b = { 2, 4, 6 };

	print("a: %v", &a);
	print("b: %v", &b);

	print("a ismember 3: %s", a.ismember(3) ? "OK" : "FAIL");

	Set<int> c;
	c = a | b;
	print("union: %v", &c);

	c = a & b;
	print("intersection: %v", &c);

	c = a - b;
	print("difference: %v", &c);

	c = a ^ b;
	print("symmetric difference: %v", &c);

	c = { 1, 2, 3 };
	print("eq: %s", (a == c) ? "OK" : "FAIL");
	c |= b;
	print("lt: %s", (a < c) ? "OK" : "FAIL");
	print("le: %s", (a <= c) ? "OK" : "FAIL");

	c = { 4, 5, 6 };
	print("disjoint: %s", a.isdisjoint(c) ? "OK" : "FAIL");

	a.remove(2);
	print("a.remove(2): %v", &a);

	while(len(b) > 0) {
		print("b.pop(): %d", b.pop());
	}

	del(a);
	print("del(a): %v len: %zu", &a, len(a));
	print("a.empty(): %s", a.empty() ? "OK" : "FAIL");
	print("operator!(): %s", (!a) ? "OK" : "FAIL");

	return 0;
}