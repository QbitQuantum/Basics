static void
populatebyrow (IloModel model, IloNumVarArray x, IloRangeArray c)
{
   IloEnv env = model.getEnv();

   x.add(IloNumVar(env, 0.0, 40.0));
   x.add(IloNumVar(env));
   x.add(IloNumVar(env));
   x.add(IloNumVar(env, 2.0, 3.0, ILOINT));
   model.add(IloMaximize(env, x[0] + 2 * x[1] + 3 * x[2] + x[3]));

   c.add( - x[0] +     x[1] + x[2] + 10 * x[3] <= 20);
   c.add(   x[0] - 3 * x[1] + x[2]             <= 30);
   c.add(              x[1]        - 3.5* x[3] == 0);
   model.add(c);

}  // END populatebyrow