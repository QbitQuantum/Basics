Camera* DefFileReader::loadCamera( std::string filePath )
{
    float x, y, z;
    int n;
    char param_name[16];
    bool errors = false;
    FILE* fp = fopen(filePath.c_str(), "r");
    if (!fp)
    return 0;

    /* Lendo a posicao do observador */
    Vector4D eye;
    fscanf(fp, "%s ", param_name);
    if (strcmp(param_name, "eye=") == 0)
    {
        fscanf(fp, "%f %f %f", &x, &y, &z);
        eye.x = x;
        eye.y = y;
        eye.z = z;
        eye.w = 1.0;
    }
    else errors = true;
    
    /* Lendo a direcao de visao */
    Vector4D at;
    fscanf(fp, "%s ", param_name);
    if (strcmp(param_name, "at=") == 0)
    {
        fscanf(fp, "%f %f %f", &x, &y, &z);
        at.x = x;
        at.y = y;
        at.z = z;
        at.w = 1.0;
    }
    else errors = true;
    
    /* Lendo o "view-up" */
    Vector4D up;
    fscanf(fp, "%s ", param_name);
    if (strcmp(param_name, "up=") == 0)
    {
        fscanf(fp, "%f %f %f", &x, &y, &z);
        up.x = x;
        up.y = y;
        up.z = z;
        up.w = 1.0;
    }
    else errors = true;
    
    /* Lendo o fovy */
    float fovy;
    fscanf(fp, "%s ", param_name);
    if (strcmp(param_name, "fovy=") == 0)
    {
        fscanf(fp, "%f ", &x);
        fovy = x;
    }
    else errors = true;
    
    /* Lendo o near plane */
    float near;
    fscanf(fp, "%s ", param_name);
    if (strcmp(param_name, "nearp=") == 0)
    {
        fscanf(fp, "%f ", &x);
        near = x;
    }
    else errors = true;  
    
    /* Lendo o far plane */
    float far;
    fscanf(fp, "%s ", param_name);
    if (strcmp(param_name, "farp=") == 0)
    {
        fscanf(fp, "%f ", &x);
        far = x;
    }
    else errors = true;
    
    /* Lendo a largura da janela */
    int width;
    fscanf(fp, "%s ", param_name);
    if (strcmp(param_name, "screenW=") == 0)
    {
        fscanf(fp, "%d ", &n);
        width = n;
    }
    else errors = true;
    
    /* Lendo a altura da janela */
    int height;
    fscanf(fp, "%s ", param_name);
    if (strcmp(param_name, "screenH=") == 0)
    {
        fscanf(fp, "%d ", &n);
        height = n;
    }
    else errors = true;
    
    fclose(fp);
    
    if( errors )
    {
        printf("Ocorreram erros ao ler o arquivo .cam\n");
        exit(1);
    }
    
    return new Camera( eye, at, up, fovy, near, far, width, height );
}