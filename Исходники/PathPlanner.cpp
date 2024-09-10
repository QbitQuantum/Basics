int PathPlanner::computeHeuristic(int xs, int ys, int xg, int yg) {
	return 4*std::min(abs(nodeMap[xs][ys].x -nodeMap[xg][yg].x),abs(nodeMap[xs][ys].y -nodeMap[xg][yg].y))+3*abs(abs(nodeMap[xs][ys].x -nodeMap[xg][yg].x)-abs(nodeMap[xs][ys].y -nodeMap[xg][yg].y));

}