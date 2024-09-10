// The 'computeSliceSpacing' method
double LoadSeriesThread::computeSliceSpacing(OrthancClient::Series& series) const
{
    OrthancClient::Instance instance = series.GetInstance(0);
    instance.LoadTagContent("0020-0032"); // ImagePositionPatient
    QString pos1 = instance.GetLoadedTagContent().c_str();
    QStringList pos1s = pos1.split("\\");
    Vector3D pos1vector(pos1s.at(0).toDouble(), pos1s.at(1).toDouble(),
                        pos1s.at(2).toDouble());

    instance.LoadTagContent("0020-0037"); // ImageOrientationPatient
    QString or1 = instance.GetLoadedTagContent().c_str();
    QStringList or1s = or1.split("\\");
    Vector3D v(or1s.at(0).toDouble(), or1s.at(1).toDouble(), or1s.at(2).toDouble());
    Vector3D w(or1s.at(3).toDouble(), or1s.at(4).toDouble(), or1s.at(5).toDouble());

    Vector3D n = v.crossProduct(w);
    n.normalize();

    double min = -1;
    for(unsigned int i = 1 ; i < series.GetInstanceCount() ; i++) // TODO normally one can be enough but some bug forced me to search for the minest
    {
        OrthancClient::Instance instance2 = series.GetInstance(i);
        instance2.LoadTagContent("0020-0032");
        QString pos2 = instance2.GetLoadedTagContent().c_str();
        QStringList pos2s = pos2.split("\\");
        Vector3D pos2vector(pos2s.at(0).toDouble(), pos2s.at(1).toDouble(),
                            pos2s.at(2).toDouble());

        double dist = fabs(n.dotProduct(pos1vector-pos2vector));
        if(dist < min || min < 0)
            min = dist;
    }

    return min;
}