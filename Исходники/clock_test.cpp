void loop() {
    // update the time
    clk->updateTime(millis());

    if (clk->toggleChange()) {
        // displayMenu(nav->getCursor()->id, lcd, clk, tasks);

        // if the cursor id is below 5, it means we are currently
        // viewing the clock menu and if and update has been made on the clock
        // we have to update the clock
        lcd.setCursor(4, 3); lcd.write(clk->getTime() != 0 ? (clk->getTime() / (1000 > 0 ? 1000 : 1000 * -1) % 10 + '0') : 0);
        lcd.setCursor(5, 3); lcd.write(clk->getTime() != 0 ? (clk->getTime() / ( 100 > 0 ?  100 :  100 * -1) % 10 + '0') : 0);
        // empty space filled with ':'
        lcd.setCursor(7, 3); lcd.write(clk->getTime() != 0 ? (clk->getTime() / (  10 > 0 ?   10 :   10 * -1) % 10 + '0') : 0);
        lcd.setCursor(8, 3); lcd.write(clk->getTime() != 0 ? (clk->getTime() / (   1 > 0 ?    1 :    1 * -1) % 10 + '0') : 0);
    }
}