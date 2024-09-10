void
compute (const pcl::PCLPointCloud2::ConstPtr &source,
         const pcl::PCLPointCloud2::ConstPtr &target,
         pcl::PCLPointCloud2 &transformed_source)
{
    // Convert data to PointCloud<T>
    PointCloud<PointNormal>::Ptr src (new PointCloud<PointNormal>);
    PointCloud<PointNormal>::Ptr tgt (new PointCloud<PointNormal>);
    fromPCLPointCloud2 (*source, *src);
    fromPCLPointCloud2 (*target, *tgt);

    // Estimate
    TicToc tt;
    tt.tic ();

    print_highlight (stderr, "Computing ");

#define Scalar double
//#define Scalar float

    TransformationEstimationLM<PointNormal, PointNormal, Scalar>::Ptr te (new TransformationEstimationLM<PointNormal, PointNormal, Scalar>);
    //TransformationEstimationSVD<PointNormal, PointNormal, Scalar>::Ptr te (new TransformationEstimationSVD<PointNormal, PointNormal, Scalar>);
    CorrespondenceEstimation<PointNormal, PointNormal, double>::Ptr cens (new CorrespondenceEstimation<PointNormal, PointNormal, double>);
    //CorrespondenceEstimationNormalShooting<PointNormal, PointNormal, PointNormal>::Ptr cens (new CorrespondenceEstimationNormalShooting<PointNormal, PointNormal, PointNormal>);
    //CorrespondenceEstimationNormalShooting<PointNormal, PointNormal, PointNormal, double>::Ptr cens (new CorrespondenceEstimationNormalShooting<PointNormal, PointNormal, PointNormal, double>);
    cens->setInputSource (src);
    cens->setInputTarget (tgt);
    //cens->setSourceNormals (src);

    CorrespondenceRejectorOneToOne::Ptr cor_rej_o2o (new CorrespondenceRejectorOneToOne);

    CorrespondenceRejectorMedianDistance::Ptr cor_rej_med (new CorrespondenceRejectorMedianDistance);
    cor_rej_med->setInputSource<PointNormal> (src);
    cor_rej_med->setInputTarget<PointNormal> (tgt);

    CorrespondenceRejectorSampleConsensus<PointNormal>::Ptr cor_rej_sac (new CorrespondenceRejectorSampleConsensus<PointNormal>);
    cor_rej_sac->setInputSource (src);
    cor_rej_sac->setInputTarget (tgt);
    cor_rej_sac->setInlierThreshold (0.005);
    cor_rej_sac->setMaximumIterations (10000);

    CorrespondenceRejectorVarTrimmed::Ptr cor_rej_var (new CorrespondenceRejectorVarTrimmed);
    cor_rej_var->setInputSource<PointNormal> (src);
    cor_rej_var->setInputTarget<PointNormal> (tgt);

    CorrespondenceRejectorTrimmed::Ptr cor_rej_tri (new CorrespondenceRejectorTrimmed);

    IterativeClosestPoint<PointNormal, PointNormal, Scalar> icp;
    icp.setCorrespondenceEstimation (cens);
    icp.setTransformationEstimation (te);
    icp.addCorrespondenceRejector (cor_rej_o2o);
    //icp.addCorrespondenceRejector (cor_rej_var);
    //icp.addCorrespondenceRejector (cor_rej_med);
    //icp.addCorrespondenceRejector (cor_rej_tri);
    //icp.addCorrespondenceRejector (cor_rej_sac);
    icp.setInputSource (src);
    icp.setInputTarget (tgt);
    icp.setMaximumIterations (1000);
    icp.setTransformationEpsilon (1e-10);
    PointCloud<PointNormal> output;
    icp.align (output);

    print_info ("[done, ");
    print_value ("%g", tt.toc ());
    print_info (" ms : ");
    print_value ("%d", output.width * output.height);
    print_info (" points], has converged: ");
    print_value ("%d", icp.hasConverged ());
    print_info (" with score: %f\n",  icp.getFitnessScore ());
    Eigen::Matrix4d transformation = icp.getFinalTransformation ();
    //Eigen::Matrix4f transformation = icp.getFinalTransformation ();
    PCL_DEBUG ("Transformation is:\n\t%5f\t%5f\t%5f\t%5f\n\t%5f\t%5f\t%5f\t%5f\n\t%5f\t%5f\t%5f\t%5f\n\t%5f\t%5f\t%5f\t%5f\n",
               transformation (0, 0), transformation (0, 1), transformation (0, 2), transformation (0, 3),
               transformation (1, 0), transformation (1, 1), transformation (1, 2), transformation (1, 3),
               transformation (2, 0), transformation (2, 1), transformation (2, 2), transformation (2, 3),
               transformation (3, 0), transformation (3, 1), transformation (3, 2), transformation (3, 3));

    // Convert data back
    pcl::PCLPointCloud2 output_source;
    toPCLPointCloud2 (output, output_source);
    concatenateFields (*source, output_source, transformed_source);
}