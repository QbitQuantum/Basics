// calculates \sum_K v_i'*A*v_i
double dosum(Matrix A, Matrix v)
{
  double alpha=0.0;
  Matrix temp;
  int i, t;

  t = getMaxThreads();

  temp = createMatrix(A->rows, t);
#pragma omp parallel for schedule(static) reduction(+:alpha)
  for(i=0;i<v->cols;++i) {
    MxV(temp->col[getCurrentThread()],A,v->col[i], 1.0, 0.0, 'N');
    alpha += dotproduct(temp->col[getCurrentThread()],v->col[i]);
  }
  freeMatrix(temp);

  return alpha;
}