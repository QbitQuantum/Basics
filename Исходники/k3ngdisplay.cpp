void K3NGdisplay::redraw(){

  // redraw the screen with the current screen_buffer_live

  for (int x = 0;x < (display_columns*display_rows);x++){   
    lcd.setCursor(Xposition(x),Yposition(x));
    if (screen_buffer_attributes_live[x] & ATTRIBUTE_BLINK){  // does this character have the blink attribute
      if (current_blink_state){
        lcd.print(screen_buffer_live[x]);
      } else {
        lcd.print(' ');
      }
    } else {
      lcd.print(screen_buffer_live[x]);
    }
  }


}	