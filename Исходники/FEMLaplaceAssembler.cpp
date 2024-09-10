void FEMLaplaceAssembler::visit(Triangle3 *t) {
    //cout << force->getValue(t->getCenter()) << endl;

    Epetra_SerialDenseMatrix R(2, 2);

    R(0, 0) = t->getPoint(0)->getCoord(0) - t->getPoint(1)->getCoord(0);
    R(1, 0) = t->getPoint(0)->getCoord(1) - t->getPoint(1)->getCoord(1);
    R(0, 1) = t->getPoint(2)->getCoord(0) - t->getPoint(0)->getCoord(0);
    R(1, 1) = t->getPoint(2)->getCoord(1) - t->getPoint(0)->getCoord(1);

    double detR = R(0, 0) * R(1, 1) - R(1, 0) * R(0, 1);

    Epetra_SerialDenseSolver RSolv;
    RSolv.SetMatrix(R);
    RSolv.Invert();

    Epetra_SerialDenseMatrix maper(2, 3);

    maper(0, 0) = -1;
    maper(0, 1) = 1;
    maper(1, 0) = -1;
    maper(1, 2) = 1;

    Epetra_SerialDenseMatrix B(2, 3);
    B.Multiply('T', 'N', 1, R, maper, 0);

    Epetra_SerialDenseMatrix Kloc(3, 3);
    Kloc.Multiply('T', 'N', fabs(detR) / 2, B, B, 0);

    Epetra_IntSerialDenseVector indexes(3);

    for (int i = 0; i < 3; i++)
        indexes(i) = dofMap[t->getPoint(i)][0];

    K->SumIntoGlobalValues(indexes, indexes, Kloc);
}