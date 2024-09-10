//DFS with heuristic
void DFSBoard::DoDFS(){
  //TODO: choose an answer of the line with minimum possible answer() -> use heuristic to fill board -> check other lineis legal or not -> if legal, next line
  puts("doDFS");
  vector<int> rowOrder(r);
  int nowr = 0;
  rowOrder[nowr] = getRowWithMinBranch(nowr, rowOrder);
  while(nowr <= r){
    puts("nowroworder");
    for(int i = 0; i <= nowr; i++)
      printf("%d ", rowOrder[i]);
    puts("");
    if(isAllSolved())
      return;
    if(!tryFillRowHeuristic(rowOrder[nowr])){//try all possibilities to fill the row, will filling next answer after previous called
      if(nowr == 0){
	puts("rewind to the first row: no solution:");
	break;
      }
      //all possibilities in row nowr are failed, recover board to previous row(nowr-1)
      lastfillStart[rowOrder[nowr]].clear();
      Rewind(rowOrder[--nowr]);
    } else {// fill answer success, continue filling next row
      rowOrder[++nowr] = getRowWithMinBranch(nowr, rowOrder);
      if(nowr == r)//complete, check column again
	if(isDFSAnswerCorrect())
	  return;
	else
	  Rewind(rowOrder[--nowr]);
    }
  }
}