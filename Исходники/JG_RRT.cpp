/**
 * @function plan
 * @brief
 */
bool JG_RRT::plan( const Eigen::VectorXd &_startConfig,
                   const Eigen::Transform<double, 3, Eigen::Affine> &_goalPose,
                   const std::vector< Eigen::VectorXd > &_guidingNodes,
                   std::vector<Eigen::VectorXd> &path )
{
    /** Store information */
    this->startConfig = _startConfig;
    this->goalPose = _goalPose;
    this->goalPosition = _goalPose.translation();


    //-- Initialize the search tree
    addNode( startConfig, -1 );

    //-- Add the guiding nodes
    addGuidingNodes( _guidingNodes );

    double p;
    while( goalDistVector[activeNode] > distanceThresh )
    {
        //-- Generate the probability
        p = RANDNM( 0.0, 1.0 );

        //-- Apply either extension to goal (J) or random connection
        if( p < p_goal )
        {
            if( extendGoal() == true )
            {
                break;
            }
        }
        else
        {
            tryStep(); /*extendRandom();*/
        }

        // Check if we are still inside
        if( configVector.size() > maxNodes )
        {   cout<<"-- Exceeded "<<maxNodes<<" allowed - ws_dist: "<<goalDistVector[rankingVector[0]]<<endl;
            break;
        }
    }

    //-- If a path is found
    if( goalDistVector[activeNode] < distanceThresh )
    {   tracePath( activeNode, path );
        cout<<"JG - Got a path! - nodes: "<<path.size()<<" tree size: "<<configVector.size()<<endl;
        return true;
    }
    else
    {   cout<<"--(!) JG :No successful path found! "<<endl;
        return false;
    }
}