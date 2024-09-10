/***Use to change the coordinates of the vertices and draw the Graph ***/
void Change_Vertex(void){
    /** Initial the zBuffer
     **/
    vector<vector<float>> zBuffer;
    vector<float> temp_zBuffer;
    for(int i=0;i<2000;i++)
    {
        temp_zBuffer.push_back(10000.0);
    }
    for(int j=0;j<2000;j++){
        zBuffer.push_back(temp_zBuffer);
    }
    
    glClearColor(1.0, 1.0, 1.0,0.0);
    
    
    
    /*********It is for file reading**********************/
    ifstream f(F_PATH);
    int numberOfVertices;
    int numberOfPolygons;
    int edegeOfPolyons;
    string temp;
    
    if(!f)
    {
        cout<<"No File!"<<endl;
        return ;
    }
    string s;
    
    
    getline(f, s);
    
    istringstream is(s);
    
    is>>temp;
    is>>temp;
    numberOfVertices=atoi(temp.c_str());
    
    is>>temp;
    numberOfPolygons=atoi(temp.c_str());
    
    
    
    float vertex_list[numberOfVertices][4];
    float edege_list[numberOfPolygons][20];
//    float vertex_list[100000][4];
//    float edege_list[100000][20];
    
    
    for(int i=0;i<numberOfVertices;i++){
        getline(f, s);
        istringstream is(s);
        is>>temp;
        vertex_list[i][0]=atof(temp.c_str());
        is>>temp;
        vertex_list[i][1]=atof(temp.c_str());
        is>>temp;
        vertex_list[i][2]=atof(temp.c_str());
        vertex_list[i][3]=1;
    }
    
    
    
    for(int i=0;i<=numberOfPolygons-1;i++){
        getline(f,s);
        istringstream is(s);
        is>>temp;
        edegeOfPolyons=atoi(temp.c_str());
        
        int j=0;
        for(j;j<=edegeOfPolyons-1;j++){
            is>>temp;
            edege_list[i][j]=atoi(temp.c_str());
        }
        
        for(j;j<=19;j++){
            edege_list[i][j]=-1;
        }
    }
    
    
    /**********file read ending *************************/
    
    //draw the 3D Graph
    
    Matrix4 finalMatrix=Integrated_Matrix();
    int range=(sizeof(vertex_list)/sizeof(vertex_list[0][0])/4);
    int edege_range=sizeof(edege_list)/sizeof(edege_list[0][0])/20-1;//
    float end_Vertex[range][3];
    
    Vector4 m;
    Vector4 tempVector;
    
    w=c-lookUpPoint;
    w.normalize();
    
    for(int i=0;i<range;i++){
        m.x=vertex_list[i][0];
        m.y=vertex_list[i][1];
        m.z=vertex_list[i][2];
        m.w=vertex_list[i][3];
        tempVector=finalMatrix*m;
        tempVector.x=tempVector.x/tempVector.w;
        tempVector.y=tempVector.y/tempVector.w;
        tempVector.z=tempVector.z/tempVector.w;
        
        
        
        end_Vertex[i][0]=tempVector.x;
        end_Vertex[i][1]=tempVector.y;
        end_Vertex[i][2]=tempVector.z;//tempVector.z;
        
    }
    
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    int tag=0;
    /*%%%%*/
    float le[1000],re[1000],tempZ;
    int i,j;      int flag;/*determine the negative value*/
    int overIndex; //when y1<0 and y2>0, try to make the fabs(y1),Howver,every y2 valus becomes y2+fabs(y1),so try this is the value of fabs(y1)
    
    for(i=0;i<1000;i++)
        le[i]=1000,re[i]=0;
    
    
    
    /*%%%%*/
    srand((unsigned)time(NULL));
    
    for(int x=0;x<=edege_range;++x)
    {
        flag=0;
        /**It is for hiding back face*****/
        Vector3 temp;
        Vector3 temp_a(vertex_list[(int)edege_list[x][1]-1][0]-vertex_list[(int)edege_list[x][0]-1][0],vertex_list[(int)edege_list[x][1]-1][1]-vertex_list[(int)edege_list[x][0]-1][1],vertex_list[(int)edege_list[x][1]-1][2]-vertex_list[(int)edege_list[x][0]-1][2]);
        Vector3 temp_b(vertex_list[(int)edege_list[x][2]-1][0]-vertex_list[(int)edege_list[x][1]-1][0],vertex_list[(int)edege_list[x][2]-1][1]-vertex_list[(int)edege_list[x][1]-1][1],vertex_list[(int)edege_list[x][2]-1][2]-vertex_list[(int)edege_list[x][1]-1][2]);
        Vector3 normal_vector=temp_a.crossProduct(temp_b);
        temp.x=vertex_list[(int)edege_list[x][0]-1][0]-c.x;
        temp.y=vertex_list[(int)edege_list[x][0]-1][1]-c.y;
        temp.z=vertex_list[(int)edege_list[x][0]-1][2]-c.z;
        
        if(normal_vector.dot(temp)<0){
            continue;
        }
        /***end for hiding back face***/
        
        /***use the OPENGL function to disply the graph***/
        
        
 //       glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        //glBegin(GL_POINTS);
        int j;
        for(j=0;j<19;j++)
        {
            if(edege_list[x][j+1]<0){  //when reach the end of the edege array
                break;
            }
            
            glVertex3fv(end_Vertex[(int)edege_list[x][j]-1]);
            glVertex3fv(end_Vertex[(int)edege_list[x][j+1]-1]);
            
            
            edgedetect(end_Vertex[(int)edege_list[x][j]-1][0],end_Vertex[(int)edege_list[x][j]-1][1],end_Vertex[(int)edege_list[x][j+1]-1][0],end_Vertex[(int)edege_list[x][j+1]-1][1],le,re,&flag,&overIndex);
        }
        glVertex3fv(end_Vertex[(int)edege_list[x][j]-1]);
        glVertex3fv(end_Vertex[(int)edege_list[x][0]-1]);
        
            edgedetect(end_Vertex[(int)edege_list[x][j]-1][0],end_Vertex[(int)edege_list[x][j]-1][1],end_Vertex[(int)edege_list[x][0]-1][0],end_Vertex[(int)edege_list[x][0]-1][1],le,re,&flag,&overIndex);
        tempZ=end_Vertex[(int)edege_list[x][j]-1][2]*1000;
        glEnd();

        cout<<"flag:"<<flag<<endl;
        cout<<"tempZ:"<<tempZ<<endl;
        
        
        float red=(float)rand()/RAND_MAX;
        float green=(float)rand()/RAND_MAX;
        float blue=(float)rand()/RAND_MAX;
//        cout<<"red:"<<red<<"green:"<<green<<"blue:"<<blue<<endl;
        
        for(j=0;j<1000;j++)
        {
            if(le[j]<=re[j])
            {
                if(flag==0)
                {
                    for(i=le[j];i<re[j];i++)
                    {
                        if(tempZ<=zBuffer[(int)i+1000][(int)j+1000])
                        {
                            draw_pixel(i,j,red,green,blue);
                            zBuffer[(int)i+1000][(int)j+1000]=tempZ;
                        }
                    }
                }
                if(flag==1)
                {
                    for(i=le[j];i<re[j];i++)
                    {
                        if(tempZ<=zBuffer[(int)i+1000][(int)-j+1000])
                        {
                            draw_pixel(i,-j,red,green,blue);
                            zBuffer[(int)i+1000][(int)-j+1000]=tempZ;
                        }
                    }
                }
                if(flag==2)
                {
                    if(j<overIndex)
                    {
                        for(i=le[j];i<re[j];i++)
                        {
                            if(tempZ<=zBuffer[(int)i+1000][(int)-j+1000])
                            {
                                draw_pixel(i,-j,red,green,blue);
                                zBuffer[(int)i+1000][(int)-j+1000]=tempZ;
                            }
                        }
                    }
                    else{
                        for(i=le[j];i<re[j];i++)
                        {
                            if(tempZ<=zBuffer[(int)i+1000][(int)j-overIndex+1000])
                            {
                                draw_pixel(i,j-overIndex,red,green,blue);
                                zBuffer[(int)i+1000][(int)j-overIndex+1000]=tempZ;
                            }
                        }
                    }
                    
                }
            }
        }
        for(i=0;i<1000;i++)
            le[i]=1000,re[i]=0;
    }
    
    
    glFlush();
    
    
}