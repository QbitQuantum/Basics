void PDBLK::plot(                //draw outline
                 ScrollView* window,  //window to draw in
                 int32_t serial,   //serial number
                 ScrollView::Color colour   //colour to draw in
                ) {
  ICOORD startpt;                //start of outline
  ICOORD endpt;                  //end of outline
  ICOORD prevpt;                 //previous point
  ICOORDELT_IT it = &leftside;   //iterator

                                 //set the colour
  window->Pen(colour);
  window->TextAttributes("Times", BLOCK_LABEL_HEIGHT, false, false, false);

  if (hand_poly != nullptr) {
    hand_poly->plot(window, serial);
  } else if (!leftside.empty ()) {
    startpt = *(it.data ());     //bottom left corner
    //              tprintf("Block %d bottom left is (%d,%d)\n",
    //                      serial,startpt.x(),startpt.y());
    char temp_buff[34];
#if !defined(_WIN32) || defined(__MINGW32__)
    snprintf(temp_buff, sizeof(temp_buff), "%" PRId32, serial);
#else
    _ultoa(serial, temp_buff, 10);
#endif
    window->Text(startpt.x (), startpt.y (), temp_buff);

    window->SetCursor(startpt.x (), startpt.y ());
    do {
      prevpt = *(it.data ());    //previous point
      it.forward ();             //move to next point
                                 //draw round corner
    window->DrawTo(prevpt.x (), it.data ()->y ());
    window->DrawTo(it.data ()->x (), it.data ()->y ());
    }
    while (!it.at_last ());      //until end of list
    endpt = *(it.data ());       //end point

                                 //other side of boundary
    window->SetCursor(startpt.x (), startpt.y ());
    it.set_to_list (&rightside);
    prevpt = startpt;
    for (it.mark_cycle_pt (); !it.cycled_list (); it.forward ()) {
                                 //draw round corner
    window->DrawTo(prevpt.x (), it.data ()->y ());
    window->DrawTo(it.data ()->x (), it.data ()->y ());
      prevpt = *(it.data ());    //previous point
    }
                                 //close boundary
    window->DrawTo(endpt.x(), endpt.y());
  }
}