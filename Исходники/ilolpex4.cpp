static void
populatebycolumn (IloModel model, IloNumVarArray x, IloRangeArray c)
{
   IloEnv env = model.getEnv();

   IloObjective obj = IloMaximize(env);
   c.add(IloRange(env, -IloInfinity, 20.0));
   c.add(IloRange(env, -IloInfinity, 30.0));

   x.add(IloNumVar(obj(1.0) + c[0](-1.0) + c[1]( 1.0), 0.0, 40.0));
   x.add(obj(2.0) + c[0]( 1.0) + c[1](-3.0));
   x.add(obj(3.0) + c[0]( 1.0) + c[1]( 1.0));

   model.add(obj);
   model.add(c);
}  // END populatebycolumn