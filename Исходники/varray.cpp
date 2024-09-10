void CMVArray::Set(int row,int col,const CMString& str)
{
	if (row>=0 && row<_nrows && col>=0 && col<_ncols) {
		size_t index = row*_ncols + col;
		if (isnumber(str.c_str())) {
			double d = _wtof(str.c_str());
			array[index].e = NULL;
			array[index].dVal = d;
		}
		else {
			CMExpression* e = new CMExpression(str.c_str());
			if (e->IsPolynomial()) arraystate |= containsPolynomials;
			if (e->Fail()) {
				SetState(vsFailed, 1);
				ReportError(XBadVardef, e->GetString());
			}
			array[index].e = e;
		}
		/*
		CMExpression* e = new CMExpression(str.c_str());
		if (e->IsPolynomial()) arraystate |= containsPolynomials;
		if (e->Fail()) {
  		 	SetState(vsFailed,1);
   			ReportError(XBadVardef,e->GetString());
	   }
	   array.AddAt((long)row*ncols+col,e);
	   */
	}
}