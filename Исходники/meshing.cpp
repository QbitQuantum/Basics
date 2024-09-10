bool Meshing::isGood()
{
    //Test poly
    for(int i=0;i<original_.size()-1;i++){
        QLineF line(original_.at(i),original_.at(i+1));
        if(intersects(original_,line)){
            qDebug() << "Invalid polygon";
            return false;
        }
    }
    return true;
}