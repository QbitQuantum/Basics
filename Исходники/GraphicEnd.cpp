void GraphicEnd::lostRecovery()
{
    //以present作为新的关键帧
    cout<<BOLDYELLOW<<"Lost Recovery..."<<RESET<<endl;
    //把present中的数据存储到current中
    _currKF.id ++;
    _currKF.planes = _present.planes;
    _currKF.frame_index = _index;
    _lastRGB = _currRGB.clone();
    _kf_pos = _robot;

    //waitKey(0);
    _keyframes.push_back( _currKF );
    
    //将current关键帧存储至全局优化器
    SparseOptimizer& opt = _pSLAMEnd->globalOptimizer;
    //顶点
    VertexSE3* v = new VertexSE3();
    v->setId( _currKF.id );
    if (_use_odometry)
        v->setEstimate( _odo_this );
    else
        v->setEstimate( Eigen::Isometry3d::Identity() );
    opt.addVertex( v );

    //由于当前位置不知道,所以不添加与上一帧相关的边
    if (_use_odometry)
    {
        Eigen::Isometry3d To = _odo_last.inverse()*_odo_this;
        EdgeSE3* edge = new EdgeSE3();
        edge->vertices()[0] = opt.vertex( _currKF.id - 1 );
        edge->vertices()[1] = opt.vertex( _currKF.id );
        Eigen::Matrix<double, 6,6> information = Eigen::Matrix<double, 6, 6>::Identity();
        information(0, 0) = information(2,2) = information(1, 1) = information(3,3) = information(4,4) = information(5,5) = 1/(_error_odometry*_error_odometry);
        edge->setInformation( information );
        edge->setMeasurement( To );
        opt.addEdge( edge );
        _odo_last = _odo_this;
        _lost = 0;
        return;
    }
    //check loop closure
    for (int i=0; i<_keyframes.size() - 1; i++)
    {
        vector<PLANE>& p1 = _keyframes[ i ].planes;
        Eigen::Isometry3d T = multiPnP( p1, _currKF.planes ).T;
        
        if (T.matrix() == Eigen::Isometry3d::Identity().matrix()) //匹配不上
            continue;
        T = T.inverse();
        //若匹配上，则在两个帧之间加一条边
        EdgeSE3* edge = new EdgeSE3();
        edge->vertices() [0] = opt.vertex( _keyframes[i].id );
        edge->vertices() [1] = opt.vertex( _currKF.id );
        Eigen::Matrix<double, 6,6> information = Eigen::Matrix<double, 6, 6>::Identity();
        information(0, 0) = information(1,1) = information(2,2) = 100; 
        information(3,3) = information(4,4) = information(5,5) = 100; 
        edge->setInformation( information );
        edge->setMeasurement( T );
        edge->setRobustKernel( _pSLAMEnd->_robustKernel );
        opt.addEdge( edge );
    }
    
}