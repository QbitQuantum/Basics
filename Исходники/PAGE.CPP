int main(){
	Macro();
	int n;for (scanf("%d", &n); n; n--) {
		char c;	Point_3 p;
		scanf("\n%c%lf%lf%lf", &c, &p.x, &p.y, &p.z);
		if (c == 'T') Translation(p);	if (c == 'S') Scaling(p);
		if (c == 'R') {	double r;scanf("%lf\n", &r);
			Rotate(p, r);	//===========绕OP逆时针旋转r角度
        }}
	for (scanf("%d", &n); n; n--) {
		Point_3 p, p2;	scanf("%lf%lf%lf", &p.x, &p.y, &p.z);
		p2 = opt(p); 	printf(“%f %f %f\n”,p2.x,p2.y,p2.z);
    }
}