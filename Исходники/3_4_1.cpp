void rosette(int N, float radius)
{
	GLPoint *pointlist = new GLPoint[N];
	GLfloat theta = (2.0f * PI) / N;
	GLfloat angle = theta / 2;
	for (int c = 0; c < N; c++) {
		pointlist[c].set(radius*sin(theta*c), radius*cos(theta*c));
	}

	for (int i = 0; i < N-1; i++) {
		moveTo(pointlist[i]);
		lineTo(pointlist[i+1]);
	}
	lineTo(pointlist[0]);
}