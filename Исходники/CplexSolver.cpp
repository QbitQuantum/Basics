void generateProblem(const ILPModel& m, IloModel& model, IloNumVarArray& x, IloRangeArray& con)	{
    IloEnv env = model.getEnv();
    IloObjective obj = (m.obj == MINIMIZE ? IloMinimize(env) : IloMaximize(env));
    for (unsigned long v = 0; v < m.numberOfVariables(); ++v)	{
        switch (m.x[v].type)	{
        case FLT:
            x.add(IloNumVar(env, m.x[v].lowerBound, m.x[v].upperBound, IloNumVar::Float));
            break;
        case BIN:
            x.add(IloNumVar(env, m.x[v].lowerBound, m.x[v].upperBound, IloNumVar::Bool));
            break;
        default:
            x.add(IloNumVar(env, m.x[v].lowerBound, m.x[v].upperBound, IloNumVar::Int));
        }

        obj.setLinearCoef(x[v], m.c[v]);
        x[v].setName(m.varDesc[v].c_str());
    }

    for (unsigned long c = 0; c < m.numberOfConstraints(); ++c)	{
        switch (m.ops[c])	{
        case LESS_EQUAL:
            con.add(IloRange(env, -IloInfinity, m.b[c]));
            break;
        case EQUAL:
            con.add(IloRange(env, m.b[c], m.b[c]));
            break;
        case GREATER_EQUAL:
            con.add(IloRange(env, m.b[c], IloInfinity));
        }

        for (const pair<uint32_t, double>& p : m.A[c])
            con[c].setLinearCoef(x[p.first], p.second);

        con[c].setName(m.conDesc[c].c_str());
    }

    model.add(obj);
    model.add(con);
}