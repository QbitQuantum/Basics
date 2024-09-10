void RunTimeStep(T* mSys, const int frame) {

	if (frame % 100 == 0 && frame * timestep < 20) {
		for (int i = 0; i < 40; i++) {
			CreateFiber(mSys, Vector(2 - 1.6 * 0, 3, i / 8.0));
			CreateFiber(mSys, Vector(2 - 1.6 * 1, 3, i / 8.0));
			CreateFiber(mSys, Vector(2 - 1.6 * 2, 3, i / 8.0));
			CreateFiber(mSys, Vector(2 - 1.6 * 3, 3, i / 8.0));
			fibers += 4;
		}
		cout << "Fibers: " << fibers << endl;
	}
}