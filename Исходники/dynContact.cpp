//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool dynContact::checkVectorDim(const Vector &v, unsigned int dim, const string &descr){
    if(v.length() != dim){
        if(verbose)
            fprintf(stderr, "Error in dynContact: unexpected dimension of vector %s, %d\n", descr.c_str(), (int)v.length());
        return false;
    }
    return true;
}