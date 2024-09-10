// decompose Drawable primitives into triangles, print out these triangles and computed normals.
void printTriangles(const std::string& name, osg::Drawable& drawable)
{
    std::cout<<name<<std::endl;

    osg::TriangleFunctor<NormalPrint> tf;
    drawable.accept(tf);

    std::cout<<std::endl;
}