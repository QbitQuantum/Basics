static void decodeCommand() {
  decoderBuffer[decoderCurrBufferPos] = 0;
  if (decoderCurrBufferPos == 1 && decoderBuffer[0] == 'q') {
    kernel_quit();
  }
  unsigned int shortEvalulation = (decoderCurrBufferPos <= 1);
  decoderCurrBufferPos = 0;
  if (shortEvalulation) return;

  PrintDebug(ui, "__Command: %s", decoderBuffer);
  if (decoderBuffer[0] == 'b' && decoderBuffer[1] == 'a') {
    // Bait command
    char *temp = (char *)decoderBuffer + 5;
    int train_number = strgetui(&temp);

    DoBaitPositionFinding(trainController, train_number);
    int ret = RegisterBait(snakeDirector, train_number);

  } else if (decoderBuffer[0] == 's' && decoderBuffer[2] == 'a') {
    // Snake command
    char *temp = (char*)decoderBuffer + 6;
    int train_number = strgetui(&temp);

    DoPositionFinding(trainController, train_number);
    int ret = RegisterSnake(snakeDirector, train_number);
  } else if (decoderBuffer[0] == 'i' && decoderBuffer[1] == 'n') {
    char *temp = (char *)decoderBuffer + 5;
    int train_number = strgetui(&temp);
    DoPositionFinding(trainController, train_number);
  } else if (decoderBuffer[0] == 't' && decoderBuffer[1] == 's') {
    char *temp = (char*)decoderBuffer + 3;

    char letter = *temp++;
    int num = strgetui(&temp);
    if (letter >= 'a' && letter <= 'e') {
      letter = letter - 'a' + 'A';
    }
    if (letter >= 'A' && letter <= 'E' && num >= 1 && num <= 16) {
      triggerFakeSensor(sensorServer, Time(timeServer), letter-'A', (char)num);
    } else {
      PrintDebug(ui, "Invalid Fake Sensor Value");
    }
  }  else if (decoderBuffer[0] == 'u' && decoderBuffer[1] == 's') {
    char *temp = (char *)decoderBuffer + 3;
    char track = *temp++;

    TrackMsg msg;
    msg.type = SET_TRACK;
    if (track == 'a' || track == 'b') {
      msg.data =track;
      Send(trackController, (char *)&msg, sizeof(TrackMsg), (char *)1, 0);
    }
  } else if (decoderBuffer[0] == 't' && decoderBuffer[1] == 'r') {
    char *temp = (char *)decoderBuffer + 3;
    int train_number = strgetui(&temp);
    temp++;
    int train_speed = strgetui(&temp);
    temp++;

    SetSpeedTrain(trainController, train_number, train_speed);
  } else if (decoderBuffer[0] == 'r' && decoderBuffer[1] == 'v') {
    char *temp = (char *)decoderBuffer + 3;
    int train_number = strgetui(&temp);
    ReverseTrain(trainController, train_number);
  } else if (decoderBuffer[0] == 's' && decoderBuffer[1] == 'w') {
    char *temp = (char *)decoderBuffer + 3;
    int switch_number = strgetui(&temp);
    temp++;

    char switch_pos = *temp++;
    if (switch_pos == 's' || switch_pos == 'c') {
      TrackMsg setSwitch;

      TrackLandmark sw;
      sw.type = LANDMARK_SWITCH;
      sw.num1 = 0;
      sw.num2 = (char)switch_number;

      setSwitch.type = SUDO_SET_SWITCH;
      setSwitch.landmark1 = sw;
      setSwitch.data = switch_pos == 'c' ? SWITCH_CURVED : SWITCH_STRAIGHT;
      Send(trackController, (char*)&setSwitch, sizeof(TrackMsg), (char *)NULL, 0);

      DriverMsg trainMsg;
      trainMsg.trainNum = 255;
      trainMsg.type = BROADCAST_UPDATE_PREDICTION;
      Send(trainController, (char*)&trainMsg, sizeof(trainMsg), (char *)NULL, 0);
    }
  } else if (decoderBuffer[0] == 'r' && decoderBuffer[1] == 'o') {
    char *temp = (char *)decoderBuffer + 3;

    int train_number = strgetui(&temp);
    temp++;
    int train_speed = 9;
    if (*temp >= '0' && *temp <= '9'){
      train_speed = strgetui(&temp);
      temp++;
    }

    char letter;
    int num;

    Position pos;

    letter = *temp++;
    num = strgetui(&temp);
    temp++;
    pos.landmark1 = formLandmarkFromInput(letter, num);

    letter = *temp++;
    num = strgetui(&temp);
    temp++;
    pos.landmark2 = formLandmarkFromInput(letter, num);

    pos.offset = 0;
    if (*temp >= '0' && *temp <= '9'){
      pos.offset = strgetui(&temp);
    }

    DriverMsg msg;
    msg.trainNum = train_number;
    msg.type  = SET_ROUTE;
    msg.data2 = train_speed;
    msg.pos = pos;
    PrintDebug(ui, "CD: Route %d %d %d %d %d %d %d %d %d",
        train_number, train_speed,
        pos.landmark1.type, pos.landmark1.num1, pos.landmark1.num2,
        pos.landmark2.type, pos.landmark2.num1, pos.landmark2.num2,
        pos.offset);

    if (pos.landmark1.type == LANDMARK_FAKE ||
        pos.landmark2.type == LANDMARK_FAKE) {
      PrintDebug(ui, "Parse Fail: %s", decoderBuffer);
    } else {
      Send(trainController, (char *)&msg, sizeof(DriverMsg), (char *)NULL, 0);
    }
  } else if (decoderBuffer[0] == 'r' && decoderBuffer[1] == 's') {
    char *temp = (char*)decoderBuffer + 3;

    int train_number = strgetui(&temp);
    TrackMsg msg;
    msg.type = QUERY_EDGES_RESERVED;
    msg.data = (char)train_number;
    Send(trackController, (char *)&msg, sizeof(TrackMsg), (char *)1, 0);
  } else if (decoderBuffer[0] == 'x' && decoderBuffer[1] == 'x') {
    char *temp = (char*)decoderBuffer + 3;
    int train_number = strgetui(&temp);
    Send(randomController, (char*)&train_number, 4, (char *)1, 0);
  } else if (decoderBuffer[0] == 't' && decoderBuffer[1] == 'm') {
    int train_number = 255;
    PrintDebug(ui, "Trains going in test mode");
    PrintDebug(ui, "Make sure smaller numbered train is at A4, larger numbered train at D6");
    DriverMsg msg;
    msg.type = BROADCAST_TEST_MODE;
    msg.trainNum = 255;
    msg.data2 = 8;
    Send(trainController, (char *)&msg, sizeof(DriverMsg), (char *)NULL, 0);
  } else if (decoderBuffer[0] == 'm' && decoderBuffer[1] == 'r') {
    char *temp = (char *)decoderBuffer + 3;
    int train_number1 = strgetui(&temp);
    temp++;
    int train_number2 = strgetui(&temp);
    temp++;

    // Train1 is head, train2 is new tail
    DoTrainMerge(trainController, train_number1, train_number2);
  } else if (decoderBuffer[0] == 'q' && decoderBuffer[1] == 'd') {
    char *temp = (char *)decoderBuffer + 3;

    char letter, num;
    letter = *temp++;
    Position pos;
    num = strgetui(&temp);
    temp++;
    pos.landmark1 = formLandmarkFromInput(letter, num);

    letter = *temp++;
    num = strgetui(&temp);
    temp++;
    pos.landmark2 = formLandmarkFromInput(letter, num);
    pos.offset = 1;

    letter = *temp++;
    Position pos2;
    num = strgetui(&temp);
    temp++;
    pos2.landmark1 = formLandmarkFromInput(letter, num);

    letter = *temp++;
    num = strgetui(&temp);
    temp++;
    pos2.landmark2 = formLandmarkFromInput(letter, num);
    pos2.offset = 2;

    int distance = 9999;
    QueryDistance(trackController, &pos, &pos2, &distance);
    PrintDebug(ui, "Distance: %d", distance);
  } else if (decoderBuffer[0] == 'p' && decoderBuffer[1] == 'r') {
    DoPositionFinding(trainController, 45);
    Delay(80, timeServer);
    triggerFakeSensor(sensorServer, Time(timeServer), 3, 6); // D6
    DoPositionFinding(trainController, 44);
    Delay(80, timeServer);
    triggerFakeSensor(sensorServer, Time(timeServer), 4, 5); // E5
    DoPositionFinding(trainController, 43);
    Delay(40, timeServer);
    triggerFakeSensor(sensorServer, Time(timeServer), 3, 3); // D3
    DoTrainMerge(trainController, 45, 44);
    DoTrainMerge(trainController, 45, 43);
    Delay(40, timeServer);
    SetSpeedTrain(trainController, 45, 5);
    Delay(40, timeServer);
    // Train 44 moves
    triggerFakeSensor(sensorServer, Time(timeServer), 3, 6);  // D6
    Delay(40, timeServer);
    // Train 45 moves
    triggerFakeSensor(sensorServer, Time(timeServer), 4, 10); // E10
    Delay(40, timeServer);
    PrintDebug(ui, "e13");
    // Train 45 moves
    triggerFakeSensor(sensorServer, Time(timeServer), 4, 13); // E13
    Delay(40, timeServer);
    PrintDebug(ui, "last d6 ");
    // Train 43 moves
    triggerFakeSensor(sensorServer, Time(timeServer), 3, 6);  // D6
    Delay(40, timeServer);
  } else if (decoderBuffer[0] == 'f' && decoderBuffer[1] == 'o') {
    // sets the max/min distance between train during merge mode
    char *temp = (char *)decoderBuffer + 3;
    int train_number = strgetui(&temp);
    temp++;
    int min_dist = strgetui(&temp);
    temp++;
    int max_dist = strgetui(&temp);
    temp++;

    if (max_dist > min_dist) {
      SetFollowingDistance(trainController, train_number, min_dist, max_dist);
    } else {
      PrintDebug(ui, "ERROR, maxDist less than minDist");
    }
  } else if (decoderBuffer[0] == 'b' && decoderBuffer[1] == 'i' && decoderBuffer[2] == 'g') {
      TrackMsg setSwitch;
      setSwitch.type = SUDO_SET_SWITCH;
      setSwitch.landmark1.type = LANDMARK_SWITCH;
      setSwitch.landmark1.num1 = 0;

      setSwitch.data = SWITCH_CURVED;
      setSwitch.landmark1.num2 = 8;
      Send(trackController, (char*)&setSwitch, sizeof(TrackMsg), (char *)NULL, 0);
      Delay(1, timeServer);
      setSwitch.landmark1.num2 = 9;
      Send(trackController, (char*)&setSwitch, sizeof(TrackMsg), (char *)NULL, 0);
      Delay(1, timeServer);
      setSwitch.landmark1.num2 = 14;
      Send(trackController, (char*)&setSwitch, sizeof(TrackMsg), (char *)NULL, 0);
      Delay(1, timeServer);
      setSwitch.landmark1.num2 = 15;
      Send(trackController, (char*)&setSwitch, sizeof(TrackMsg), (char *)NULL, 0);

      setSwitch.data = SWITCH_STRAIGHT;
      Delay(1, timeServer);
      setSwitch.landmark1.num2 = 10;
      Send(trackController, (char*)&setSwitch, sizeof(TrackMsg), (char *)NULL, 0);
      Delay(1, timeServer);
      setSwitch.landmark1.num2 = 13;
      Send(trackController, (char*)&setSwitch, sizeof(TrackMsg), (char *)NULL, 0);
      Delay(1, timeServer);
      setSwitch.landmark1.num2 = 16;
      Send(trackController, (char*)&setSwitch, sizeof(TrackMsg), (char *)NULL, 0);
      Delay(1, timeServer);
      setSwitch.landmark1.num2 = 17;
      Send(trackController, (char*)&setSwitch, sizeof(TrackMsg), (char *)NULL, 0);

      DriverMsg trainMsg;
      trainMsg.trainNum = 255;
      trainMsg.type = BROADCAST_UPDATE_PREDICTION;
      Send(trainController, (char*)&trainMsg, sizeof(trainMsg), (char *)NULL, 0);


  } else {
    PrintDebug(ui, "__Bad command__ %s", decoderBuffer);
    return;
  }
}