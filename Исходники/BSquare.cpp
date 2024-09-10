// --------------------------------------------------------
// does nothing on blank squares. Otherwise, it checks that the square's mark is in its possibility set and throws a fatal error if not. Finally, it updates the possibility sets in all the clusters to which it belongs by calling its delegate Cluster::shoop().
void BSquare::
shoop() const
{
    if ( !isBlank() )
    {
        if ( !isPossible(getMark()) )
            throw Fatal("Mark %d not possible in square (%d, %d)", getMark(), row, column);
        else {
            // update possibleSet in the cluster
            for (std::vector<Cluster*>::const_iterator it = clu.begin(); it < clu.end(); it++)
                (*it)->shoop(this);
        }
    }
}