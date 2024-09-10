/* initialisiere N^2 Variablen und erstelle eine zu minimierende
 * Strecken-Zielfunktion über die Distanzmatrix c
 *
 * eigentlich sind nur (N*N-N)/2 Variablen nötig, aber dafür müsste
 * ich mir etwas schlaues zur Adressierung ausdenken (weil das untere linke
 * Dreieck einer Matrix adressiert werden muss, ist das nicht trivial)
 * Der Presolver scheint die überflüssigen Variablen allerdings
 * direkt zu verwerfen, weshalb das nicht dringend ist.
 * */
IloNumVarArray CplexTSPSolver::init_symmetric_var(IloModel model)
{
    IloEnv env = model.getEnv();

    // Edge Variables
    IloNumVarArray x(env);
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(j<i)
                x.add(IloNumVar(env, 0, 1, mip ? ILOINT : ILOFLOAT));
            else
                x.add(IloNumVar(env, 0, 0, ILOFLOAT)); // fülle oben rechts mit dummies
    model.add(x);

    // Cost Function
    IloExpr expr(env);

    // die folgenden Schleifen adressieren ein unteres linkes
    // Dreieck in einer quadratischen Matrix
    for(int i=0; i<N; i++)
        for (int j=0; j<i; j++)
            expr += c[i*N + j] * x[i*N + j];

    model.add(IloMinimize(env, expr));
    expr.end();

    return x;
}