void AAM::train(vector<Mat> images, Mat shapes)
{
    this->images=images;
    this->shapeSet = shapes;
    //cout<<"training shape set:  "<<shapeSet<<endl;
    makeShapeModel();
    triangulateMeanPoints();
    //cout<<"shape pca counted"<<endl;
    this->meanConvexHull = this->createConvexHull(this->meanPoints);
    cout<<"convexHull"<<meanConvexHull<<endl;
    for(int i=0; i<this->images.size(); i++)
    {
        Mat image_grey;
        cvtColor(this->images[i], image_grey, COLOR_BGR2GRAY);
        Mat texture=this->getTetureInShape(image_grey, this->shapeSet.row(i));
        //cout<<"texture smapled and normalized: "<<texture<<endl;
        this->addTexture(texture);
    }
    makeTextureModel();
    this->displayModel();
    getW();
    makeApearanceModel();
    this->countA();
    cout<<"A: "<<this->A<<endl;
    cout<<"AAM training complete"<<endl;

}