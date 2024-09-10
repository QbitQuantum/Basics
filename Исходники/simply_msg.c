static void handle_element_text_packet(Simply *simply, Packet *data) {
  ElementTextPacket *packet = (ElementTextPacket*) data;
  SimplyElementText *element = (SimplyElementText*) simply_stage_get_element(simply->stage, packet->id);
  if (!element) {
    return;
  }
  if (element->time_units != packet->time_units) {
    element->time_units = packet->time_units;
    simply_stage_update_ticker(simply->stage);
  }
  strset(&element->text, packet->text);
  simply_stage_update(simply->stage);
}