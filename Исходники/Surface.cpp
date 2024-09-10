void Surface::trans(Matrix4d& m, Matrix4d& inv) {
	_trans = true;
	_mInv = inv;
	_mTrans = m.inverse().transpose();
	_b = _b.transform(m);
}