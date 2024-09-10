	void test01_shRotation() {
		/* Generate a random SH expansion, rotate it and 
		   spot-check 100 times against the original evaluated
		   at appropriately rotated positions */

		ref<Random> random = new Random();
		int bands = 8;

		SHVector vec1(bands);
		for (int l=0; l<bands; ++l)
			for (int m=-l; m<=l; ++m)
				vec1(l, m) = random->nextFloat();

		Vector axis(squareToSphere(Point2(random->nextFloat(), random->nextFloat())));
		Transform trafo = Transform::rotate(axis, random->nextFloat()*360);
		Transform inv = trafo.inverse();
		SHRotation rot(vec1.getBands());

		SHVector::rotation(trafo, rot);
		SHVector vec2(bands);

		rot(vec1, vec2);

		for (int i=0; i<100; ++i) {
			Vector dir1(squareToSphere(Point2(random->nextFloat(), random->nextFloat()))), dir2;
			trafo(dir1, dir2);

			Float value1 = vec1.eval(dir2);
			Float value2 = vec2.eval(dir1);
			assertEqualsEpsilon(value1, value2, Epsilon);
		}
	}