void PrintSchdFile(Record* const rd, int index) {
  FILE *fp;
  if (index == 1) {
    fp = fopen("FCFS_Schd.dat", "a");
  }
  else if (index == 2) {
    fp = fopen("PRIO_Schd.dat", "a");
  }
  else {
    fp = fopen("OPTI_Schd.dat", "a");
  }
  Record* cur = rd;
  int rejected_a = 0;
  int rejected_b = 0;
  int rejected_d = 0;
  int total = 0;
  int i;
  char message_from_child[2];

  //Accepted Part
  fprintf(fp, " ____________________________________________________________________________ \n");
  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|***Room Booking - ACCEPTED***                                               |\n");
  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|Room_A has the following bookings:                                          |\n");
  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|Date         Start   End     Type          Requester  Device                |\n");
  fprintf(fp, "|============================================================================|\n");

  while (cur->next != NULL) {
    cur = cur->next;
    total++;
    if (cur->room_A == 1 && cur->accept == 1)
      PrintAccept(cur, fp);
    else if (cur->room_A == 1)
      rejected_a++;
  }

  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|Room_B has the following bookings:                                          |\n");
  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|Date         Start   End     Type          Requester  Device                |\n");
  fprintf(fp, "|============================================================================|\n");

  cur = rd;
  while (cur->next != NULL) {
    cur = cur->next;
    if (cur->room_B == 1 && cur->accept == 1)
      PrintAccept(cur, fp);
    else if (cur->room_B == 1)
      rejected_b++;
  }

  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|   -End-                                                                    |\n");
  fprintf(fp, "|============================================================================|\n");
  fprintf(fp, "|____________________________________________________________________________|\n");

  //Rejected Part
  fprintf(fp, " ____________________________________________________________________________ \n");
  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|***Room Booking - REJECTED***                                               |\n");
  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|Room_A, there are %d bookings rejected.                                      ", rejected_a);
  Format(fp, rejected_a);
  fprintf(fp, "|\n");
  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|Date         Start   End     Type          Device                           |\n");
  fprintf(fp, "|============================================================================|\n");

  cur = rd;
  while (cur->next != NULL) {
    cur = cur->next;
    if (cur->room_A == 1 && cur->accept == 0) PrintReject(cur, fp);
  }

  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|Room_B, there are %d bookings rejected.                                      ", rejected_b);
  Format(fp, rejected_b);
  fprintf(fp, "|\n");
  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|Date         Start   End     Type          Device                           |\n");
  fprintf(fp, "|============================================================================|\n");

  cur = rd;
  while (cur->next != NULL) {
    cur = cur->next;
    if (cur->room_B == 1 && cur->accept == 0)
      PrintReject(cur, fp);
  }

  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|   -End-                                                                    |\n");
  fprintf(fp, "|============================================================================|\n");
  fprintf(fp, "|____________________________________________________________________________|\n");

  cur = rd;
  while (cur->next != NULL) {
    cur = cur->next;
    if (cur->type == 0 && cur->accept == 0)
      rejected_d++;
  }

  //Performance part
  fprintf(fp, " ____________________________________________________________________________ \n");
  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|Performance:                                                                |\n");
  fprintf(fp, "|                                                                            |\n");
  fprintf(fp, "|Total Number of Bookings Received: %d (100.0%%)                               ", total);
  Format(fp, total);
  fprintf(fp, "|\n");
  fprintf(fp, "|      Number of Bookings Assigned: %d (%.1f%%)                                 ", total - rejected_a - rejected_b - rejected_d, total == 0 ? 0.0 : (double) (total - rejected_a - rejected_b - rejected_d) * 100.0 / (double) total);
  Format(fp, total - rejected_a - rejected_b - rejected_d);
  Format(fp, total == 0 ? 0.0 : (double) (total - rejected_a - rejected_b - rejected_d) * 100.0 / (double) total);
  fprintf(fp, "|\n");
  fprintf(fp, "|      Number of Bookings Rejected: %d (%.1f%%)                                 ", rejected_a + rejected_b + rejected_d, total == 0 ? 0.0 : (double) (rejected_a + rejected_b + rejected_d) * 100.0 / (double) (total));
  Format(fp, rejected_a + rejected_b + rejected_d);
  Format(fp, total == 0 ? 0.0 : (double) (rejected_a + rejected_b + rejected_d) * 100.0 / (double) (total));
  fprintf(fp, "|\n");
  fprintf(fp, "|Utilization of Time Slot:                                                   |\n");
  fprintf(fp, "|                                                                            |\n");

  for (i = 0; i < 10; i++) {
    time_slot_record[i] = Send(i, "00T");
  }

  fprintf(fp, "|      Room_A                  - %.1f%%                                        ", (double) time_slot_record[0] * 100.0 / 126.0);
  Format(fp,time_slot_record[0] * 100 / 126);
  fprintf(fp, "|\n");

  fprintf(fp, "|      Room_B                  - %.1f%%                                        ", (double) time_slot_record[1] * 100.0 / 126.0);
  Format(fp, time_slot_record[1] * 100 / 126);
  fprintf(fp, "|\n");

  fprintf(fp, "|      webcam_720p             - %.1f%%                                        ", (double) time_slot_record[2] * 100.0 / 126.0);
  Format(fp, time_slot_record[2] * 100 / 126);
  fprintf(fp, "|\n");

  fprintf(fp, "|      webcam_1080p            - %.1f%%                                        ", (double) time_slot_record[3] * 100.0 / 126.0);
  Format(fp, time_slot_record[3] * 100 / 126);
  fprintf(fp, "|\n");

  fprintf(fp, "|      monitor_50              - %.1f%%                                        ", (double) time_slot_record[4] * 100.0 / 126.0);
  Format(fp, time_slot_record[4] * 100 / 126);
  fprintf(fp, "|\n");

  fprintf(fp, "|      monitor_75              - %.1f%%                                        ", (double) time_slot_record[5] * 100.0 / 126.0);
  Format(fp, time_slot_record[5] * 100 / 126);
  fprintf(fp, "|\n");

  fprintf(fp, "|      projector_fhd           - %.1f%%                                        ", (double) time_slot_record[6] * 100.0 / 126.0);
  Format(fp, time_slot_record[6] * 100 / 126);
  fprintf(fp, "|\n");

  fprintf(fp, "|      projector_xga           - %.1f%%                                        ", (double) time_slot_record[7] * 100.0 / 126.0);
  Format(fp, time_slot_record[7] * 100 / 126);
  fprintf(fp, "|\n");

  fprintf(fp, "|      screen_100              - %.1f%%                                        ", (double) time_slot_record[8] * 100.0 / 126.0);
  Format(fp, time_slot_record[8] * 100 / 126);
  fprintf(fp, "|\n");

  fprintf(fp, "|      screen_150              - %.1f%%                                        ", (double) time_slot_record[9] * 100.0 / 126.0);
  Format(fp, time_slot_record[9] * 100 / 126);
  fprintf(fp, "|\n");

  fprintf(fp, "|____________________________________________________________________________|\n");
}