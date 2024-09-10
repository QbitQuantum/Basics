string SBDelanteroL::Accion()
{

    Vector3f b = soccerPerceptor.GetDriveVec(VO_BALL);
    Vector3f myPos = soccerPerceptor.getMyPos();
    int unum=soccerPerceptor.getUnum();

    Vector3f g1 = soccerPerceptor.GetDriveVec(G1R);
    Vector3f g2 = soccerPerceptor.GetDriveVec(G2R);
    Vector3f Dir = (g1 + g2) / 2;

    if (myPos.x() <-10 && b.Length() > 5) {
        return Ir(Dir);
    }

    //Buscar centrar el Balon si esta cerca de las esquinas del contrario
    if (gAbs(myPos.y()) + myPos.x() > 28) {
        Dir += (soccerPerceptor.GetDriveVec(F2L) + soccerPerceptor.GetDriveVec(F1L))*.01;
    }

    Dir -= b;
    Dir = Dir.Normalize();

    float Pesc = Dir.Dot(b) / b.Length(), fact = 0;
    // cout << " Pesc " << Pesc <<" b.Length() " << b.Length() << endl;
    if (Pesc < 0.3 && b.Length() < 2) {
        if (unum % 2 == 0) {
            Dir = soccerPerceptor.GetDriveVec(F1L);
        } else {
            Dir = soccerPerceptor.GetDriveVec(F2L);
        }
        Dir = Dir.Normalize() - b.Normalize();
    } else if (Pesc > 0.75 && b.Length() < 5) {
        Dir = Dir + b;
    } else {
        fact = -b.Length() *.2 - 1;
        Dir = Dir * fact + b;
    }
    return Ir(Dir);
}