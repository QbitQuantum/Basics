// This routine separates Benders' cuts violated by the current x solution.
// Violated cuts are found by solving the worker LP
//
IloBool
separate(const Arcs x, const IloNumArray2 xSol, IloCplex cplex,
         const IloNumVarArray v, const IloNumVarArray u,
         IloObjective obj, IloExpr cutLhs, IloNum& cutRhs)
{
   IloBool violatedCutFound = IloFalse;

   IloEnv env = cplex.getEnv();
   IloModel mod = cplex.getModel();

   IloInt numNodes = xSol.getSize();
   IloInt numArcs  = numNodes * numNodes;
   IloInt i, j, k, h;

   // Update the objective function in the worker LP:
   // minimize sum(k in V0) sum((i,j) in A) x(i,j) * v(k,i,j)
   //          - sum(k in V0) u(k,0) + sum(k in V0) u(k,k)
   
   mod.remove(obj);
   IloExpr objExpr = obj.getExpr();
   objExpr.clear();
   for (k = 1; k < numNodes; ++k) {
      for (i = 0; i < numNodes; ++i) {
         for (j = 0; j < numNodes; ++j) {
               objExpr +=  xSol[i][j] * v[(k-1)*numArcs + i*numNodes + j];
         }
      }
   }
   for (k = 1; k < numNodes; ++k) {
      objExpr += u[(k-1)*numNodes + k];
      objExpr -= u[(k-1)*numNodes];
   }
   obj.setExpr(objExpr);
   mod.add(obj);
   objExpr.end(); 

   // Solve the worker LP

   cplex.solve();

   // A violated cut is available iff the solution status is Unbounded

   if ( cplex.getStatus() == IloAlgorithm::Unbounded ) {

      IloInt vNumVars = (numNodes-1) * numArcs;
      IloNumVarArray var(env);
      IloNumArray val(env);

      // Get the violated cut as an unbounded ray of the worker LP

      cplex.getRay(val, var);

      // Compute the cut from the unbounded ray. The cut is:
      // sum((i,j) in A) (sum(k in V0) v(k,i,j)) * x(i,j) >=
      // sum(k in V0) u(k,0) - u(k,k)

      cutLhs.clear();
      cutRhs = 0.;

      for (h = 0; h < val.getSize(); ++h) {

         IloInt *index_p = (IloInt*) var[h].getObject();
         IloInt index = *index_p;

         if ( index >= vNumVars ) {
            index -= vNumVars;
            k = index / numNodes + 1;
            i = index - (k-1)*numNodes;
            if ( i == 0 )
               cutRhs += val[h];
            else if ( i == k )
               cutRhs -= val[h];
         }
         else {
            k = index / numArcs + 1;
            i = (index - (k-1)*numArcs) / numNodes;
            j = index - (k-1)*numArcs - i*numNodes;
            cutLhs += val[h] * x[i][j];
         }
      }

      var.end();
      val.end();

      violatedCutFound = IloTrue;
   }

   return violatedCutFound;

} // END separate