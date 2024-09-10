// Decribe for debugging use or output on some errors
void MPMBase::Describe(void)
{   cout << "# pt: pos=(" << pos.x << "," << pos.y << "," << pos.z << ") mass=" << mp <<
         " matl=" << matnum << " elem=" << inElem << endl;
    cout << "#     vel=(" << vel.x << "," << vel.y << "," << vel.z << ") " << UnitsController::Label(CUVELOCITY_UNITS) << endl;
    Matrix3 pF = GetDeformationGradientMatrix();
    cout << "#       F=" << pF << ", |F|=" << pF.determinant() << endl;
    double rho0=theMaterials[MatID()]->rho;
    double rho = rho0*UnitsController::Scaling(1.e-6)/theMaterials[MatID()]->GetCurrentRelativeVolume(this);
    cout << "#       P= " << pressure*rho << " " << UnitsController::Label(PRESSURE_UNITS) << endl;
    cout << "# sigmaii=(" << sp.xx*rho << "," << sp.yy*rho << "," << sp.zz << ") " << UnitsController::Label(PRESSURE_UNITS) << endl;
    cout << "#   tauij=(" << sp.xy*rho << "," << sp.xz*rho << "," << sp.yz << ") " << UnitsController::Label(PRESSURE_UNITS) << endl;
    cout << "#       T= " << pTemperature << " prev T=" << pPreviousTemperature << endl;
}