void dynamicsRegressorFixedBaseLoop(const UndirectedTree & ,
                         const KDL::JntArray &q,
                         const Traversal & traversal,
                         const std::vector<Frame>& X_b,
                         const std::vector<Twist>& v,
                         const std::vector<Twist>& a,
                         Eigen::MatrixXd & dynamics_regressor)
{
        dynamics_regressor.setZero();

        Eigen::Matrix<double, 6, 10> netWrenchRegressor_i;

        for(int l =(int)traversal.getNrOfVisitedLinks()-1; l >= 0; l-- ) {
            LinkMap::const_iterator link = traversal.getOrderedLink(l);
            int i = link->getLinkIndex();

            //Each link affects the dynamics of the joints from itself to the base
            netWrenchRegressor_i = netWrenchRegressor(v[i],a[i]);

             //dynamics_regressor.block(0,(int)(10*i),6,10) = WrenchTransformationMatrix(X_b[i])*netWrenchRegressor_i;

            LinkMap::const_iterator child_link = link;
            LinkMap::const_iterator parent_link=traversal.getParentLink(link);
            while( child_link != traversal.getOrderedLink(0) ) {
                if( child_link->getAdjacentJoint(parent_link)->getNrOfDOFs() == 1 ) {
                    int dof_index = child_link->getAdjacentJoint(parent_link)->getDOFIndex();
                    int child_index = child_link->getLinkIndex();
                    Frame X_j_i = X_b[child_index].Inverse()*X_b[i];
                    dynamics_regressor.block(dof_index,10*i,1,10) =
                            toEigen(parent_link->S(child_link,q(dof_index))).transpose()*WrenchTransformationMatrix(X_j_i)*netWrenchRegressor_i;
                }
                child_link = parent_link;
                parent_link = traversal.getParentLink(child_link);
            }
        }
}