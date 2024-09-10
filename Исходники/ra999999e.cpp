// ATENÇÃO: Não modifique a assinatura deste método.
bool brach_and_bound999999(TSP_Data_R &tsp, const vector<DNode> &terminais, const vector<DNode> &postos,
                           const DNode source,
                           int delta, int maxTime, vector<DNode> &sol, double &lbound){
    // Converte o TSP direcionado para um nao direcionado com duas arestas
    ListGraph graph;
    EdgeValueMap weights(graph);

    // Adiciona os nos
    for (ListDigraph::NodeIt u(tsp.g); u!=INVALID; ++u)
    {
        Node v = graph.addNode();
    }

    // Adiciona as arestas
    for (ListDigraph::ArcIt ait(tsp.g); ait!=INVALID; ++ait)
    {
        // pega os dois nos incidentes
        Arc a(ait);
        DNode u = tsp.g.source(a);
        DNode v = tsp.g.target(a);

        // cria a mesma aresta no grafo não direcionado
        Node gu = graph.nodeFromId(tsp.g.id(u));
        Node gv = graph.nodeFromId(tsp.g.id(v));

        // insere a aresta no grafo nao direcionado
        Edge e = graph.addEdge(gu, gv);
        
        // Atribui pesos as arestas
        weights[e] = tsp.weight[a];
    }

    NodeStringMap nodename(graph);
    NodePosMap posicaox(graph);
    NodePosMap posicaoy(graph);

    TSP_Data utsp(graph, nodename, posicaox, posicaoy, weights);

    // utiliza o convertido
    ListGraph::EdgeMap<GRBVar> x(graph);
    GRBEnv env = GRBEnv();
    GRBModel model = GRBModel(env);

    // TODO: [Opcional] Comente a linha abaixo caso não queira inserir cortes durante a execução do B&B
    model.getEnv().set(GRB_IntParam_LazyConstraints, 1);

    model.getEnv().set(GRB_IntParam_Seed, 0);
    model.set(GRB_StringAttr_ModelName, "TSPR - TSP with Refueling"); // name to the problem
    model.set(GRB_IntAttr_ModelSense, GRB_MINIMIZE); // is a minimization problem

    // Add one binary variable for each arc and also sets its cost in the objective function
    for (EdgeIt e(utsp.g); e!=INVALID; ++e) {
        char name[100];
        
        Edge edge(e);
        unsigned uid = utsp.g.id(utsp.g.u(edge));
        unsigned vid = utsp.g.id(utsp.g.v(edge));

        sprintf(name,"x_%s_%s",tsp.vname[tsp.g.nodeFromId(uid)].c_str(),tsp.vname[tsp.g.nodeFromId(vid)].c_str());
        x[e] = model.addVar(0.0, 1.0, utsp.weight[e],GRB_BINARY,name);
    }
    model.update(); // run update to use model inserted variables

    // converte os terminais e os postos
    vector<Node> uterminais;
    for (auto t : terminais)
    {
        unsigned tid = tsp.g.id(t);
        uterminais.push_back(utsp.g.nodeFromId(tid));
    }

    NodeBoolMap upostos(utsp.g, false);
    for (auto p: postos)
    {
        unsigned pid = tsp.g.id(p);
        // upostos.push_back(utsp.g.nodeFromId(pid));
        upostos[utsp.g.nodeFromId(pid)] = true;
    }

    // Adicione restrições abaixo

    // (1) Nós terminais devem ser visitados exatamente uma vez
    for (auto v : uterminais) {
        GRBLinExpr expr = 0;
        for (IncEdgeIt e(utsp.g,v); e!=INVALID; ++e){
            expr += x[e];
        }
        model.addConstr(expr == 2 );
    }

    // (3) Nó source sempre presente no início do caminho
    Node usource = utsp.g.nodeFromId(tsp.g.id(source));
    GRBLinExpr expr = 0;
    for (IncEdgeIt e(utsp.g,usource); e!=INVALID; ++e){
        expr += x[e];
    }
    model.addConstr(expr >= 1 );

    try {
        model.update(); // Process any pending model modifications.
        //if (maxTime >= 0) model.getEnv().set(GRB_DoubleParam_TimeLimit,maxTime);

        subtourelim cb = subtourelim(utsp , x, usource, upostos, delta);
        model.setCallback(&cb);

        // TODO: [Opcional] Pode-se utilizar o valor de uma solução heurística p/ acelerar o algoritmo B&B (cutoff value).
        //cutoff = tsp.BestCircuitValue-MY_EPS;
        double cutoff = 0.0;
        if (cutoff > MY_EPS) model.getEnv().set(GRB_DoubleParam_Cutoff, cutoff );
        model.update(); // Process any pending model modifications.
        model.optimize();

        // Obtém o status da otimização
        int status = model.get(GRB_IntAttr_Status);
        if(status == GRB_INFEASIBLE || status == GRB_INF_OR_UNBD){
            cout << "Modelo inviavel ou unbounded." << endl;
            return false;
        }

        // Limitante inferior e superior do modelo
        //lbound = model.get(GRB_DoubleAttr_ObjBoundC);

        if( model.get(GRB_IntAttr_SolCount) <= 0 ){
            cout << "Modelo nao encontrou nenhuma solucao viavel no tempo. LowerBound = " << lbound << endl;
            return false;
        }
        else if (status == GRB_OPTIMAL){
            if(verbose) cout << "O modelo foi resolvido ate a otimalidade." << endl;
        }
        else {
            if(verbose) cout << "O modelo encontrou uma solucao sub-otima (i.e. nao ha garantia de otimalidade)." << endl;
        }

        double custo_solucao = model.get(GRB_DoubleAttr_ObjVal);
        
        int uncovered=0;
        EdgeBoolMap cover(utsp.g, false);
        for (EdgeIt e(utsp.g); e!=INVALID; ++e)
        {
            if (BinaryIsOne(x[e].get(GRB_DoubleAttr_X)))
            {
                cover[e] = true;
                uncovered++;
            }
        }
        sol.push_back(tsp.g.nodeFromId(utsp.g.id(usource)));        
        convertSol(x, sol, tsp, utsp, usource, cover, uncovered);

        // Calculo manual do custo da solução (deve ser igual ao ObjVal do Gurobi).
        double soma=0.0;
        ArcName aname(tsp.g);
        vector<Arc> edgesSol;
        ArcColorMap acolor(tsp.g);
        // if( verbose ) cout << "####### " << endl << "Edges of Solution (B&B):" << endl;
        // for (EdgeIt e(utsp.g); e!=INVALID; ++e){
        //     if (BinaryIsOne(x[e].get(GRB_DoubleAttr_X))){ // Note que se este método serve para variáveis binárias, p/ inteiras terá de usar outro método.
        //         soma += utsp.weight[e];
        //         edgesSol.push_back(tsp.g.arcFromId(utsp.g.id(e)));
        //         if( verbose) cout << "(" << tsp.vname[tsp.g.nodeFromId(utsp.g.id(utsp.g.u(e)))] << "," << tsp.vname[tsp.g.nodeFromId(utsp.g.id(utsp.g.v(e)))] << ")" << endl;
        //         acolor[tsp.g.arcFromId(utsp.g.id(e))] = BLUE;
        //     }
        // }
        // if( verbose ) cout << "####### " << endl;
        if( verbose ) cout << "####### " << endl << "Edges of Solution (B&B):" << endl;
        DNode u = sol[0];
        for (int i=1; i<sol.size(); i++) 
        {
            DNode v = sol[i];
            soma += tsp.AdjMatD.Cost(u,v);
            if ( verbose ) cout << "(" << tsp.vname[u] << "," << tsp.vname[v] << ")" << endl;
            u = v;
        }
        if( verbose ) cout << "####### " << endl;

        if( verbose ) cout << "Custo calculado pelo B&B = "<< soma << " / " << custo_solucao << endl;
        if( verbose ){
            cout << "Caminho encontrado a partir do vértice de origem (" << tsp.vname[source] << "): ";
            for(auto node : sol){
                cout << tsp.vname[node] << " ";
            } // Obs: O caminho é gerado a partir do nó source, se o conjunto de arestas retornado pelo B&B for desconexo, o caminho retornado por 'path_search' será incompleto.
            cout << endl << "Custo calculado da solucao (caminho a partir do no origem) = " << solutionCost(tsp, sol) << endl;
            ostringstream out;
            out << "TSP with Refueling B&B, cost= " << custo_solucao;
            ViewListDigraph(tsp.g, tsp.vname, tsp.posx, tsp.posy, tsp.vcolor, acolor, out.str());
        }
        return true;
    }
    catch(GRBException e) {
        cerr << "Gurobi exception has been thrown." << endl;
        cerr << "Error code = " << e.getErrorCode() << endl;
        cerr << e.getMessage();
    }
    catch (...) {
        cout << "Model is infeasible"  << endl;
        return false;
    }
    return false;
}