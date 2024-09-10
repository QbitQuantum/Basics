void inverseTranspose(akMatrix4& mat)
{
    //TODO optimise
    akMatrix4 tmp = inverse(mat);
    mat = transpose(tmp);
}