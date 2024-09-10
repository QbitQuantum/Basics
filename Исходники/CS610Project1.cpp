int _tmain(int argc, _TCHAR* argv[])
{
	LongInt* A = new LongInt();
	A->SetData("2222");

	LongInt* B = new LongInt();
	B->SetData("99999999");

	LongInt* C = new LongInt();
	C->SetData("246813575732");

	LongInt* D = new LongInt();
	D->SetData("180270361023456789");

	cout<<"A = "<<A->GetData()<<endl;
	cout<<"B = "<<B->GetData()<<endl;
	cout<<"C = "<<C->GetData()<<endl;
	cout<<"D = "<<D->GetData()<<endl<<endl;

	LongInt *E, *F, *G, *H, *I, *J, *K, *L, *M, *N;

	cout<<"E = A * D = "<<(E = A->Multi(D))->GetData()<<endl;
	cout<<"F = A^2 = "<<(F = A->Pow(2))->GetData()<<endl;
	cout<<"G = D^2 = "<<(G = D->Pow(2))->GetData()<<endl;
	cout<<"H = B * C = "<<(H = B->Multi(C))->GetData()<<endl;
	cout<<"I = A + D = "<<(I = A->Add(D))->GetData()<<endl;
	cout<<"J = I^2 = "<<(J = I->Pow(2))->GetData()<<endl;
	cout<<"K = J - F = "<<(K = J->Minus(F))->GetData()<<endl;
	cout<<"L = K - G = "<<(L = K->Minus(G))->GetData()<<endl;
	cout<<"M = L / E = "<<""<<endl;
	cout<<"N = E^5 = "<<(N = E->Pow(5))->GetData()<<endl;
	//cout<<"O = H^3 = "<<""<<endl;
	//cout<<"P = N - O = "<<""<<endl;
	//cout<<"Q = N^2 = "<<""<<endl;
	//cout<<"R = O^2 = "<<""<<endl;
	//cout<<"S = Q - R = "<<""<<endl;
	//cout<<"T = S / P = "<<""<<endl;
	//cout<<"U = T - O = "<<""<<endl;
	//cout<<"V = U - N = "<<""<<endl;
	//cout<<"W = C^2 = "<<""<<endl;
	//cout<<"X = B^2 = "<<""<<endl;
	//cout<<"Y = W - X = "<<""<<endl;
	//cout<<"Z = C + B = "<<""<<endl;
	//cout<<"H = Y / Z = "<<""<<endl;
	//cout<<"F = N^5 = "<<""<<endl;
	//cout<<"G = E^25 = "<<""<<endl;
	//cout<<"I = F / N = "<<""<<endl;
	//cout<<"J = G / I = "<<""<<endl;
	//cout<<"M = N^10 = "<<""<<endl;
	//cout<<"P = G^2 = "<<""<<endl;
	//cout<<"Q = P - M = "<<""<<endl;
	//cout<<"R = J - M = "<<""<<endl;

	getchar();
	return 0;
}