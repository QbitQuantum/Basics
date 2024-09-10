static void
populatebyrow (IloModel model, IloNumVarArray x, IloRangeArray c)
{
   IloEnv env = model.getEnv();

   x.add(IloNumVar(env, 0.0, 40.0));
   x.add(IloNumVar(env));
   x.add(IloNumVar(env));
   model.add(IloMaximize(env, x[0] + 2 * x[1] + 3 * x[2]
                            - 0.5 * (33*x[0]*x[0] + 22*x[1]*x[1] +
                                     11*x[2]*x[2] - 12*x[0]*x[1] -
                                     23*x[1]*x[2]                 ) ));

   c.add( - x[0] +     x[1] + x[2] <= 20);
   c.add(   x[0] - 3 * x[1] + x[2] <= 30);
   model.add(c);
}  // END populatebyrow