void Executer::transition_cb(ArmTaskClient::GoalHandle goal_handle)
{
    std::string state = goal_handle.getCommState().toString();

    ROS_DEBUG("transition_cb: %s", state.c_str());

    if (goal_handle == active_goal) {
        switch (goal_handle.getCommState().state_) {
        case actionlib::CommState::WAITING_FOR_GOAL_ACK:
        case actionlib::CommState::ACTIVE:
            // good
            break;
        default:
            // every other CommState will result in the goal being NOT active,
            // so we should stop the execution
            if (!is_done_) {
                ROS_INFO("current goal is not active (%s) -> stopping execution", state.c_str());
                is_done_ = true;
            }
            break;
        }
    }

    // cleanup old goal handles
    if (goal_handle.getCommState() == actionlib::CommState::DONE) {
        // we don't have the goal here, instead just search for the handle
        for (std::map<goal_key, ArmTaskClient::GoalHandle>::iterator it = goal_map.begin(); it != goal_map.end(); ) { // no it++ here
            ArmTaskClient::GoalHandle &cur = it->second;
            if (cur == goal_handle) {
                ROS_DEBUG("removed old goal from the goal_map");
                goal_map.erase(it++);
            } else {
                ++it;
            }
        }
    }
}