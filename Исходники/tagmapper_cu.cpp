// Main loop.
int main(int argc, char **argv)
{
  ros::init(argc, argv, "new_tagmapper_cu");
  ros::NodeHandle n;
  kill_pub = n.advertise<std_msgs::Int8>("/cu/killsg", 1000);
  pose_sub = n.subscribe("/cu/pose_cu", 1, pose_callback);
  marker_sub = n.subscribe("/cu/stargazer_marker_cu", 1, marker_callback);
  speeds_sub = n.subscribe("/speeds_bus", 1, speeds_callback);
  ros::Rate loop_rate(1000);

  isStopped = false;
  restart = false;
  poseSampleCount = 0;
  markerSampleCount = 0;
  lastTagLine = 0;
  memset(tagIDs, 0, PSEUDO_FILE_LINES*sizeof(int));
  tagCount = 0;
  currentTag = 0;

  // Open the file, read it in, extract the tag IDs, and determine the place to insert the new tag.
  int ifline = 0;
  std::ifstream psin;
  psin.open(pseudo_file, std::ifstream::in);
  if (!psin.good()) {
    return 1;
  }
  while (!psin.eof()) {
    psin.getline(pseudo_text[ifline], PSEUDO_FILE_LINE_WIDTH);
    ifline++;
  }
  psin.close();
  for (int i = 0; i < PSEUDO_FILE_LINES; i++) {
    if (strstr(pseudo_text[i], "/PseudoLiteMap")) {
      lastTagLine = i;
      break;
    }
  }
  for (int i = 0; i < lastTagLine; i++) {
    if (strstr(pseudo_text[i], "PseudoLite id")) {
      sscanf(pseudo_text[i], "    <PseudoLite id=\"%d\"", &tagIDs[tagCount]);
      tagCount++;
    }
  }

  // Run the main loop.  If the new tag samples have all been retrieved and the robot is stopped, save the tag, kill Stargazer, and then shut down.
  int count = 0;
  while (ros::ok())
  {
    if (poseSampleCount == SAMPLES && markerSampleCount == SAMPLES && isStopped) {
      saveTagInXml();
      publish_kill();
      break;
    }
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }

  kill_pub.shutdown();
  pose_sub.shutdown();
  marker_sub.shutdown();
  speeds_sub.shutdown();

  return 0;
}