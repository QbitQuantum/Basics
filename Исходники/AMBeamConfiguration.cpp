QVector3D AMBeamConfiguration::findCenter(QVector<QVector3D> shape) const
{
    QVector3D sum(0,0,0);
    int count = 0;
    while(!shape.isEmpty())
    {
        sum += shape.first();
        shape.remove(0);
        count++;
    }
    return sum/count;

}