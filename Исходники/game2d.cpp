void
Game2D::
init (){
    state_=0;
    score_=0;
    time_=0;
    direction_=0;
    movable_=0;

    delay_=DEFAULT_SPEED_DELAY;

    if (!bg_.isLoad ()){
        bg_.loadImage ("bg.png");
    }

    killTimer (timer_id_);
    timer_id_=startTimer (delay_);
}