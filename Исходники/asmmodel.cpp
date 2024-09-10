void ASMModel::findParamForShapeBTSM(const ShapeVec &Y, const ShapeVec &Y_old,
                               FitResult & fitResult, FitResult &b_old, int l)
{
    //const double c[3] = {0.005, 0.005, 0.001};
    const double c[3] = {0.0005, 0.0005, 0.0005};
    
    double rho2, delta2, x2;
    double p;
    ShapeVec y_r, y_rpr, xFromParam, xFromY, x;
    
    ShapeVec yt = Y_old;
    yt -= Y;
    rho2 = c[l] * yt.dot(yt);
    
    SimilarityTrans curTrans = b_old.transformation;
    Mat_< double > curParam, tmpFullParam, lastParam;
    
    curParam.create(pcaPyr[l].eigenvalues.rows, 1);
    for (int i=0; i<pcaPyr[l].eigenvalues.rows; i++)
        if (i<b_old.params.rows)
            curParam(i, 0) = b_old.params(i, 0);
        else
            curParam(i, 0) = 0;
    //curParam = curParam.rowRange(0, pcaPyr[l].eigenvalues.rows);
    
    int ii=0;
    do{
        double s = curTrans.getS();
        lastParam = curParam.clone();
        
        // Expectation Step
        curTrans.backTransform(Y, y_r);
        p = sigma2Pyr[l]/(sigma2Pyr[l] + rho2/(s * s));
        //printf("p: %g, rho2/s2: %g, sigma2: %g\n", p, rho2/(s * s), sigma2Pyr[l]);
        delta2 = 1/(1/sigma2Pyr[l] + s*s / rho2);
//         printf("p: %g, rho2/s2: %g, sigma2: %g, delta2: %g\n", 
//                p, rho2/(s * s), sigma2Pyr[l], delta2);
        
        this->pcaPyr[l].backProject(curParam, xFromParam);
        
        pcaFullShape->project(y_r, tmpFullParam);
        pcaFullShape->backProject(tmpFullParam, y_rpr);
        x = p*y_rpr + (1-p) * xFromParam;
        x2 = x.dot(x) + (x.rows - 4) * delta2;
//         printf("p: %g, rho2/s2: %g, sigma2: %g, delta2: %g, x.x: %g, x2: %g\n", 
//                p, rho2/(s * s), sigma2Pyr[l], delta2, x.dot(x), x2);
        
        // Maximization Step
        pcaPyr[l].project(x, curParam);
        
        for (int i=0; i<pcaPyr[l].eigenvalues.rows; i++)
            curParam(i, 0) *= (pcaShape->eigenvalues.at<double>(i, 0))/
                            (pcaShape->eigenvalues.at<double>(i, 0)+sigma2Pyr[l]);
        int nP = x.rows / 2;
        curTrans.a = Y.dot(x) / x2;
        curTrans.b = 0;
        for (int i=0; i<nP; i++)
            curTrans.b += x.X(i) * Y.Y(i) - x.Y(i)*Y.X(i);
        curTrans.b /= x2;
        curTrans.Xt = Y.getXMean();
        curTrans.Yt = Y.getYMean();
        
        //clampParamVec(curParam);
        ii++;
    } while (norm(lastParam-curParam)>1e-4 && ii<20);
    fitResult.params = curParam;
    fitResult.transformation = curTrans;
}