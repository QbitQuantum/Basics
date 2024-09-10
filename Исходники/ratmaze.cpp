bool ratMaze::solveAux(Point curr,char newM[][MAXSIZE])
{
    if (curr.getW()==cheese.getW()&&curr.getL()==cheese.getL())
        return true;
    if (curr.getW()<0||curr.getW()>=wid||curr.getL()<0||curr.getL()>=len)
        return false;
    if (newM[curr.getL()][curr.getW()]=='#')
        return false;
    if (newM[curr.getL()][curr.getW()]=='P')
        return false;
    //else
    newM[curr.getL()][curr.getW()]='P';
    if (solveAux(northRat(curr), newM))
        return true;
    if (solveAux(eastRat(curr), newM))
        return true;
    if (solveAux(southRat(curr), newM))
        return true;
    if (solveAux(westRat(curr), newM))
        return true;
    newM[curr.getL()][curr.getW()]='.'; 
    return false;
}   