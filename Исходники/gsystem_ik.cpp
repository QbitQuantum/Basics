bool GSystemIK::solveIK_dq(RMatrix &dq, std::vector<GBody*> pbodies_primary, std::vector<GBody*> pbodies_secondary, std::vector<Vec3> p_primary, std::vector<Vec3> p_secondary, std::vector<se3> V_primary, std::vector<se3> V_secondary, std::vector< std::vector<int> > idxC_primary, std::vector< std::vector<int> > idxC_secondary, std::vector<GCoordinate*> pcoords_prescribed, std::ofstream *pfout, gReal alpha_primary, gReal alpha_secondary)
{
	if ( pcoords_prescribed.size() == 0 ) {
		return solveIK_dq(dq, pbodies_primary, pbodies_secondary, p_primary, p_secondary, V_primary, V_secondary, idxC_primary, idxC_secondary, alpha_primary, alpha_secondary);
	}

	std::vector<GCoordinate*>::iterator viter_pcoord;
	std::list<GCoordinate*>::iterator iter_pcoord;
	RMatrix Jp, Js;		// Jacobian matrices for primary/secondary constraints
	RMatrix Vp, Vs;		// the righthand isde of the constraints

	if ( !buildConstrIK_dq(Jp, Vp, pbodies_primary, p_primary, V_primary, idxC_primary) ) return false;
	if ( !buildConstrIK_dq(Js, Vs, pbodies_secondary, p_secondary, V_secondary, idxC_secondary) ) return false;

	int num_prescribed = 0;
	std::vector<bool> b_prescribed;
	for (iter_pcoord = pCoordinates.begin(); iter_pcoord != pCoordinates.end(); iter_pcoord++) {
		if ( find(pcoords_prescribed.begin(), pcoords_prescribed.end(), *iter_pcoord) == pcoords_prescribed.end() ) {
			b_prescribed.push_back(false);
		} else {
			b_prescribed.push_back(true);
			num_prescribed++;
		}
	}

	std::vector<GCoordinate*> pcoords_all(pCoordinates.begin(), pCoordinates.end());
	int nx = getNumCoordinates() - num_prescribed;
	RMatrix Jp_(Jp.RowSize(), nx), Js_(Js.RowSize(), nx);
	RMatrix Vp_(Vp), Vs_(Vs);

	int cnt = 0;
	for (int i=0; i<getNumCoordinates(); i++) {
		if ( b_prescribed[i] ) {
			Vp_ -= pcoords_all[i]->dq * Jp.Sub(0, Jp.RowSize()-1, i, i);
			Vs_ -= pcoords_all[i]->dq * Js.Sub(0, Js.RowSize()-1, i, i);
		} else {
			Jp_.Push(0, cnt, Jp.Sub(0, Jp.RowSize()-1, i, i));
			Js_.Push(0, cnt, Js.Sub(0, Js.RowSize()-1, i, i));
			cnt++;
		}
	}

	RMatrix x;
	x.SetZero(nx,1);
	if ( Jp_.RowSize() > 0 ) {
		RMatrix x0, N;
		x0 = srInv(Jp_, N, alpha_primary) * Vp_;
		if ( Js_.RowSize() > 0 ) {
			x = x0 + N * ( srInv(Js_ * N, alpha_secondary) * (Vs_ - Js_ * x0) );
		} else {
			x = x0;
		}
	} else {
		if ( Js_.RowSize() > 0 ) {
			x = srInv(Js_, alpha_secondary) * Vs_;
		}
	}

	dq.ReSize(getNumCoordinates(), 1);
	cnt = 0;
	for (int i=0; i<getNumCoordinates(); i++) {
		if ( b_prescribed[i] ) {
			dq[i] = pcoords_all[i]->dq;
		} else {
			dq[i] = x[cnt++];
		}
	}

	if ( pfout != NULL ) {
		*pfout << "x = " << x << "Jp_ = " << Jp_ << "Js_ = " << Js_ << "Vp_ = " << Vp_ << "Vs_ = " << Vs_;
		*pfout << "Jp = " << Jp << "Js = " << Js << "Vp = " << Vp << "Vs = " << Vs;
		*pfout << "dq_prescribed = (";
		for (int i=0; i<(int)pcoords_prescribed.size(); i++) {
			*pfout << pcoords_prescribed[i]->dq << ", ";
		}
		*pfout << std::endl;
	}

	return true;
}