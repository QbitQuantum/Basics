int main(){
	int n;
	axisX = Line(Vector(0, 0), Vector(1, 0));
	while (scanf("%d", &n) == 1 && n){
		scanf("%lf%lf", &light.x, &light.y);
		for (int i = 0; i < n; i++)
			scanf("%lf%lf%lf", &cir[i].center.x, &cir[i].center.y, &cir[i].r);
		for (int i = 0; i < n; i++){
			if (cir[i].r == 0)	continue;
			double d = light.distance(cir[i].center);
			double theta = asin(cir[i].r / d);
			Line a = Line(light, (cir[i].center - light).leftRotate(-theta) + light);
			Line b = Line(light, (cir[i].center - light).leftRotate(theta) + light);
			Vector u, v;
			a.intersect(axisX, u);
			b.intersect(axisX, v);
			seg[i] = Segment(u.x, v.x);
		}
		sort(seg, seg + n, cmp);
		Segment ans = seg[0];
		for (int i = 1; i < n; i++){
			if (cir[i].r == 0)	continue;
			if (sign(seg[i].L - ans.R) > 0){
				print(ans);
				ans = seg[i];
			}
			else
				ans.R = max(ans.R, seg[i].R);
		}
		print(ans);
		putchar('\n');
	}
	return 0;
}