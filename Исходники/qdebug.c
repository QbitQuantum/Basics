/**
 * @brief Transmits the channel reference values to QTouch Studio
 */
void Transmit_Ref(void)
{
   uint8_t c;
   PutChar(QT_REFERENCES);
   for(c=0; c<QT_NUM_CHANNELS; c++)
   {
      PutChar(qt_measure_data.channel_references[c] >> 8);
      PutChar(qt_measure_data.channel_references[c] & 0xFF);
   }
   Send_Message();
}