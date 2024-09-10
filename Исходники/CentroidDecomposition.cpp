//fill(d, d + n, -1)
//decompose(0, -1, 0)
void decompose(int root, int parent, int level) {  
	find(root, -1, find(root, -1, INF));
	int c = centroid;
	par[c] = parent;
	d[c] = level;
	calc_in_component(centroid, -1, level);
	for(int to : g[c])
		if(d[to] == -1)
			decompose(to, c, level + 1);
}