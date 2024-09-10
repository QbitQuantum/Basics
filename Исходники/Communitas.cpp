void Communitas::addParticle(ofPoint _pos, int _n) {
	if ( universe.inside( _pos ) ){
		timer = 0;

		int nLnk = 0;
		for (int i = pAct.size()-1; i >= 0 ; i--){
			if (nLnk == 0)
				if (pAct[i]->idN == _n)
					nLnk = i;

			if ( _pos.distance(pAct[i]->loc) <= 40)
				pAct[i]->alpha = 255;
		}

		LineDot * dot = new LineDot(_n, &universe, _pos ,false);

		if ( nLnk > 0) 
            dot->setLnk(pAct[nLnk]);

		pAct.push_back(dot);
	}
}