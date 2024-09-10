void sktinfoextractor::hacerUpdate(){
    int hhh=cam->numContextosIniciados;
    if(cam->numContextosIniciados>0){
        if(numFrames==0){
#ifdef _WIN32 || _WIN64
            GetSystemTime(&inicio);
#else
            gettimeofday(&inicio,NULL);
#endif
        }
        bool* update=new bool[cam->numContextosIniciados];

        //if(cam->updateCam(true,0,true,false)){
        int tid;

        Moments moms;
        int b;
        Point2f pt;
        if(cam->numContextosIniciados>1){
            omp_set_num_threads(2);
#pragma omp parallel private(tid,moms,b,pt) shared(update)
            {
                /// TODO : FIX FOR LESS AVAILABLE THREADS THAN CONTEXTS
                tid = omp_get_thread_num();
                //if(tid!=0){
                //  tid--;
                cameras* cc=cam;
                if(tid<cc->numContextosIniciados){
                    if(cc->updateCam(false,tid,true,false)){
                        cc->retriveDepthAndMask(tid,depths[tid],masks[tid]);
                        cc->retrivePointCloudFast(tid,&(depths[tid]),&(pCs[tid]));
                        if(cConfig[tid]->method=="Background"){
                            depths[tid].convertTo(depthsS[tid],CV_32FC1,1.0/6000);
                            sktP[tid]->processImage(depthsS[tid],toBlobs[tid],masks[tid]);
                        }
                        else
                        {
                            sktP[tid]->processImage(pCs[tid],toBlobs[tid],masks[tid]);
                        }
                        findContours(toBlobs[tid], blobs[tid],CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
                        finBlobs[tid].clear();
                        blobSizes[tid].clear();
                        for(b=0; b<blobs[tid].size(); b++)
                        {
                            moms=moments(blobs[tid][b],true);
                            if(moms.m00>cConfig[tid]->minBlobSize)
                            {
                                //Point2f pt((int)(moms.m10 / moms.m00),(int)(moms.m01 / moms.m00));
                                //circle(toBlobs[k],pt,sqrt((double)moms.m00/3.14),cvScalar(255),-1);
                                //Save blob centers
                                pt.x=(int)(moms.m10 / moms.m00);
                                pt.y=(int)(moms.m01 / moms.m00);
                                finBlobs[tid].push_back(pt);
                                blobSizes[tid].push_back((int)moms.m00);
                            }
                        }
                        update[tid]=true;
                    }
                    else{update[tid]=false;}
                }
                //}
            }
        }
        else{
            if(cam->updateCam(false,0,true,false)){
                cam->retriveDepthAndMask(0,depths[0],masks[0]);
                cam->retrivePointCloudFast(0,&(depths[0]),&(pCs[0]));
                if(cConfig[0]->method=="Background"){
                    depths[0].convertTo(depthsS[0],CV_32FC1,1.0/6000);
                    sktP[0]->processImage(depthsS[0],toBlobs[0],masks[0]);
                }
                else
                {
                    sktP[0]->processImage(pCs[0],toBlobs[0],masks[0]);
                }
                findContours(toBlobs[0], blobs[0],CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
                finBlobs[0].clear();
                blobSizes[0].clear();
                for(b=0; b<blobs[0].size(); b++)
                {
                    moms=moments(blobs[0][b],true);
                    if(moms.m00>cConfig[0]->minBlobSize)
                    {
                        //Point2f pt((int)(moms.m10 / moms.m00),(int)(moms.m01 / moms.m00));
                        //circle(toBlobs[k],pt,sqrt((double)moms.m00/3.14),cvScalar(255),-1);
                        //Save blob centers
                        pt.x=(int)(moms.m10 / moms.m00);
                        pt.y=(int)(moms.m01 / moms.m00);
                        finBlobs[0].push_back(pt);
                        blobSizes[0].push_back((int)moms.m00);
                    }
                }
                update[0]=true;
            }
            else{update[0]=false;}
        }
        bool doUpdate=true;
        for(int i=0;i<cam->numContextosIniciados;i++){
            doUpdate=(doUpdate && update[i]);
        }
        if(doUpdate){
            vector<Point2f> ou=finBlobs[0];
            if(cam->numContextosIniciados>1 && update[1]){
                if(ui->mixActive->isChecked()){
                    //Run through blob centers and get 3d vector
                    //Convert 3d vectors to the first cam
                    int count=0;
                    XnPoint3D* rP=real;
                    Vec3f v;
                    //cout <<"SIZE : " << finBlobs[1].size() << endl;
                    for(int i=0;i<finBlobs[1].size();i++){
                        if(count<999 && calMat.cols>2){
                            /// POSIBLE SPEEDUP : USE POINTERS
                            v=pCs[1].at<Vec3f>(finBlobs[1][i].y,finBlobs[1][i].x);
                            ///
                            (*rP).X=v[0]*matC[0][0]+v[1]*matC[0][1]+v[2]*matC[0][2] +matC[0][3];
                            (*rP).Y=v[0]*matC[1][0]+v[1]*matC[1][1]+v[2]*matC[1][2] +matC[1][3];
                            (*rP).Z=v[0]*matC[2][0]+v[1]*matC[2][1]+v[2]*matC[2][2] +matC[2][3];
                            count++;rP++;}
                    }
                    //Convert results to projected in first cam
                    if(count >0)
                        cam->depthG[0].ConvertRealWorldToProjective(count,real,proj);

                    rP=proj;

                    for(int i=0;i<count;i++){
                        //circle(final,Point(proj[i].X,proj[i].Y),sqrt((double)blobSizes[1][i]/3.14),cvScalar(0,0,255),-1);
                        if(!hasCloseBlob2(rP,finBlobs[0],mD)){
                            //cout << "1 : "<< (int)(rP->X) << "," << (int)(rP->Y) << endl;
                            ou.push_back(Point2f(rP->X,rP->Y));
                        }
                        rP++;
                    }
                }
                else{
                    ou.insert(ou.end(), finBlobs[1].begin(), finBlobs[1].end() );
                }
            }
            if(sendTuio && isServerCreated){
                if(calSKT->isCalibrated){
                    calSKT->convertPointVector(&ou);
                }
                tds->sendCursors(ou,minDataUpdate);
            }
            if(useDC){
                if(calSKT->isCalibrated){
                    calSKT->convertPointVector(&ou);
                }
                dc->updateData(ou,minDataUpdate);
            }
            numFrames++;
        }
        if(numFrames==10){
            numFrames=0;

#ifdef _WIN32 || _WIN64
            SYSTEMTIME fin;
            GetSystemTime(&fin);
            double timeSecs=(double)(fin.wSecond+(double)fin.wMilliseconds/1000.0-((double)inicio.wMilliseconds/1000.0+inicio.wSecond))/10;
#else
            struct timeval fin;
            gettimeofday(&fin,NULL);
            double timeSecs=(double)(fin.tv_sec+(double)fin.tv_usec/1000000.0-((double)inicio.tv_usec/1000000.0+inicio.tv_sec))/10;
#endif
            //cout << timeSecs << endl;
            double dif=1.0/timeSecs;
            //cout << "FPS : " << dif <<endl;
            ui->framesPerSec->setText(QString::number(dif));
        }
        delete update;
    }
}