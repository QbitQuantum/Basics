void* map_run(void *junk){
    int start = clock() / CLOCKS_PER_SEC;
    while (ros::ok()) {
		//ROS_INFO("start");
        if (feedbackKey || goalKey || getKey || mapKey ) continue;
        if (clock() / CLOCKS_PER_SEC - start < 2) {
            /*
            if (mapDataInit[Now.y*width+Now.x] == -1) {
                start = clock() / CLOCKS_PER_SEC;
                if (getKey) continue;
                ROS_INFO("get again");
                int pathLen = getPath();
                while (getKey);
                if (pathLen == 0) {
                    ROS_INFO("I can't get there!!!");
                } else if (pathLen == 1) {
                    printf("now Point is %d\n", nowPoint);
                    bitathome_navigation_control::MyPoint ret;
                    ret.x = (PATH[nowPoint].x - Start.x) * pointSize;
                    ret.y = (PATH[nowPoint].y - Start.y) * pointSize;
                    ret.z = goalData.z;
                    ret.say = goalData.say;
                    goalPoint_pub.publish(ret);
                } else {
                    printf("now Point is %d\n", nowPoint);
                    bitathome_navigation_control::MyPoint ret;
                    ret.x = (PATH[nowPoint].x - Start.x) * pointSize;
                    ret.y = (PATH[nowPoint].y - Start.y) * pointSize;
                    ret.z = euler_angles[PATH[nowPoint].ddir];
                    ret.say = "";
                    goalPoint_pub.publish(ret);
                }
            }
            */
			//ROS_INFO("<100000");
			//printf("clock is %d", clock() / CLOCKS_PER_SEC - start);
            if (abs(Now.x - PATH[nowPoint].x) < 5 && abs(Now.y - PATH[nowPoint].y) < 5 && !getKey) {
                //printf("now Point is %d\n", nowPoint);
                if (nowPoint + 1 >= PATH.size() && !getKey) {
                    continue;
                }
                else if (nowPoint + 2 == PATH.size() && !getKey) {
                    printf("now Point is %d\n", nowPoint);
                    nowPoint ++;
                    bitathome_navigation_control::MyPoint ret;
                    ret.x = (PATH[nowPoint].x - Start.x) * pointSize;
                    ret.y = (PATH[nowPoint].y - Start.y) * pointSize;
                    ret.z = goalData.z;
                    ret.say = goalData.say;
                    goalPoint_pub.publish(ret);
                } else if (!getKey){
                    printf("now Point is %d\n", nowPoint);
                    nowPoint ++;
                    bitathome_navigation_control::MyPoint ret;
                    ret.x = (PATH[nowPoint].x - Start.x) * pointSize;
                    ret.y = (PATH[nowPoint].y - Start.y) * pointSize;
                    ret.z = euler_angles[PATH[nowPoint].ddir];
                    ret.say = "";
                    goalPoint_pub.publish(ret);
                }
            }
        } else {
            start = clock() / CLOCKS_PER_SEC;
            if (getKey) continue;
            //bitathome_navigation_control::MyPoint ret;
            //ret.x =  feedbackData.position.x;
            //ret.y = feedbackData.position.y;
            //double z[3];
            //tf::Quaternion q(feedbackData.orientation.x, feedbackData.orientation.y, feedbackData.orientation.z, feedbackData.orientation.w);
            //tf::Matrix3x3 m(q);
            //m.getRPY(z[0], z[1], z[2]);
            //ret.z = z[2];
            //ret.say = "";
            //goalPoint_pub.publish(ret);
			ROS_INFO("get again");
            int pathLen = getPath();
            while (getKey);
            if (pathLen == 0) {
                ROS_INFO("I can't get there!!!");
            } else if (pathLen == 1) {
                printf("now Point is %d\n", nowPoint);
                bitathome_navigation_control::MyPoint ret;
                ret.x = (PATH[nowPoint].x - Start.x) * pointSize;
                ret.y = (PATH[nowPoint].y - Start.y) * pointSize;
                ret.z = goalData.z;
                ret.say = goalData.say;
                goalPoint_pub.publish(ret);
            } else {
                printf("now Point is %d\n", nowPoint);
                bitathome_navigation_control::MyPoint ret;
                ret.x = (PATH[nowPoint].x - Start.x) * pointSize;
                ret.y = (PATH[nowPoint].y - Start.y) * pointSize;
                ret.z = euler_angles[PATH[nowPoint].ddir];
                ret.say = "";
                goalPoint_pub.publish(ret);
            }
        }
    }
}