int Interset(IntervalVector x, IntervalVector y) {
assert(x.size() == y.size());
int res = 2;
int i;
for(i = 0;i<x.size();i++) {
	if (!x[i].is_subset(y[i])) {
		res = 1;
		break;}
	}
while(i<x.size()) {
    if(!x.intersects(y)) {
		res = 0;
		return res;
	}
	i++;}
return res;}