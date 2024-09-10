static void led_task(void *pParam) {

	BT_GpioSetDirection(BT_CONFIG_ALIVE_LED_GPIO, BT_GPIO_DIR_OUTPUT);

	BT_TICK ticks = BT_kTickCount();
	BT_TICK ticks_a = ticks;

	while(1) {
		ticks_a = BT_kTickCount();
		BT_GpioSet(BT_CONFIG_ALIVE_LED_GPIO, INVERT(BT_TRUE));
		BT_kTaskDelayUntil(&ticks_a, 10);
		BT_GpioSet(BT_CONFIG_ALIVE_LED_GPIO, INVERT(BT_FALSE));
		BT_kTaskDelayUntil(&ticks_a, 50);
		BT_GpioSet(BT_CONFIG_ALIVE_LED_GPIO, INVERT(BT_TRUE));
		BT_kTaskDelayUntil(&ticks_a, 10);
		BT_GpioSet(BT_CONFIG_ALIVE_LED_GPIO, INVERT(BT_FALSE));

		BT_kTaskDelayUntil(&ticks, BT_CONFIG_ALIVE_LED_PERIOD);
	}

	BT_kTaskDelete(NULL);
}