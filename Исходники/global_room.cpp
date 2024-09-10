void NewRoom(int nrnum) {
    if (nrnum < 0)
        quitprintf("!NewRoom: room change requested to invalid room number %d.", nrnum);

    if (displayed_room < 0) {
        // called from game_start; change the room where the game will start
        playerchar->room = nrnum;
        return;
    }


    DEBUG_CONSOLE("Room change requested to room %d", nrnum);
    EndSkippingUntilCharStops();

    can_run_delayed_command();

    if (play.stop_dialog_at_end != DIALOG_NONE) {
        if (play.stop_dialog_at_end == DIALOG_RUNNING)
            play.stop_dialog_at_end = DIALOG_NEWROOM + nrnum;
        else {
            quitprintf("!NewRoom: two NewRoom/RunDialog/StopDialog requests within dialog; last was called in \"%s\", line %d",
                last_in_dialog_request_script_pos.Section.GetCStr(), last_in_dialog_request_script_pos.Line);
        }
        return;
    }

    get_script_position(last_in_dialog_request_script_pos);

    if (in_leaves_screen >= 0) {
        // NewRoom called from the Player Leaves Screen event -- just
        // change which room it will go to
        in_leaves_screen = nrnum;
    }
    else if (in_enters_screen) {
        setevent(EV_NEWROOM,nrnum);
        return;
    }
    else if (in_inv_screen) {
        inv_screen_newroom = nrnum;
        return;
    }
    else if ((inside_script==0) & (in_graph_script==0)) {
        new_room(nrnum,playerchar);
        return;
    }
    else if (inside_script) {
        curscript->queue_action(ePSANewRoom, nrnum, "NewRoom");
        // we might be within a MoveCharacterBlocking -- the room
        // change should abort it
        if ((playerchar->walking > 0) && (playerchar->walking < TURNING_AROUND)) {
            // nasty hack - make sure it doesn't move the character
            // to a walkable area
            mls[playerchar->walking].direct = 1;
            StopMoving(game.playercharacter);
        }
    }
    else if (in_graph_script)
        gs_to_newroom = nrnum;
}