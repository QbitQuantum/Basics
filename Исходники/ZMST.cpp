void ZMST::exec() {
  smst.calculateMST();
  //reserve before mass data pushing back
  lines_.reserve(smst.lines().size());
  for (int i = 0; i < (int)smst.lines().size(); i ++)
    lines_.push_back(Line_Z(smst.lines()[i].start(), smst.lines()[i].end(),
                            Point()));
  //lines is a sorted line vector, while smst.lines_ is in father-child order
  sort(lines_.begin(), lines_.end(), lineCmp);
  //make the positive direction table
  int* head = new int[points().size() + 1];
  for (int i = 0, j = 0; i <= (int)points().size() && j <= (int)lines().size(); ) {
    if (j == (int)lines().size() || line(j).start() != i - 1)
      head[i ++] = j;
    else
      j ++;
  }
  //Discretization
  int* father = new int[points().size()],
     * xgrids = new int[points().size()],
     * ygrids = new int[points().size()],
     xgridsize, ygridsize;
  for (int i = 0; i < (int)lines_.size(); i ++) {
    father[lines_[i].end()] = lines_[i].start();
  }
  father[0] = -1;
  for (int i = 0; i < (int)points().size(); i ++) {
    xgrids[i] = point(i).x();
    ygrids[i] = point(i).y();
  }
  sort (xgrids, xgrids + points().size());
  sort (ygrids, ygrids + points().size());
  xgridsize = unique(xgrids, xgrids + points().size()) - xgrids;
  ygridsize = unique(ygrids, ygrids + points().size()) - ygrids;
  vector<vector<layout> > subProb(vector<vector<layout> >(points().size(),
                                                          vector<layout>()));
  //Enumerate all layouts
  for (vector<Line_Z>::iterator it = lines_.begin();
       it != lines_.end(); ++ it) {
    int minx = min(point(it->start()).x(), point(it->end()).x()),
        maxx = max(point(it->start()).x(), point(it->end()).x()),
        miny = min(point(it->start()).y(), point(it->end()).y()),
        maxy = max(point(it->start()).y(), point(it->end()).y());
    int minxid = lower_bound(xgrids, xgrids + xgridsize, minx) - xgrids,
        maxxid = lower_bound(xgrids, xgrids + xgridsize, maxx) - xgrids,
        minyid = lower_bound(ygrids, ygrids + ygridsize, miny) - ygrids,
        maxyid = lower_bound(ygrids, ygrids + ygridsize, maxy) - ygrids;
    for (int i = minxid; i <= maxxid; i ++) {
      subProb[it->end()].push_back(Point(xgrids[i], point(it->start()).y()));
    }
    for (int i = minyid; i <= maxyid; i ++) {
      subProb[it->end()].push_back(Point(point(it->start()).x(), ygrids[i]));
    }
  }
  //Caculate from leaves to root
  int stack[6];
  for (vector<Line>::const_reverse_iterator it = smst.lines().rbegin();
       it != smst.lines().rend(); ++ it) {
    for (vector<layout>::iterator lit = subProb[it->end()].begin();
         lit != subProb[it->end()].end(); ++ lit) {
      dfs(it->end(), father[it->end()], head[it->end()], *lit, lines(),
          subProb, head, stack);
    }
  }
  subProb[0].push_back(point(0));
  dfs(0, 0, head[0], subProb[0][0], lines(), subProb, head, stack);
  getAns(0, subProb[0][0],subProb, head);
  delete []head;
  delete []xgrids;
  delete []ygrids;
  delete []father;
}