static void
populatebyrow (IloModel model, IloNumVarArray x, IloRangeArray c)
{
   IloEnv env = model.getEnv();

   x.add(IloNumVar(env, -1.0, 1.0));
   x.add(IloNumVar(env,  0.0, 1.0));
   model.add(IloMinimize(env, 0.5 * (-3*x[0]*x[0] - 3*x[1]*x[1] +
                                       - 1*x[0]*x[1]               ) ));

   c.add( - x[0] + x[1] >= 0);
   c.add(   x[0] + x[1] >= 0);
   model.add(c);
}  // END populatebyrow