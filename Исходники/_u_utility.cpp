IntegerVector get_superset_all_(CharacterVector x, List setlist){
  IntegerVector vec(setlist.length());
  int k=0;

  for (int i=0; i<setlist.length(); ++i){
		CharacterVector set=setlist[i];
		bool out = (any(is_na(match(x, set))));
		out = ! out;
		if (out)
			vec[k++] = i+1;
  }

	IntegerVector out = IntegerVector(k);
	if (k>0){
		for (int i=0; i<k; ++i)	out[i]=vec[i];
	}

	return out;
}