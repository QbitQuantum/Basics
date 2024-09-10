            void
            printPose( Eigen::Affine3f const& pose )
            {
                // debug
                std::cout << pose.linear() << std::endl <<
                             pose.translation().transpose() << std::endl;

                float alpha = atan2(  pose.linear()(1,0), pose.linear()(0,0) );
                float beta  = atan2( -pose.linear()(2,0),
                                     sqrt( pose.linear()(2,1) * pose.linear()(2,1) +
                                           pose.linear()(2,2) * pose.linear()(2,2)  )
                                     );
                float gamma = atan2(  pose.linear()(2,1), pose.linear()(2,2) );

                std::cout << "alpha: " << alpha << " " << alpha * 180.f / M_PI << std::endl;
                std::cout << "beta: "  << beta  << " " << beta  * 180.f / M_PI << std::endl;
                std::cout << "gamma: " << gamma << " " << gamma * 180.f / M_PI << std::endl;
            }