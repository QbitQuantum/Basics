void EarlyRegression(int Gid){

    char buf[512]; FILE *_fp = NULL;
    vector<Point6f> feat; vector<int> label;
    for(int gid = 2; gid < 3; ++gid){
        sprintf(buf, "FlowFeature/%i.txt", gid);
        _fp = fopen(buf, "r");
        float f[6] = {0};
        while(fscanf(_fp,"%f\t%f\t%f\t%f\t%f\t%f\n",&f[0],&f[1],&f[2],&f[3],&f[4], &f[5]) != EOF){
            feat.push_back(Point6f(f));
        } fclose(_fp);
        sprintf(buf, "FlowFeature/%d_gt.txt", gid);
        _fp = fopen(buf, "r"); int t = 0;
        while(fscanf(_fp,"%d\n", &t) != EOF) label.push_back(t);
        fclose(_fp);
    }
    float _fmin[6]={INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY};
    float _fmax[6]={-1,-1,-1,-1,-1,-1};
    Point6f fmin(_fmin), fmax(_fmax);
    for(int i = 0; i < feat.size(); ++i){ 
        fmin = min(fmin,feat[i]);
        fmax = max(fmax,feat[i]);
    }
    float fscore = 0, opt_rec = 0, opt_prec = 0, grid = 1000;
    for(float th = fmin.u; th < fmax.u; th += (fmax.u-fmin.u)/grid){
        for(float th2 = fmin.x; th2 < fmax.x; th2 += (fmax.x-fmin.x)/grid){
            int tp(0),fp(0),fn(0),tn(0);
            for(int i = 0 ; i < feat.size(); ++i){
                if(feat[i].u > th && feat[i].x > th2 ){
                    if(label[i] == 1)++tp;
                    else ++fp;
                }else{
                    if(label[i] == 1)++fn;
                    else ++tn;
                }
            }
            float _prec = float(tp)/float(max(1,tp+fp)), _rec = float(tp)/float(max(1,tp+fn));
            float _f1 = F_Measure(2.0, _prec, _rec);
            if(_f1 > fscore){ fscore = _f1, opt_rec = th;}
        }
    }
    
    for(int g = 0; g < DATASET_SIZE; g++){ /*for all data*/
        sprintf(buf, "FlowFeature/%i.txt", g);
        _fp = fopen(buf, "r");
        float f[6]; feat.clear(); label.clear();
        while(fscanf(_fp,"%f\t%f\t%f\t%f\t%f\t%f\n",&f[0],&f[1],&f[2],&f[3],&f[4], &f[5]) != EOF){
            feat.push_back(Point6f(f));
        } fclose(_fp);
        sprintf(buf, "FlowFeature/%d_gt.txt", g);
        _fp = fopen(buf, "r"); int t = 0;
        while(fscanf(_fp,"%d\n", &t) != EOF) label.push_back(t);
        fclose(_fp);
        
        ////////////////////////////
        int tp(0),fp(0),fn(0),tn(0);
        for(int i = 0 ; i < feat.size(); ++i){
            
            if(feat[i].u > opt_rec && feat[i].x > opt_prec){
                if(label[i] == 1)++tp;
                else ++fp;
            }else{
                if(label[i] == 1)++fn;
                else ++tn;
            }
        }
        float _prec = float(tp)/float(max(1,tp+fp)), _rec = float(tp)/float(max(1,tp+fn));
        float _f1 = 2.0*_prec*_rec/max(1.0f,(_prec+_rec));
        printf("\n[%d]CMAT[+/-: %d,%d][PRF:%f; %f; %f]\n", g, int(tp+fn), int(fp+tn), _prec, _rec, _f1);
        printf("%d\t%d\n%d\t%d\n", tp, fp, fn, tn);
        printf("Accuracy:[%f]\n\n", float(tp+tn)/float(tp+fp+fn+tn));
    }
}