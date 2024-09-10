int main (int argc, char** argvs) {
  //Check number of arguments
  if(argc != 2){
    printf("Expected 1 argument to commandline.\n");
    exit(-1);
  }

  //Read in AST
  char* filename = argvs[1];
  ScopeStmt* stmt = read_ast(filename);

  //Compile to bytecode
  Program* program = compile(stmt);

  //Read in bytecode
  //Program* program = load_bytecode(argvs[1]);
  //Interpret bytecode
#ifdef DEBUG
  TIME_T t1, t2;
  FREQ_T freq;
  FREQ(freq);
  TIME(t1);
#endif

  interpret_bc(program);

#ifdef DEBUG
  TIME(t2);
  double interp_time = ELASPED_TIME(t1, t2, freq);
  fprintf(stderr, "Interpret Time: %.4lf ms.\n", interp_time);
#endif

}