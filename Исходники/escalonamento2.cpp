int main(int argc,char *argv[]) {
  srand48(1);
  if (argc!=2) {cout<<endl<<"Usage: "<< argv[0]<<"  <filename>"<< endl << endl;
    cout << "Example:      " << argv[0] << " arq1.in" << endl << endl; exit(0);}
	
  ifstream ifile;
  ifile.open(argv[1]);  if (!ifile) return(false);  

  int n, m;
  ifile >> n; ifile >> m;
  vector<double> jobsize(n);
  vector<double> machinespeed(m);
  for(int i=0; i<n; i++) ifile >> jobsize[i];
  for(int i=0; i<m; i++) ifile >> machinespeed[i];
  ifile.close();

  cout << endl;
  cout << "Numero de tarefas: " << n << endl;
  cout << "Tamanho das tarefas" << endl;
  for(int i=0; i<n; i++)
    cout << "T_" << i << ": " << jobsize[i] << endl;
  cout << "Velocidade das maquinas" << endl;
  for(int i=0; i<m; i++)
    cout << "M_" << i << ": " << machinespeed[i] << endl;
  cout << endl << endl;
  
  try {
/*--------------------------------------------------------------------------------- */	
/*--------------------------- ALTERE DAQUI PARA ABAIXO ---------------------------- */
/*--------------------------------------------------------------------------------- */	

    // Voce deve atualizar esta variavel com valores 0 e 1 de tal forma que
    // tarefa_maquina[i][j] = 1 SE_E_SOMENTE_SE a tarefa i foi escalonada na maq. j
    vector<vector<int> > tarefa_maquina(n, vector<int>(m));

    // mais abaixo eh feito um escalonamento aleatorio.
    // Nao se esqueca de alterar a geracao do escalonamento aleatorio para o
    // escalonamento obtido pelo seu programa linear inteiro

    
    // cabecalho comum para os programas lineares (descomente)
     int seed=0;
     GRBEnv env = GRBEnv();
     GRBModel model = GRBModel(env);
     model.getEnv().set(GRB_IntParam_Seed, seed);
     model.set(GRB_StringAttr_ModelName, "Escalonamento de Tarefas"); // prob. name
     model.set(GRB_IntAttr_ModelSense, GRB_MINIMIZE); // is a minimization problem  

    // Lembretes e sintaxes de alguns comandos:
    // GRBVar = nome do tipo das variaveis do Gurobi
    //
     //vector<GRBVar> x[m];
     double TP[m][n];
     GRBVar max = model.addVar(0,10000,1,GRB_CONTINUOUS,"max");
    // Para inserir uma variavel:
    // <variavel_do_tipo_GRBVar> =
    //            model.addVar(<lower_bound>,
    //                         <upper_bound> , 
    //                         <valor_na_funcao_objetivo>,
    //                         <GRB_CONTINUOUS ou GRB_BINARY GRB_INTEGER>
    //                         <string_do_nome_da_variavel>);
    //
    // Este comando deve ser executado depois de inserir todas as variaveis e antes de
    // inserir as restricoes.
     model.update();
    //
    // Para declarar variavel que armazena expressoes
     // for(int i = 0; i<n; i++) { //para cada maquina
     //   GRBLinExpr expr;
     //   for(int j = 0; j<m;j++) { //para cada tarefa
     // 	 expr+=x[m*i+j];
     //   }
     //   model.addConstr(expr >= 0);
     // }
    //
    // Para inserir uma restricao linear:
    // model.addConstr( <restricao_linear> );
    //
    // Comando para escrever o modelo produzido em um arquivo texto (apenas para debugar)
     model.update(); //Tem que dar update de novo pra ver as restricoes
     model.write("model.lp"); system("cat model.lp");
    //
    // Depois que construiu seu programa linear / linear inteiro, execute este comando
    // para resolver o programa linear
     model.optimize();
    //
    // Verifica se obteve solucao otima
     if (model.get(GRB_IntAttr_Status) != GRB_OPTIMAL) {
       cout << "Erro, sistema impossivel" << endl;
       exit(1);
     }
    //
    // Para obter o valor da variavel do programa linear/linear inteiro
    // deve ser executado apos o model.optimize()
    // 	<variavel_do_tipo_GRBVar>.get(GRB_DoubleAttr_X)

    
    // Faz um escalonamento aleatorio.
    // Remova esta parte e coloque o escalonamento
    // gerado pelo seu programa linear inteiro.
    for (int i=0; i<n; i++) 
      for (int j=0; j<m; j++)
	tarefa_maquina[i][j] = 0; // deixa cada maq. sem atribuicao
    // for (int i=0; i<n; i++)
    //   for (int j=0; j<m; j++)
    // 	//if(x[j][i].get(GRB_DoubleAttr_X) >= 0.999) {
    // 	//  cout << j << "  " << i << endl;
    // 	  tarefa_maquina[i][j] = 1;
    // 	}
	  
/*--------------------------------------------------------------------------------- */	
/*--------------------------- ALTERE DAQUI PARA CIMA ------------------------------ */
/*--------------------------------------------------------------------------------- */	

    cout << "\n\n";
      double makespan=0;
      cout << "Escalonamento obtido das tarefas nas maquinas\n";
      cout << "Notacao para tarefas : T_id(tamanho_original)\n";
      cout << "Notacao para maquinas: M_id(velocidade)\n\n";
      
      for (int j=0; j<m; j++) {
	double tmaq=0.0;
	cout << "M_"<<j<<"("<< machinespeed[j] << ") : ";
	for(int i=0; i<n; i++) {
	  if (tarefa_maquina[i][j] == 1) {
	    cout << "T_" << i << "(" << jobsize[i] << ") ";
	    tmaq += jobsize[i] / machinespeed[j];
	  }
	}
	cout << endl << "Tempo gasto pela maquina M_" <<j << ": " << tmaq << endl<<endl;
	if (tmaq>makespan) makespan = tmaq;
      }
      cout << "\nTempo para completar todas as tarefas: " << makespan << "s\n\n";
      //  } else  cout << "No solution" << "\n";
  }
  // catch (GRBException e) {
  //   cout << "Error code = " << e.getErrorCode() << endl;
  //   cout << e.getMessage() << endl;
  // }
  catch (...) {
    cout << "Exception during optimization" << endl;
  }
  return 0;
}