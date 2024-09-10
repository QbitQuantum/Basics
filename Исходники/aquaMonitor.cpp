void menuState()
{
  menuItem tempItem;

  for (int i = 0; i < NUMBER_OF_MENU_LINES; i++) {
    tempItem = menuItems.pop();
    if (tempItem.message != NULL) {
      lcd.setCursor(0,i);
      lcd.print(i+1);
      lcd.print(tempItem.message);
    }
    menuItems.push(tempItem);
  }

  lcd.setCursor(0,3);
  if (menuItems.count() > NUMBER_OF_MENU_LINES) {
    lcd.print("Next : * Back : 0");
  }
  else{
    lcd.print("Back : #");
  }
}