/****************************************************************
 * Function to add arcs by calling isArcUnique and testing. If 
 * isArcUnique returns true then function is added to the vector. 
 * If the arc is not unique, it is ignored implicitly.
 *
 * Returns:
 *   none
**/
void UnionFind::addArc(const int a, const int b)
{
    std::vector<Arc>::iterator it;
    Arc arcToAdd = Arc(a, b);

    if( this->isArcUnique(arcToAdd) ) {
        this->arcs.push_back(arcToAdd);
    }
}