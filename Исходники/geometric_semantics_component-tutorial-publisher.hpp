    Geometric_semantics_component_tutorial_publisher(string const& name)
        : TaskContext(name)
        , object_PoseCoordinatesSemantics("a","a","A","b","b","B","b")
        , xpos(0)
        , ypos(0)
        , zpos(0)
    {
        object_PoseCoordinatesSemantics = PoseCoordinatesSemantics("e1","e1","E1","b1","b1","B1","b1");

        transform.setOrigin( tf::Vector3(1,2,3) );
        transform.setRotation(tf::createQuaternionFromRPY(0.2, 0, 0) );
        object_coordinates_Pose.setOrigin( tf::Vector3(1,2, 0.0) );
        object_coordinates_Pose.setRotation( tf::createQuaternionFromRPY(0.75, 0, 0) );

        //geometric_semantics::Pose<tf::Pose> object_PoseCoordinatesTF(conversions_geometric_msgs::PoseTFFromMsg(*msg))
        object_PoseTF = geometric_semantics::Pose<tf::Pose> (object_PoseCoordinatesSemantics, object_coordinates_Pose);

        propPose= conversions_geometric_msgs::PoseTFToMsg(object_PoseTF);

        /****************************
          Pose
         **************************/
        // Pose
        this->addPort( "outPortPose", outPortPose).doc( "Output Port for Pose." );
        this->addProperty( "propPose", propPose).doc( "Property for Pose." );

        log(Debug) << "Geometric_semantics_component_tutorial_publisher constructed !" <<endlog();

    }