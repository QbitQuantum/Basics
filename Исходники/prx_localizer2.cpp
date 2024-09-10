void
save_localize_transform()
{
    std::ofstream filed_transform;
	std::stringstream file_name;

	std::string path = ros::package::getPath("prx_localizer");
	file_name << path << "/transform/localize_transform.bin";
    filed_transform.open(file_name.str().c_str(), std::ofstream::binary|std::ofstream::trunc);

    tfScalar x, y, z, w;
    x = g_localize_transform.getRotation().getX();
    y = g_localize_transform.getRotation().getY();
    z = g_localize_transform.getRotation().getZ();
    w = g_localize_transform.getRotation().getW();
    filed_transform.write((char *) &x, sizeof(tfScalar));
    filed_transform.write((char *) &y, sizeof(tfScalar));
    filed_transform.write((char *) &z, sizeof(tfScalar));
    filed_transform.write((char *) &w, sizeof(tfScalar));

    x = g_localize_transform.getOrigin().getX();
    y = g_localize_transform.getOrigin().getY();
    z = g_localize_transform.getOrigin().getZ();
    filed_transform.write((char *) &x, sizeof(tfScalar));
    filed_transform.write((char *) &y, sizeof(tfScalar));
    filed_transform.write((char *) &z, sizeof(tfScalar));

    filed_transform.close();
}