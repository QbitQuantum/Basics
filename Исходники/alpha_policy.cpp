/**
 * Loads a policy file.
 *
 * @return True on success.
 */
bool AlphaPolicy::loadFromFile(const char* path)
{
  int action;
  double alpha;
  std::vector<double> alphas;
  std::string line;
  bool alpha_line = false; // True for alpha line, false for action line. (Simple state machine.)

  // Open file.
  std::ifstream policy_file;
  policy_file.open(path);
  if(!policy_file.good())
  {
    ROS_ERROR_STREAM("Unable to open file " << path);
    return false;
  }

  // Check Policy has what it needs to read the file.
  ROS_ASSERT_MSG(state_space_, "Requires StateSpace to be initialized!");

  // Read file.
  while(!policy_file.eof())
  {
    std::getline(policy_file, line);
    if(policy_file.fail())
      continue;

    line = stripComment(line);
    if(isBlank(line))
      continue; // Skip line

    std::stringstream line_ss(line);

    // Action line
    if(!alpha_line)
    {
      // Read element from line.
      std::string action_str;
      line_ss >> action_str;
      if(line_ss.fail())
      {
        ROS_ERROR_STREAM("Invalid action line: '" << line << "'");
        return false;
      }

      // Convert to action.
      // Kludgy. @todo Change actions from ints to FeatureValues.
      shared_ptr<FeatureValue> action_obj = action_space_->readFeatureValue(action_str);
      action = boost::dynamic_pointer_cast<SimpleFeatureValue>(action_obj)->asInt();
      if(!action_space_->isValid(SimpleFeatureValue(action)))
      {
        ROS_ERROR_STREAM("Invalid action: '" << action_str << "'");
        return false;
      }

      actions_.push_back(action);
      alpha_line = true;
    }
    // Alpha line
    else if(alpha_line)