void step_rat(void) {
    // The keepout is used to know where to -not- put the paddle
    // the 'bouncepos' is where we expect the ball's y-coord to be when
    // it intersects with the paddle area
    static uint8_t right_keepout_top, right_keepout_bot;
    static uint8_t left_keepout_top, left_keepout_bot;
    static uint16_t dest_paddle_pos;
    static uint16_t right_dest, left_dest;

    // Save old ball location so we can do some vector stuff
    oldball_x = ball_x;
    oldball_y = ball_y;

    // move ball according to the vector
    ball_x += ball_dx;
    ball_y += ball_dy;



    /************************************* TOP & BOTTOM WALLS */
    // bouncing off bottom wall, reverse direction
//  if (ball_y  > (SCREEN_H_FIXED - BALL_RADIUS*2*FIXED_MATH - BOTBAR_H_FIXED)) {
    if (ball_y  > (SCREEN_H - BOTBAR_H - BALL_RADIUS*2)*FIXED_MATH) {
        //DEBUG(putstring_nl("bottom wall bounce"));
        ball_y = (SCREEN_H - BOTBAR_H - BALL_RADIUS*2)*FIXED_MATH;
        ball_dy = -ball_dy;
    }

    // bouncing off top wall, reverse direction
    if (ball_y < TOPBAR_H_FIXED) {
        //DEBUG(putstring_nl("top wall bounce"));
        ball_y = TOPBAR_H_FIXED;
        ball_dy = -ball_dy;
    }



    /************************************* LEFT & RIGHT WALLS */
    // the ball hits either wall, the ball resets location & angle
    if (   ((INT_MSB(ball_x))  > (SCREEN_W - BALL_RADIUS*2))
            || ((int8_t)(INT_MSB(ball_x)) <= 0)
            || ((ball_dx ==0) && (ball_dy==0))   ) {
        if(DEBUGGING) {
            if ((int8_t)(INT_MSB(ball_x)) <= 0) {
                putstring("Left wall collide");
                if (! minute_changed) {
                    putstring_nl("...on accident");
                } else {
                    putstring_nl("...on purpose");
                }
            } else {
                putstring("Right wall collide");
                if (! hour_changed) {
                    putstring_nl("...on accident");
                } else {
                    putstring_nl("...on purpose");
                }
            }
        }

        // place ball in the middle of the screen
        ball_x = (SCREEN_W/2 - BALL_RADIUS)*FIXED_MATH;
        ball_y = (SCREEN_H/2 - BALL_RADIUS)*FIXED_MATH;

// TODO JMM:  don't use cosine/sine... pick one randomly and calc the other one.
        int8_t angle = random_angle();
        ball_dx = (int16_t)  (((int32_t) MAX_BALL_SPEED * cosine(angle)) / 0x7FFF);
        ball_dy = (int16_t)  (((int32_t) MAX_BALL_SPEED * sine(angle)) / 0x7FFF);

        glcdFillRectangle(LEFTPADDLE_X, left_keepout_top, PADDLE_W, left_keepout_bot - left_keepout_top, 0);
        glcdFillRectangle(RIGHTPADDLE_X, right_keepout_top, PADDLE_W, right_keepout_bot - right_keepout_top, 0);

        right_keepout_top = right_keepout_bot = 0;
        left_keepout_top = left_keepout_bot = 0;
        redraw_time_rat = 1;
        minute_changed = hour_changed = 0;
        ticksremaining = calculate_dest_pos(&left_dest, &right_dest, &dest_paddle_pos, ball_dx > 0);

        //left_score = time_h;
        //right_score = time_m;
        setscore_rat();
    }



    // save old paddle position
    oldleftpaddle_y = leftpaddle_y;
    oldrightpaddle_y = rightpaddle_y;


    /* if(ball_dx > 0) {
     // For debugging, print the ball location
     DEBUG(putstring("ball @ ("));
     DEBUG(uart_putw_dec(ball_x));
     DEBUG(putstring(", "));
     DEBUG(uart_putw_dec(ball_y));
     DEBUG(putstring(")"));
     DEBUG(putstring(" ball_dx @ ("));
     DEBUG(uart_putw_dec(ball_dx));
     DEBUG(putstring(")"));
     DEBUG(putstring(" ball_dy @ ("));
     DEBUG(uart_putw_dec(ball_dy));
     DEBUG(putstring(")"));
     DEBUG(putstring(" ball_dy @ ("));
     DEBUG(uart_putw_dec(ball_dy));
     DEBUG(putstring(")"));

     }*/

    /*if(!minute_changed) {
      if((ball_dx < 0) && (ball_x < (SCREEN_W/2)*FIXED_MATH)) {
      	move_paddle(&leftpaddle_y, ball_y);
      }
    } else {
      //Minute changed.  We now have to miss the ball on purpose, if at all possible.
      //If we don't succeed this time around, we will try again next time around.
      if((ball_dx < 0) && (ball_x < (SCREEN_W/2)*FIXED_MATH) ) {
      	move_paddle(&leftpaddle_y, dest_paddle_pos);
      }
    }*/

    //ticksremaining--;
    if((ball_dx < 0) && (ball_x < (SCREEN_W/2)*FIXED_MATH) ) {
        move_paddle(&leftpaddle_y, minute_changed?dest_paddle_pos:(ball_y-(PADDLE_H_FIXED/3)));
    } else if((ball_dx > 0) && (ball_x > (SCREEN_W/2)*FIXED_MATH) ) {
        move_paddle(&rightpaddle_y, hour_changed?dest_paddle_pos:(ball_y-(PADDLE_H_FIXED/3)));
    } else {
        if(ball_dx < 0)
            ticksremaining = calculate_dest_pos(&left_dest, &right_dest, &dest_paddle_pos, 1);
        else
            ticksremaining = calculate_dest_pos(&left_dest, &right_dest, &dest_paddle_pos, 0);
    }

    // make sure the paddles dont hit the top or bottom
    if (leftpaddle_y < TOPBAR_H_FIXED +1)
        leftpaddle_y = TOPBAR_H_FIXED + 1;
    if (rightpaddle_y < TOPBAR_H_FIXED + 1)
        rightpaddle_y = TOPBAR_H_FIXED + 1;

    if (leftpaddle_y > ((SCREEN_H - PADDLE_H - BOTBAR_H)*FIXED_MATH - 1))
        leftpaddle_y =   ((SCREEN_H - PADDLE_H - BOTBAR_H)*FIXED_MATH - 1);
    if (rightpaddle_y> ((SCREEN_H - PADDLE_H - BOTBAR_H)*FIXED_MATH - 1))
        rightpaddle_y =  ((SCREEN_H - PADDLE_H - BOTBAR_H)*FIXED_MATH - 1);

    if ((ball_dx > 0) && intersectrect(INT_MSB(ball_x), INT_MSB(ball_y), BALL_RADIUS*2, BALL_RADIUS*2, RIGHTPADDLE_X, INT_MSB(rightpaddle_y), PADDLE_W, PADDLE_H)) {
        ball_dx = -ball_dx;
        ball_x = RIGHTPADDLE_X_FIXED - (BALL_RADIUS*2*FIXED_MATH);
        //ball_y = right_dest;
        //ticksremaining = calculate_dest_pos(&left_dest, &right_dest, &dest_paddle_pos, 1);
    }
    if ((ball_dx < 0) && intersectrect(INT_MSB(ball_x), INT_MSB(ball_y), BALL_RADIUS*2, BALL_RADIUS*2, LEFTPADDLE_X, INT_MSB(leftpaddle_y), PADDLE_W, PADDLE_H)) {
        ball_dx = -ball_dx;
        ball_x = LEFTPADDLE_X_FIXED + PADDLE_W_FIXED;
        //ball_y = left_dest;
        //ticksremaining = calculate_dest_pos(&left_dest, &right_dest, &dest_paddle_pos, 0);
    }

}