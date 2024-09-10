Quaternion XFormNode::get_rotation(long time) const
{
    Animation *anim = anims[curr_anim];

    /*if the <vector> is empty return an identity quaternion.*/
    if(anim->rotation_is_empty()){
        return Quaternion();
	}

    KeyframeQuat first_keyframe = anim->get_rotation_keyframe(0);
    KeyframeQuat last_keyframe = anim->get_rotation_keyframe(anim->get_rotation_count() - 1);

    long start_time=first_keyframe.time; //start time of the animation.
    long full_interval=last_keyframe.time-start_time;//full duration of the animation.

    //animation loop algorithm----------
    if(full_interval && anim->is_loop_enabled()){
        time -= start_time;
        time %= full_interval;
        time += start_time;
	}
    //----------------------------------

    if(time < first_keyframe.time){
        return first_keyframe.r;
	}

    if(time >= last_keyframe.time){
        return last_keyframe.r;
	}

	long interval;
	double t;

    for(unsigned int i = 0 ; i < anim->get_rotation_count() - 1 ; i++){
        KeyframeQuat current = anim->get_rotation_keyframe(i);
        KeyframeQuat next = anim->get_rotation_keyframe(i + 1);

        if( (time >= current.time) && (time <= next.time) ){
            Quaternion tmp_rot;

            /*calculation of the interval between keyframes.*/
            interval = next.time - current.time;

            /*calculation of the interpolated parameter t.*/
            t = (double)(time - current.time) / (double)interval;

            /*Spherical linear interpolation--->>>SLERP!(cause we have rotations).*/
            tmp_rot = slerp(current.r , next.r , t);

            return tmp_rot;
		}
	}
	std::cout<<"Error: Rotation Keyframe not found!!!"<<std::endl;
    return Quaternion();
}