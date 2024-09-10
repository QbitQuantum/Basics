        /** Compute the potential of a node according to the weights and its
         * features.
         * \param features: features of the node.
         * \return potentials of that node.
         */
        Eigen::VectorXd computePotentials( Eigen::VectorXd &features )
        {
            // Check that features are a column vector, and transpose it  otherwise
            if ( features.cols() > 1 )
                        features = features.transpose();

            assert ( features.rows() == m_nFeatures );

            return (*m_computePotentialsFunction)(m_weights,features);
        }