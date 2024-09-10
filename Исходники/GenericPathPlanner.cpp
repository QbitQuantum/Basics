Path* GenericPathPlanner::getInitialPath(OccupancyGridMap* map,int startCell, int goalCell, int isSmart)
{
	  Path* emptyPath=new Path();

if (isStartAndGoalCellsValid(map, startCell, goalCell)){

  ofstream file ("generic", ios::trunc) ;
  Path* initialPath;// the initial path that will be generated
  vector <vector <int> > deadLockPos; // it contains the couples of (previousCell, DeadlockCell).
  vector <int> neighborCells;
  int currentCell; // the current cell

 	      initialPath=new Path();
	      initialPath->setCost(0.0);
	      initialPath->insertCell(map,0,startCell);
	      currentCell=startCell;

	      // while the goal position has not reached.

	      while ((currentCell!=goalCell) && (currentCell != -1))
	      {
		neighborCells.clear();
		neighborCells=getValidNeighbors(map,initialPath,currentCell,deadLockPos,goalCell); //search the neighbor cells

		//2 cases: 
		if(neighborCells.size()>0){ //if the size of the neighbors vector is superior to 0
			currentCell=getBestNextCellEuclidian(map,neighborCells,goalCell); //choose the nextCell
			//currentCell=getBestNextCellManhattan(map,neighborCells,goalCell);
		}
		else{ //if the size of the vector of neighboor is equal to 0: we fall in a deadlock
		  currentCell=backtracking(map,deadLockPos, initialPath, goalCell);
		}

		if (currentCell == -1){
			return emptyPath;
		}

		initialPath->insertCell(map,initialPath->getPath().size(),currentCell);	
	      }

  return initialPath;

}
	else {
		cout<<"NOT valid start or goal";
		return emptyPath;
		//exit(1);
	}

}