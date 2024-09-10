double GetPsi(float R, float Z, eavlDataSet *psiMesh)
{
    double psi = -1.0;

    eavlCellSet *cells = psiMesh->GetCellSet(0);
    int nCells = cells->GetNumCells();
    
    //psiMesh->PrintSummary(cout);
    eavlField *Rf = psiMesh->GetField("xcoords");
    eavlField *Zf = psiMesh->GetField("ycoords");
    eavlField *psiF = psiMesh->GetField("psi");

    int cellIdx = -1;
    for (int i = 0; i < nCells; i++)
    {
	eavlCell c = cells->GetCellNodes(i);
	float r0 = Rf->GetArray()->GetComponentAsDouble(c.indices[0], 0);
	float r1 = Rf->GetArray()->GetComponentAsDouble(c.indices[1], 0);
	float r2 = Rf->GetArray()->GetComponentAsDouble(c.indices[2], 0);
	
	float z0 = Zf->GetArray()->GetComponentAsDouble(c.indices[0], 0);
	float z1 = Zf->GetArray()->GetComponentAsDouble(c.indices[1], 0);
	float z2 = Zf->GetArray()->GetComponentAsDouble(c.indices[2], 0);

	float v0[2] = {r1-r0, z1-z0}, v1[2] = {r2-r0, z2-z0}, v2[2] = {R-r0, Z-z0};
	float d00 = DOT(v0,v0);
	float d01 = DOT(v0, v1);
	float d11 = DOT(v1, v1);
	float d20 = DOT(v2, v0);
	float d21 = DOT(v2, v1);
	float denom = d00 * d11 - d01 * d01;
	
	float v = (d11 * d20 - d01 * d21) / denom;
	float w = (d00 * d21 - d01 * d20) / denom;
	float u = 1.0f - v - w;

	//We have a triangle hit...
	if (u >= 0.0f && u <= 1.0f &&
	    v >= 0.0f && v <= 1.0f &&
	    w >= 0.0f && w <= 1.0f)
	{

	    double psi0 = psiF->GetArray()->GetComponentAsDouble(c.indices[0], 0);
	    double psi1 = psiF->GetArray()->GetComponentAsDouble(c.indices[1], 0);
	    double psi2 = psiF->GetArray()->GetComponentAsDouble(c.indices[2], 0);

	    psi = psi0*u + psi1*v + psi2*w;
	    //cout<<psi<<"= "<<psi0<<"*"<<u<<" + "<<psi1<<"*"<<v<<" + "<<psi2<<"*"<<w<<endl;
	    //cout<<"Found a cell index: "<< cellIdx<<endl;
	    cellIdx = i;
	    break;
	}
    }

    return psi;
}