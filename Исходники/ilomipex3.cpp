static void
populatebyrow (IloModel model, IloNumVarArray x, IloRangeArray c)
{
   IloEnv env = model.getEnv();

   x.add(IloNumVar(env, 0.0, 40.0));
   x.add(IloNumVar(env, 0.0, IloInfinity, ILOINT));
   x.add(IloNumVar(env, 0.0, IloInfinity, ILOINT));
   x.add(IloNumVar(env, 2.0, 3.0, ILOINT));
   model.add(IloMaximize(env, x[0] + 2 * x[1] + 3 * x[2] + x[3]));

   c.add( - x[0] +     x[1] + x[2] + 10 * x[3] <= 20);
   c.add(   x[0] - 3 * x[1] + x[2]             <= 30);
   c.add(              x[1]        - 3.5* x[3] == 0);
   model.add(c);

   IloNumVarArray sosvar(env, 2);
   IloNumArray    sosval(env, 2);
   sosvar[0] = x[2]; sosvar[1] = x[3];
   sosval[0] = 25.0; sosval[1] = 18.0;

   model.add(IloSOS1(model.getEnv(), sosvar, sosval));

}  // END populatebyrow