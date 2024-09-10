int main(int argc, char **argv) {
    PLYReader ply_reader;
    PCDWriter pcd_writer;

    PointCloud<PointXYZRGB>::Ptr source_pointer (new PointCloud<PointXYZRGB>);
    PointCloud<PointXYZRGB>::Ptr target_pointer (new PointCloud<PointXYZRGB>);

    PointCloud<PointXYZRGB> output_cloud;

    std::string source_filename = argv[1];
    std::string target_filename = argv[2];

    ply_reader.read(source_filename, *source_pointer);
    ply_reader.read(target_filename, *target_pointer);

    IterativeClosestPoint<PointXYZRGB, PointXYZRGB> icp;


#if PCL_MINOR_VERSION > 6
    icp.setInputSource(source_pointer);
#else
    icp.setInputCloud(source_pointer);
#endif
    icp.setInputTarget(target_pointer);

    icp.align(output_cloud);

    pcd_writer.write("icp_test_face.pcd", output_cloud);

    return 0;
}