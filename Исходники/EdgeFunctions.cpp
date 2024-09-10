bool intersectEdges(Edge *a, Edge *b, Point *pi) {

	// resolver 'p + tr = q + us'
	// onde t = (q - p) x s / (r x s)
	// e    u = (q - p) x r / (r x s)
	Point P = a->Orig()->p;
	Point Q = b->Orig()->p;
	Point R = (a->Dest()->p) - P;
	Point S = (b->Dest()->p) - Q;

	Point QmP = Q - P;
	double QmPxS = QmP.cross(S);
	double QmPxR = QmP.cross(R);
	double RxS = R.cross(S);

	if (RxS != 0.0) {
		// as linhas se intersectam, vamos calcular se os segmentos tambem
		double t = QmPxS / RxS;
		double u = QmPxR / RxS;
		// se 0<=t<=1 e 0<=u<=1, os segmentos se encontram em 'p + tr = q + us'
		if ((t >= 0) && (t <= 1) && (u >= 0) && (u <= 1)) {
			int x = (int)(P.x + (t * R.x));
			int y = (int)(P.y + (t * R.y));
			*pi = Point(x,y);
			return true;
		}
	} else {
	//	 os segmentos sao colineares ou paralelos, vamos ignorar ;)
	}

	return false;
}