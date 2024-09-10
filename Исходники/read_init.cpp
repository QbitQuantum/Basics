void READ_INIT :: read(char* src_ip, int* src_port, char* sin_ip, int* sin_port, VECTOR* pPos, VECTOR* ePos, float* pR, float* eR) {
    char tmp[32];
    float x=0, y=0, z=0;
    fscanf_s(fp, "%s\n", tmp, 32);
    fscanf_s(fp, "x = %f\n", &x);
    fscanf_s(fp, "y = %f\n", &y);
    fscanf_s(fp, "z = %f\n", &z);
    fscanf_s(fp, "rotate = %f\n", pR);
    fscanf_s(fp, "ip = %s\n", src_ip, 15);
    fscanf_s(fp, "port = %d\n", src_port);
    pPos->x = x;
    pPos->y = y;
    pPos->z = z;

    fscanf_s(fp, "%s\n", tmp, 32);
    fscanf_s(fp, "x = %f\n", &x);
    fscanf_s(fp, "y = %f\n", &y);
    fscanf_s(fp, "z = %f\n", &z);
    fscanf_s(fp, "rotate = %f\n", eR);
    fscanf_s(fp, "ip = %s\n", sin_ip, 15);
    fscanf_s(fp, "port = %d", sin_port);
    ePos->x = x;
    ePos->y = y;
    ePos->z = z;
}