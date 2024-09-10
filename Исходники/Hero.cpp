void cute(){
	getpath();
	//for (int i=1;i<=sink;i++) printf("%d ",prev[i]);
	//printf("\n");
	int v=sink;
	while (v!=source){
		--dat[pree[v]];
		++dat[pree[v]^1];
		ans+=cost[pree[v]];
		v=prev[v];
	}
}