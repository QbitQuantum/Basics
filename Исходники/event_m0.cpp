void EventDispatcher::handle_lcd_frame_sync() {
	DisplayFrameSyncMessage message;
	message_map.send(&message);
	painter.paint_widget_tree(top_widget);
}