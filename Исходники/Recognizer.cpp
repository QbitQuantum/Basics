void do_states()
{
    ros::Rate loop_rate(50);
    while(ros::ok())
    {
        switch(state)
        {
            case IDLE:

               break;
            case COLLECT_FACES:
                numFaces = 0;
                faces.clear();
                collectFaces = true;
                img_sub = it->subscribe("/ardrone/image_raw", 1,&imageCb);
                state = IDLE;
                break;
            case RECOGNIZE:
                img_sub.shutdown();
                vector<Mat> reconstructedFaces;
                // Calculate reconstructed faces
                for(int i = 0; i< faces.size(); i++)
                {
                    reconstructedFaces.push_back(recognizer->reconstructFace(faces[i]));
                }
                // Calculate L2-error to see if the person is in the database
                vector<bool> inDatabase;
                for(int i = 0; i< faces.size(); i++)
                {
                    double L2 = recognizer->calculateL2error(faces[i], reconstructedFaces[i]);
                    inDatabase.push_back(L2 < UNKNOWN_PERSON_THRESHOLD);
                }
                // Predict person only on faces with OK L2-error
                vector<int> labels;
                for(int i = 0; i<faces.size(); i++)
                {
                    if(inDatabase[i])
                    {
                        labels.push_back(recognizer->predict(faces[i]));
                    }
                }
                if(labels.size() == 0){
                    publish_identity(-1);
                    ROS_INFO("Identity unknown! Not in database");
                    publish_identity(-1);
                    state = IDLE;
                    break;
                }
                vector<int> votes(10);

                // Take the majority vote
                for(int i = 0; i< labels.size(); i++)
                {
                    int pos = labels[i];
                    votes[pos] = votes[pos] + 1;
                }
                int identity = -1;
                int maxVotes = -1;
                for(int i = 0; i< votes.size(); i++)
                {
                    if(votes[i] > maxVotes)
                    {
                        identity = i;
                        maxVotes = votes[i];
                    }
                }
                publish_identity(identity);
                state = IDLE;
                break;
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
}