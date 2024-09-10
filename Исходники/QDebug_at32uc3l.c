/*! \brief Transmits the channel delta values to QTouch Studio.
 */
void Transmit_Delta(void)
{
	int16_t delta;
	UNUSED(delta);  /* Dummy. To avoid warning. */

#if ((DEF_TOUCH_QDEBUG_ENABLE_QM == 1)      ||\
	(DEF_TOUCH_QDEBUG_ENABLE_QTA == 1) ||\
	(DEF_TOUCH_QDEBUG_ENABLE_QTB == 1))

	uint8_t c;
	PutChar(QT_DELTAS);
	for (c = 0; c < QDEBUG_NUM_SENSORS; c++) {
		QDEBUG_GET_DELTA_FUNC(c, &delta);

		PutChar((uint8_t)((delta >> 8) & 0xFFu));
		PutChar((uint8_t)(delta & 0xFFu));
	}
#endif

#if DEF_TOUCH_QDEBUG_ENABLE_AT == 1
	uint16_t reference = *(QDEBUG_REFERENCES_PTR);
	uint16_t signal = *(QDEBUG_SIGNALS_PTR);
	uint16_t unsigned_delta = (uint16_t)(reference - signal);
	delta = (int16_t)unsigned_delta;

	PutChar(QT_DELTAS);
	PutChar((uint8_t)((delta >> 8) & 0xFFu));
	PutChar((uint8_t)(delta & 0xFFu));
#endif

	Send_Message();
}