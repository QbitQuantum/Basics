void loop() {
    // Though counter-intuitive, game creation cannot be in setup because of varying arduino boot times and boot gibberish
    if (!gameCreated) {
        drawGUI();
        while(!waitUntil(JOYSTICK_BUTTON_PIN, false));
        if (!startNetwork()) {
            tft.fillScreen(ST7735_BLACK); // we must clear all conflicting messages from screen
            tft.setCursor(0,0);
            dualPrint("Network connection failed!");
            dualPrint("Please ensure:");
            dualPrint("1) both arduinos are connected");
            dualPrint("2) both parties pressed the joystick");
            dualPrint("If both are true, consult someone who");
            dualPrint("looks like he knows what he's talking about");
            dualPrint("Reset both Arduinos to try again");
            while(1);
        }
        /* Extensibility Goal:
         * Enable colour selection here, time permissible
         */
        gameCreated = true;
    }
    if (!gameStarted) {
        setSpawns(&player1, &player2);
        setColour(&player1, &player2);
        tft.fillScreen(ST7735_BLACK);
        startCountdown();
        gameStarted = true;
    }
    winner = gameOver(&player1.currentPosition, &player2.currentPosition);
    if (winner) {
        tft.setCursor(0, 80);
        String message;
        switch (winner) {
        case -1:
            message = "YOU SUPER TIE";
            break;
        case 1:
            message = "YOU SUPER WIN";
            player1.score++;
            break;
        case 2:
            message = "YOU SUPER LOSE";
            player2.score++;
            break;
        }
        tft.println(message);
        tft.println("SCORES:");
        tft.print("You: ");
        tft.print(player1.score);
        tft.print(" | Him: ");
        tft.println(player2.score);
        tft.println("Again? <Press Joystick>");
        waitUntil(JOYSTICK_BUTTON_PIN, LOW);
        memset(&wallPositions, 0, 2560); // 2560 is a magic number because size_ts were acting unexpectedly
        gameStarted = false;
        tft.fillScreen(ST7735_BLACK);
    } else {
        // add a wall ad draw car at current position
        addWallPosition(player1.currentPosition);
        addWallPosition(player2.currentPosition);
        tft.fillRect(player1.currentPosition.x, player1.currentPosition.y, 2, 2, player1.colour);
        tft.fillRect(player2.currentPosition.x, player2.currentPosition.y, 2, 2, player2.colour);
        movement_t newDirection = getJoystickInput();
        if (validInput(newDirection, player1.direction)) player1.direction = newDirection;
        sendDeltas(&player1.direction);
        receiveDeltas(&player2.direction);
        player1.currentPosition.x += player1.direction.x;
        player1.currentPosition.y += player1.direction.y;
        player2.currentPosition.x += player2.direction.x;
        player2.currentPosition.y += player2.direction.y;
        delay(75); // this is how we control the game speed
        /* Extensibility Goal:
         * Find a more efficient and reliable way of controlling game speed.
         * Implement it, and allow it to be customized
         */
    }
}