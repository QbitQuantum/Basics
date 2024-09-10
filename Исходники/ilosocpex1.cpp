// Test KKT conditions on the solution.
// The function returns true if the tested KKT conditions are satisfied
// and false otherwise.
// The function assumes that the model currently extracted to CPLEX is fully
// described by obj, vars and rngs.
static bool
checkkkt (IloCplex& cplex, IloObjective const& obj, IloNumVarArray const& vars,
          IloRangeArray const& rngs, IloIntArray const& cone, double tol)
{
   IloEnv env = cplex.getEnv();
   IloModel model = cplex.getModel();
   IloNumArray x(env), dslack(env);
   IloNumArray pi(env, rngs.getSize()), slack(env);

   // Read primal and dual solution information.
   cplex.getValues(x, vars);
   cplex.getSlacks(slack, rngs);

   // pi for second order cone constraints.
   getsocpconstrmultipliers(cplex, vars, rngs, pi, dslack);

   // pi for linear constraints.
   for (IloInt i = 0; i < rngs.getSize(); ++i) {
      IloRange r = rngs[i];
      if ( !r.getQuadIterator().ok() )
         pi[idx(r)] = cplex.getDual(r);
   }

   // Print out the data we just fetched.
   streamsize oprec = env.out().precision(3);
   ios_base::fmtflags oflags = env.out().setf(ios::fixed | ios::showpos);
   env.out() << "x      = [";
   for (IloInt i = 0; i < x.getSize(); ++i)
      env.out() << " " << x[i];
   env.out() << " ]" << endl;
   env.out() << "dslack = [";
   for (IloInt i = 0; i < dslack.getSize(); ++i)
      env.out() << " " << dslack[i];
   env.out() << " ]" << endl;
   env.out() << "pi     = [";
   for (IloInt i = 0; i < rngs.getSize(); ++i)
      env.out() << " " << pi[i];
   env.out() << " ]" << endl;
   env.out() << "slack  = [";
   for (IloInt i = 0; i < rngs.getSize(); ++i)
      env.out() << " " << slack[i];
   env.out() << " ]" << endl;
   env.out().precision(oprec);
   env.out().flags(oflags);

   // Test primal feasibility.
   // This example illustrates the use of dual vectors returned by CPLEX
   // to verify dual feasibility, so we do not test primal feasibility
   // here.

   // Test dual feasibility.
   // We must have
   // - for all <= constraints the respective pi value is non-negative,
   // - for all >= constraints the respective pi value is non-positive,
   // - the dslack value for all non-cone variables must be non-negative.
   // Note that we do not support ranged constraints here.
   for (IloInt i = 0; i < vars.getSize(); ++i) {
      IloNumVar v = vars[i];
      if ( cone[i] == NOT_IN_CONE && dslack[i] < -tol ) {
         env.error() << "Dual multiplier for " << v << " is not feasible: "
                     << dslack[i] << endl;
         return false;
      }
   }
   for (IloInt i = 0; i < rngs.getSize(); ++i) {
      IloRange r = rngs[i];
      if ( fabs (r.getLB() - r.getUB()) <= tol ) {
         // Nothing to check for equality constraints.
      }
      else if ( r.getLB() > -IloInfinity && pi[i] > tol ) {
         env.error() << "Dual multiplier " << pi[i] << " for >= constraint"
                     << endl << r << endl
                     << "not feasible"
                     << endl;
         return false;
      }
      else if ( r.getUB() < IloInfinity && pi[i] < -tol ) {
         env.error() << "Dual multiplier " << pi[i] << " for <= constraint"
                     << endl << r << endl
                     << "not feasible"
                     << endl;
         return false;
      }
   }

   // Test complementary slackness.
   // For each constraint either the constraint must have zero slack or
   // the dual multiplier for the constraint must be 0. We must also
   // consider the special case in which a variable is not explicitly
   // contained in a second order cone constraint.
   for (IloInt i = 0; i < vars.getSize(); ++i) {
      if ( cone[i] == NOT_IN_CONE ) {
         if ( fabs(x[i]) > tol && dslack[i] > tol ) {
            env.error() << "Invalid complementary slackness for " << vars[i]
                        << ":" << endl
                        << " " << x[i] << " and " << dslack[i]
                        << endl;
            return false;
         }
      }
   }
   for (IloInt i = 0; i < rngs.getSize(); ++i) {
      if ( fabs(slack[i]) > tol && fabs(pi[i]) > tol ) {
         env.error() << "Invalid complementary slackness for "
                     << endl << rngs[i] << ":" << endl
                     << " " << slack[i] << " and " << pi[i]
                     << endl;
         return false;
      }
   }

   // Test stationarity.
   // We must have
   //  c - g[i]'(X)*pi[i] = 0
   // where c is the objective function, g[i] is the i-th constraint of the
   // problem, g[i]'(x) is the derivate of g[i] with respect to x and X is the
   // optimal solution.
   // We need to distinguish the following cases:
   // - linear constraints g(x) = ax - b. The derivative of such a
   //   constraint is g'(x) = a.
   // - second order constraints g(x[1],...,x[n]) = -x[1] + |(x[2],...,x[n])|
   //   the derivative of such a constraint is
   //     g'(x) = (-1, x[2]/|(x[2],...,x[n])|, ..., x[n]/|(x[2],...,x[n])|
   //   (here |.| denotes the Euclidean norm).
   // - bound constraints g(x) = -x for variables that are not explicitly
   //   contained in any second order cone constraint. The derivative for
   //   such a constraint is g'(x) = -1.
   // Note that it may happen that the derivative of a second order cone
   // constraint is not defined at the optimal solution X (this happens if
   // X=0). In this case we just skip the stationarity test.
   IloNumArray sum(env, vars.getSize());
   for (IloExpr::LinearIterator it = obj.getLinearIterator(); it.ok(); ++it)
      sum[idx(it.getVar())] = it.getCoef();

   for (IloInt i = 0; i < vars.getSize(); ++i) {
      IloNumVar v = vars[i];
      if ( cone[i] == NOT_IN_CONE )
         sum[i] -= dslack[i];
   }
   for (IloInt i = 0; i < rngs.getSize(); ++i) {
      IloRange r = rngs[i];
      if ( r.getQuadIterator().ok() ) {
         // Quadratic (second order cone) constraint.
         IloNum norm = 0.0;
         for (IloExpr::QuadIterator q = r.getQuadIterator(); q.ok(); ++q) {
            if ( q.getCoef() > 0 )
               norm += x[idx(q.getVar1())] * x[idx(q.getVar1())];
         }
         norm = sqrt(norm);
         if ( fabs(norm) <= tol ) {
            // Derivative is not defined. Skip test.
            env.warning() << "Cannot test stationarity at non-differentiable point."
                          << endl;
            return true;
         }
         else {
            for (IloExpr::QuadIterator q = r.getQuadIterator(); q.ok(); ++q) {
               if ( q.getCoef() < 0 )
                  sum[idx(q.getVar1())] -= pi[i];
               else
                  sum[idx(q.getVar1())] += pi[i] * x[idx(q.getVar1())] / norm;
            }
         }
      }
      else {
         // Linear constraint.
         for (IloExpr::LinearIterator l = r.getLinearIterator(); l.ok(); ++l)
            sum[idx(l.getVar())] -= pi[i] * l.getCoef();
      }
   }

   // Now test that all elements in sum[] are 0.
   for (IloInt i = 0; i < vars.getSize(); ++i) {
      if ( fabs(sum[i]) > tol ) {
         env.error() << "Invalid stationarity " << sum[i] << " for "
                     << vars[i] << endl;
         return false;
      }
   }

   return true;   
}