void XYSeries::addPoints(QVariantList data)
{
    ChartPoint *point;
    for(int i=0;i<data.length();++i){
        point = new ChartPoint(data.at(i).toMap(), this);
        dataList.append(point);
        connect(point, &ChartPoint::xChanged, this, &XYSeries::calculateDataRange);
        connect(point, &ChartPoint::yChanged, this, &XYSeries::calculateDataRange);
    }
    calculateDataRange();
    emit dataChanged();
}