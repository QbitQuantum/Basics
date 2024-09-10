Wall::Wall(vector3 pos, vector3 dir, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, string texture_path):
            LevelDelimiter(pos,dir.normalize(),vector3(0.0,1.0,0.0),vertex1,vertex2,vertex3,vertex4,texture_path)
{
    const_term = dir[0]*vertices[0]+dir[1]*vertices[1]+dir[2]*vertices[2];
    square_root = sqrt(dir[0]*dir[0]+dir[1]*dir[1]+dir[2]*dir[2]);
    build_bounding_box();
    GLfloat orizzontal = ((int)length)/2;
    GLfloat vertical = ((int)height)/5;
    GLfloat texc[8] = { 0.0,0.0,
            orizzontal,0.0,
            orizzontal,vertical,
            0.0,vertical};
    memcpy(texcoords, texc, sizeof(GLfloat)*8);
}