 /** Get the best incumbent in this worker.
  * Calling this function before calling join() is an error.
  */
 IloNumArray getX() const {
    IloNumArray values(cplex.getEnv());
    cplex.getValues(x, values);
    return values;
 }