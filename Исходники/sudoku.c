// This function actually solves the puzzle.
void solve(int cell, int trial, char * puzzle, int * indexes, int maxIndex)
{

// The following can be viewed if compiled with option -DDEBUG
#ifdef DEBUG
printf("Blah-1  cell=%i  trial=%i   indexes[cell]=%i  a=%i\n", cell, trial, indexes[cell], maxIndex);
#endif

if (maxIndex < 0)
{
  return;
}

// Base case (This means we have reaches the last cell)
if (cell > maxIndex)
{
  printf("\nThat was easy!\n\n");
  return;
}

// No possible number for the cell (means we have to go and try different numbers for the previous cells)
if (trial > 9 && cell > 0)
{
  puzzle[indexes[cell]] = '0';
  return solve(cell - 1, chartoint(puzzle[indexes[cell-1]]) + 1, puzzle, indexes, maxIndex);
}

// If no numbers are possible for the first cell then the puzzle is not solvable!
else if (trial > 9 && cell == 0)
{
  printf("Puzzle not solvable\n");
  return;
}

  
// flag keeps track of whether or not the trial is possible for the current cell
int flag = 1;

    
// Rule for vertical columns
for (int f = 0; f < 81; f++)
{
  if ((f % 9) == (indexes[cell] % 9))
  {
    if (puzzle[f] == inttochar(trial))
    {
      flag = 0;         }
    }
}
        
// Rule for horizontal rows
int b = indexes[cell] - (indexes[cell] % 9);
for (int d = 0; d < 9; ++d, ++b)
{
  if (puzzle[b] == inttochar(trial))
  {
    flag = 0;
  }
}

// Rule for sqaures
int c = (indexes[cell]-(indexes[cell] % 27)+(indexes[cell] % 9)-(indexes[cell] % 3));
for (int z = 0; z < 3; z++)
{
  for (int y = 0; y < 3; y++)
  {
    if (puzzle[9*z + y + c] == inttochar(trial))
    {
      flag = 0;
    }
  }
}


// If the trial works go to the next cell
if (flag == 1)
{
  puzzle[indexes[cell]] = inttochar(trial);
  return solve(cell + 1, 1, puzzle, indexes, maxIndex);
}

// Else try the next number
else
{
  return solve(cell, trial + 1, puzzle, indexes, maxIndex);
}
  
}