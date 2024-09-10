void Tri3::GetStiffnessMatrix(Matrix<FEdouble>* S)
{
	Node* node1 = _model->GetNode(_node1);
	Node* node2 = _model->GetNode(_node2);
	Node* node3 = _model->GetNode(_node3);
	Matrix<FEdouble>* Fe = new Matrix<FEdouble>(3,6);
	(*Fe)(0,0) = (*Fe)(2,1) = node2->GetY()-node3->GetY();
	(*Fe)(2,0) = (*Fe)(1,1) = -(node2->GetX()-node3->GetX());
	(*Fe)(0,2) = (*Fe)(2,3) = node3->GetY()-node1->GetY();
	(*Fe)(2,2) = (*Fe)(1,3) = -(node3->GetX()-node1->GetX());
	(*Fe)(0,4) = (*Fe)(2,5) = node1->GetY()-node2->GetY();
	(*Fe)(2,4) = (*Fe)(1,5) = -(node1->GetX()-node2->GetX());

	FEdouble F = 0.5*static_cast<FEdouble>(fabs(
		node1->GetX()*(node2->GetY()-node3->GetY())+
		node2->GetX()*(node3->GetY()-node1->GetY())+
		node3->GetX()*(node1->GetY()-node2->GetY())
		));

	(*Fe)*=1/(2*F);

	Material* mat = _model->GetMaterial(_mat);

	FEdouble D = mat->GetEmodul()*_thickness/(1-(mat->GetNue()*mat->GetNue()));

	Matrix<FEdouble>* E = new Matrix<FEdouble>(3);
	(*E)(0,0) = (*E)(1,1) = D;
	(*E)(1,0) = (*E)(0,1) = D*mat->GetNue();
	(*E)(2,2) = 0.5*D*(1-mat->GetNue());

	Matrix<FEdouble> K = (*E)*(*Fe);
	Fe->Transpose();

	(*S) = (*Fe)*K;
	(*S)*=F;
	
}