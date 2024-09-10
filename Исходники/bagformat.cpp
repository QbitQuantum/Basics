void BagFormat::writeData(const ros::Time& time, const QVector< Plot::LinkedBufferIterator* >& data)
{
	plot_msgs::Plot msg;
	msg.header.stamp = time;

	Q_FOREACH(Plot::LinkedBufferIterator* it, data)
	{
		if(!it)
			continue;

		const Plot::DataPoint& p = **it;
		const Plot* plot = it->plot();

		plot_msgs::PlotPoint point;
		point.name = plot->path().toStdString();
		point.value = p.value;
		msg.points.push_back(point);
	}

	try
	{
		m_bag.write("plot", time, msg);
	}
	catch(rosbag::BagException& e)
	{
		fprintf(stderr, "Bag exception: %s\n", e.what());
		fprintf(stderr, "Time was %lf\n", time.toSec());
		throw;
	}
}