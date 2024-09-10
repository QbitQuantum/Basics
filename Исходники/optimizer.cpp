void Optimizer::eachCloudPair(CloudPair &pair)
{
    int cloud0 = pair.corresIdx.first;
    int cloud1 = pair.corresIdx.second;

    size_t matrix_size = m_pointClouds.size() * 6;

    TriContainer mat_elem;
    mat_elem.reserve(matrix_size * matrix_size / 5);
    SparseMatFiller filler(mat_elem);

    for (int i = 0; i < 6; ++i) {
        filler.add(i, i, 1.0);
    }

    Vec atb(matrix_size);
    Mat ata(matrix_size, matrix_size);
    atb.setZero(), ata.setZero();

    double score = 0.0;
    {
        //pcl::ScopeTime time("calculate LSE matrix");
    
#pragma unroll 8
        for (size_t point_count = 0; point_count < pair.corresPointIdx.size(); ++point_count) {
            int point_p = pair.corresPointIdx[point_count].first;
            int point_q = pair.corresPointIdx[point_count].second;
            PointType P = m_pointClouds[cloud0]->points[point_p];
            PointType Q = m_pointClouds[cloud1]->points[point_q];

            Eigen::Vector3d p = P.getVector3fMap().cast<double>();
            Eigen::Vector3d q = Q.getVector3fMap().cast<double>();
            Eigen::Vector3d Np = P.getNormalVector3fMap().cast<double>();

            double b = -(p - q).dot(Np);
            score += b * b;
            Eigen::Matrix<double, 6, 1> A_p, A_q;
            A_p.block<3, 1>(0, 0) = p.cross(Np);
            A_p.block<3, 1>(3, 0) = Np;
            A_q.block<3, 1>(0, 0) = -q.cross(Np);
            A_q.block<3, 1>(3, 0) = -Np;
        
            filler.fill(cloud0, cloud1, A_p, A_q);
            atb.block<6, 1>(cloud0 * 6, 0) += A_p * b;
            atb.block<6, 1>(cloud1 * 6, 0) += A_q * b;
        }
        ata.setFromTriplets(mat_elem.begin(), mat_elem.end());
    }

    {
        //pcl::ScopeTime time("Fill sparse matrix");
        boost::mutex::scoped_lock lock(m_cloudPairMutex);
        //std::cout << "\tcurrent thread : " << boost::this_thread::get_id() << std::endl;
        //PCL_INFO("\tPair <%d, %d> alignment Score : %.6f\n", cloud0, cloud1, score);
        ATA += ata;
        ATb += atb;
        align_error += score;
    }
}