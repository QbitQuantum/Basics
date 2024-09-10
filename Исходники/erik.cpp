void Erik::in_right(Uint16 dt) {
    if (state&STATE_RUN) {
        if (!(state&STATE_LEFT)) event->reset();
        //changed directions, TODO: play decelerate animation
        else cancelEvent();
    } else if (input->keyState(KEY_SP2)) {
        run_right=true;
        setEvent(new ERun(this,10000,maxspeedx,500,ESTATE_ABORT,au_run,anim_erik_run_right));
    }
    Player::in_right(dt);
}