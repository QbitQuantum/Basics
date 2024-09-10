void solve(const Instance &inst, bool print_inst = false, bool pyout = false) {
    Arcflow afg(inst);
    char vtype = inst.vtype;
    GRBEnv* env = new GRBEnv();
    GRBModel model = GRBModel(*env);
    model.set(GRB_StringAttr_ModelName, "flow");

    model.getEnv().set(GRB_IntParam_OutputFlag, 1);
    model.getEnv().set(GRB_IntParam_Threads, 1);
    model.getEnv().set(GRB_IntParam_Presolve, 1);
    // model.getEnv().set(GRB_IntParam_Method, 0);
    model.getEnv().set(GRB_IntParam_Method, 2);
    model.getEnv().set(GRB_IntParam_MIPFocus, 1);
    // model.getEnv().set(GRB_IntParam_RINS, 1);
    model.getEnv().set(GRB_DoubleParam_Heuristics, 1);
    model.getEnv().set(GRB_DoubleParam_MIPGap, 0);
    model.getEnv().set(GRB_DoubleParam_MIPGapAbs, 1-1e-5);
    // model.getEnv().set(GRB_DoubleParam_ImproveStartTime, 60);
    // model.getEnv().set(GRB_DoubleParam_ImproveStartGap, 1);

    vector<Arc> As(afg.A);
    sort(all(As));
    map<Arc, GRBVar> va;
    int lastv = afg.Ts[0]-1;
    for (int i = 0; i < inst.nbtypes; i++) {
        lastv = min(lastv, afg.Ts[i]-1);
    }
    for (int i = 0; i < 3; i++) {
        for (const Arc &a : As) {
            if (i == 1 && a.u != afg.S) {
                continue;
            }
            if (i == 2 && a.v <= lastv) {
                continue;
            }
            if (i == 0 && (a.u == afg.S || a.v > lastv)) {
                continue;
            }

            if (a.label == afg.LOSS || inst.relax_domains) {
                va[a] = model.addVar(
                    0.0, inst.n, 0, vtype);
            } else {
                va[a] = model.addVar(
                    0.0, inst.items[a.label].demand, 0, vtype);
            }
        }
    }
    model.update();

    for (int i = 0; i < inst.nbtypes; i++) {
        GRBVar &feedback = va[Arc(afg.Ts[i], afg.S, afg.LOSS)];
        feedback.set(GRB_DoubleAttr_Obj, inst.Cs[i]);
        if (inst.Qs[i] >= 0) {
            feedback.set(GRB_DoubleAttr_UB, inst.Qs[i]);
        }
    }

    vector<vector<Arc>> Al(inst.nsizes);
    vector<vector<Arc>> in(afg.NV);
    vector<vector<Arc>> out(afg.NV);

    for (const Arc &a : As) {
        if (a.label != afg.LOSS) {
            Al[a.label].push_back(a);
        }
        out[a.u].push_back(a);
        in[a.v].push_back(a);
    }

    for (int i = 0; i < inst.m; i++) {
        GRBLinExpr lin = 0;
        for (int it = 0; it < inst.nsizes; it++) {
            if (inst.items[it].type == i) {
                for (const Arc &a : Al[it]) {
                    lin += va[a];
                }
            }
        }
        if (inst.ctypes[i] == '>' || inst.relax_domains) {
            model.addConstr(lin >= inst.demands[i]);
        } else {
            model.addConstr(lin == inst.demands[i]);
        }
    }

    for (int u = 0; u < afg.NV; u++) {
        GRBLinExpr lin = 0;
        for (const Arc &a : in[u]) {
            lin += va[a];
        }
        for (const Arc &a : out[u]) {
            lin -= va[a];
        }
        model.addConstr(lin == 0);
    }

    Al.clear();
    in.clear();
    out.clear();

    double pre = TIMEDIF(afg.tstart);
    model.optimize();
    printf("Preprocessing time: %.2f seconds\n", pre);
    double tg = model.get(GRB_DoubleAttr_Runtime);
    printf("Gurobi run time: %.2f seconds\n", tg);
    printf("Total run time: %.2f seconds\n", tg+pre);

    if (inst.vtype == 'I') {
        map<Arc, int> flow;
        for (const auto &a : va) {
            double x = a.second.get(GRB_DoubleAttr_X);
            int rx = static_cast<int>(round(x));
            assert(x - rx <= EPS);
            if (rx > 0) {
                int u = a.first.u;
                int v = a.first.v;
                int lbl = a.first.label;
                Arc a(u, v, lbl);
                flow[a] = rx;
            }
        }
        ArcflowSol solution(inst, flow, afg.S, afg.Ts, afg.LOSS, true);
        solution.print_solution(print_inst, pyout);
    }
    free(env);
}