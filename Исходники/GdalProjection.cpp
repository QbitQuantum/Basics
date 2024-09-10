/**
*@brief 点对点的转换
*@param poDataset [in] gdal数据集
*@param xyPeak [in] 左上顶点，和右下顶点的坐标{xl,yl,xr,yr}
*@param band [in] 波段数
*@param typeParam [in] 类型重载变量
*@return
*/
double *GdalProjection::PointToPoint(const char *fromWkt,const char *toWkt,double x,double y)
{
    OGRSpatialReference oSourceSRS,oTargetSRS;
    OGRCoordinateTransformation *poct;

    oSourceSRS.importFromWkt((char **) &fromWkt);
    oTargetSRS.importFromWkt((char **) &toWkt);

    poct = OGRCreateCoordinateTransformation(&oSourceSRS,&oTargetSRS);
    double *xy = (double *)malloc(sizeof(double) * 2);
    if (poct == NULL || !poct->Transform(1,&x,&y))
    {
        xy[0] = 0.0;
        xy[1] = 0.0;
    }
    else
    {
        xy[0] = x;
        xy[1] = y;
    }
    delete poct;
    return xy;
}