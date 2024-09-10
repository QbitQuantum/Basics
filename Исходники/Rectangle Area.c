int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    int i=MAX(A,E),j=MAX(B,F),m=MIN(C,G),n=MIN(D,H),area=(D-B)*(C-A)+(H-F)*(G-E);
	if(i<m && j<n)
		area-=(n-j)*(m-i);
	return area;
}