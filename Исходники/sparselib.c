void resizeMatrix(sparseMatrix *matrix, int newSize)
{
  int oldSize;

  if(matrix == NULL)
    oldSize = 0;
  else
    oldSize = matrix->size;
  while(oldSize>newSize) {
	  oldSize--;
	  freeVector(matrix->list[oldSize]);
    return;
  }
  REALLOC(matrix->list, newSize);
  while(oldSize<newSize) {
	  matrix->list[oldSize] = NULL;
	  oldSize++;
  }
  if(newSize>0)
    matrix->size = newSize;
}