void FirstOrderNonLinearODErEx1::Main(int argc, char **argv)
{
    FirstOrderNonLinearODErEx1 nnl;

    unsigned int N = 100;
    unsigned int M = nnl.count();
    double h = 0.01;
    nnl.setDimension(Dimension(h, 0, static_cast<int>(N)));

    DoubleVector y0(M);
    for (unsigned int r=0; r<M; r++)
    {
        y0[r] = nnl.x(PointNodeODE(0.0, 0), r+1);
    }

    std::vector<DoubleVector> x;
    nnl.cauchyProblem(0.0, y0, x, OdeSolverMethod::RK4);

    for (unsigned int m=0; m<M; m++)
    {
        for (unsigned int n=0; n<=N; n++)
        {
            if (n%(N/10)==0) printf("%14.10f ", x[n][m]);
        }
        puts("");
    }
    IPrinter::printSeperatorLine();

    for (unsigned int m=0; m<M; m++)
    {
        for (unsigned int n=0; n<=N; n++)
        {
            if (n%(N/10)==0) printf("%14.10f ", nnl.x(n*h, m+1));
        }
        puts("");
    }
    IPrinter::printSeperatorLine();

    double norm[] = {0.0, 0.0, 0.0};
    for (unsigned int m=0; m<M; m++)
    {
        norm[m] = 0.0;
        for (unsigned int n=0; n<=N; n++)
        {
            norm[m] += (x[n][m]-nnl.x(n*h, m+1))*(x[n][m]-nnl.x(n*h, m+1));
        }
        norm[m] = sqrt(norm[m]);
    }
    printf("Norms: %.10f %.10f %.10f\n", norm[0], norm[1], norm[2]);
}