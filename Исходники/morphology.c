//腐蚀
void Erode(double *src,int s_width,int s_height,double *dst,int d_width,int d_height,double *se,int se_width,int se_height,Position *center){
    
    if(center==NULL){
        Position temp;
        temp.x=se_width/2;
        temp.y=se_height/2;
        center=&temp;
    }
    MoveDirection m;
    double *temp=(double *)malloc(sizeof(double)*d_width*d_height);
    double *tempdst=(double *)malloc(sizeof(double)*d_width*d_height);
    double *realdst=(double *)malloc(sizeof(double)*d_width*d_height);
    Zero(realdst, d_width, d_height);
    Zoom(src,s_width,s_height,temp,d_width,d_height);
    for(int i=0;i<se_width;i++){
        for(int j=0;j<se_height;j++){
            if(se[j*se_width+i]>100.0){
                m.x=center->x-i;
                m.y=center->y-j;
                Translation(temp,tempdst,d_width,d_height, &m);
                And(tempdst, realdst, realdst,d_width,d_height);
            }
        }
    }
    matrixCopy(realdst, dst, d_width, d_height);
    free(temp);
    free(realdst);
    free(tempdst);
}