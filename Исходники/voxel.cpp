void Voxelize::generateUmap(pcl::PointCloud<pcl::PointXYZ> &cloud,double resolution,boost::unordered_map<unordered_map_voxel,un_key> &m)//遍历每个点，生成栅格。然后计算每个栅格的参数
{
    double t0 = ros::Time::now().toSec();

    un_key tempp;  //key键不允许修改，全存在value中

    for(int i=0;i<cloud.size();i++)
    {
        unordered_map_voxel tempv(cloud[i].x,cloud[i].y,cloud[i].z,resolution);

        pair<umap::iterator,bool> pair_insert = m.insert(umap::value_type(tempv,tempp));//这个pair就是用来存储插入返回值的，看是否这个栅格已经存在

        pair_insert.first->second.vec_index_point.push_back(i);
        /*
           if(!pair_insert.second)//如果栅格已经存在，那么把value++
           {
           (pair_insert.first)->second.cout++;
           pair_insert.first->second.vec_index_point.push_back(i);
           }
           else{
           pair_insert.first->second.vec_index_point.push_back(i);
           }
           */
    }

    double t2 = ros::Time::now().toSec();
    //cout <<"划栅格的时间为"<<(t2-t0)<<endl;
    Matrix3d tempmat;
    tempmat.setZero();

    pcl::PointXYZ temppoint(0,0,0);
    for(umap::iterator iter=m.begin();iter!=m.end();)
    {
        temppoint.x=temppoint.y=temppoint.z=0;
        if(iter->second.vec_index_point.size()<10)
        {
            m.erase(iter++);
            continue;
        }

        for(int j = 0;j<iter->second.vec_index_point.size();j++)
        {
            double x_ = cloud[iter->second.vec_index_point[j]].x;
            double y_ = cloud[iter->second.vec_index_point[j]].y;
            double z_ = cloud[iter->second.vec_index_point[j]].z;

            tempmat += (Vector3d(x_,y_,z_) * RowVector3d(x_,y_,z_));//存储pipiT的和
            temppoint.x += x_;
            temppoint.y += y_;
            temppoint.z += z_;
        }

        int n = iter->second.vec_index_point.size();
        //cout <<"栅格大小为"<<n<<endl;
        Vector3d v(temppoint.x/n,temppoint.y/n,temppoint.z/n);//存储栅格重心
        RowVector3d vT(temppoint.x/n,temppoint.y/n,temppoint.z/n);

        tempmat /= n;
        tempmat -= v*vT;//S
        iter->second.matS = tempmat;
        //cout <<"S 矩阵= "<< tempmat <<endl;

        vector<eigen_sort> vector1(3);//用于排序

        //cout <<"tempmat="<<endl<<tempmat<<endl;
        EigenSolver<MatrixXd> es(tempmat);
        VectorXcd eivals = es.eigenvalues();
        MatrixXcd eigenvectors = es.eigenvectors();
        //cout << "特征值="<<eivals<<endl;
        vector1[0]=eigen_sort(eivals(0).real(),es.eigenvectors().col(0));
        vector1[1]=eigen_sort(eivals(1).real(),es.eigenvectors().col(1));
        vector1[2]=eigen_sort(eivals(2).real(),es.eigenvectors().col(2));
        sort(vector1.begin(),vector1.end());
        double lamada1 = vector1[0].eigen_value;
        double lamada2 = vector1[1].eigen_value;
        double lamada3 = vector1[2].eigen_value;
        //cout <<"lamada="<<lamada1<<" "<<lamada2<<" "<<lamada3<<endl;
        //
        if(vector1[0].eigen_vector(2).real()<0)
        {
            vector1[0].eigen_vector(2).real() = -vector1[0].eigen_vector(2).real();
        }
        if(vector1[2].eigen_vector(2).real()<0)
        {
            vector1[2].eigen_vector(2).real() = -vector1[2].eigen_vector(2).real();
        }


        iter->second.c = (lamada3-lamada2)/(lamada1+lamada2+lamada3);
        iter->second.p = 2*(lamada2-lamada1)/(lamada1+lamada2+lamada3);
        iter->second.u = v;
        iter->second.v1 = vector1[0].eigen_vector;
        iter->second.v3 = vector1[2].eigen_vector;

        double c = iter->second.c;
        double p = iter->second.p;


        iter->second.vector_9D << v(0),v(1),v(2),p*vector1[0].eigen_vector(0).real(),p*vector1[0].eigen_vector(1).real(),
            p*vector1[0].eigen_vector(2).real(),c*vector1[2].eigen_vector(0).real(),c*vector1[2].eigen_vector(1).real(),
            p*vector1[2].eigen_vector(2).real();

        //cout << "9D向量="<<iter->second.vector_9D<<endl;
        //ArrayXd ad = iter->second.vector_9D;
        //cout <<"ad = "<<ad<<endl;
        //cout <<"ad square="<<ad.square()<<endl;
        tempmat.setZero();

        iter++;

    }

    double tn = ros::Time::now().toSec();
    //cout << "对栅格计算处理的时间"<<(tn - t2)<<endl;
    //cout <<"栅格数量为" <<m.size()<<endl;

}