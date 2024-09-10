static void Exec_Update_ProgressBar(LCUI_Widget *widget)
/* 功能：更新进度条的图形 */
{ 
	LCUI_ProgressBar *pb = (LCUI_ProgressBar*)Get_Widget_PrivData(widget);
	if(Strcmp(&widget->style, "dynamic") == 0) {
		/* 绘制空槽 */
		Draw_Empty_Slot(&widget->graph, widget->size.w, widget->size.h);
		Set_Widget_Border_Style(widget, BORDER_STYLE_NONE);
		/* 载入两个图形 */
		if(!Graph_Valid(&pb->fore_graph)) 
			Load_Graph_ProgressBar_Fore(&pb->fore_graph);  
			
		if(!Graph_Valid(&pb->flash_image)) 
			Load_Graph_ProgressBar_Img(&pb->flash_image);
		
		Resize_Widget(pb->img_pic_box, Get_Graph_Size(&pb->flash_image)); 
		/* 让图片盒子显示这个图形 */
		Set_PictureBox_Image_From_Graph(pb->img_pic_box, &pb->flash_image);
	} else {
		Strcpy(&widget->style, "classic");
		if(!Graph_Valid(&pb->fore_graph)) 
			Graph_Create(&pb->fore_graph, 10, widget->size.h); 
		Graph_Fill_Color(&pb->fore_graph, RGB(80,80,200));
		Graph_Fill_Alpha(&pb->fore_graph, 255);
	}
	
	/* 让图片盒子显示这个图形 */
	Set_PictureBox_Image_From_Graph(pb->fore_pic_box, &pb->fore_graph); 
	
	int width, height;
	/* 计算进度条的长度 */ 
	width = (widget->size.w - widget->border.left - widget->border.right) 
			* pb->value / pb->max_value + 0.5;
	height = widget->size.h - widget->border.top - widget->border.bottom;
	
	Move_Widget(pb->fore_pic_box, Pos(widget->border.left, widget->border.top));
	/* 改变进度条的尺寸 */
	Resize_Widget(pb->fore_pic_box, Size(width, height));
}