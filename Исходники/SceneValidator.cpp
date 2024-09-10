/* checks if a given scene is in static equilibrium or not */
bool SceneValidator::isValidScene(std::vector<string> modelnames, std::vector<Eigen::Affine3d> model_poses){
    //set all the Objects's positions
    num = modelnames.size();
    for (int i =0; i < num; i++){
       auto mappedObject= m.find(modelnames[i]);   //get model from hashmap
       Eigen::Affine3d a = model_poses[i];
       const dMatrix3 R = {                        //convert affine info to a 3x3 rotation matrix and a x,y,z position array
         a(0,0), a(0,1), a(0,2),
         a(1,0), a(1,1), a(1,2),
         a(2,0), a(2,1), a(2,2)    };
       const dReal center[3] = {a.translation()[0],a.translation()[1], a.translation()[2]};
       translateObject(mappedObject->second, center, R);  //get the model name's MyObject info and feed it the position and rotation
    }

    //complete series of checks to see if scene is still stable or not
    if (!isStableStill(modelnames, STEP1)){   //check #1
         return false;
    } else
    if (!isStableStill(modelnames, STEP2)){   //check #2
         return false;
    } else
    if (!isStableStill(modelnames, STEP3)){   //check #3
         return false;
    } else
    if (!isStableStill(modelnames, STEP4)){   //check #4
         return false;
    }
    else{
         return true;
    }
}