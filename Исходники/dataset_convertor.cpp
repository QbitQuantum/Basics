void writeCSVCamera(shared_ptr<ofstream> file, ros::Time stamp)
{
  std::stringstream ss;
  ss << stamp.toNSec() << "," << stamp.toNSec() << ".png";

  *file << ss.str() << endl;
}