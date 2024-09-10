  //コンソール用のタスク
void task_console(Sheet* sheet)
{
	Timer* timer;
	Task* task;
	char s[2];

	int i,cursor_x = 16,cursor_y=28,cursor_c = COLOR_LGREEN;//カーソルの初期設定

	task = TaskControll::task_now();
	timer = TimerControl::alloc(); 
	timer->init(task->fifo,1);           //timerにfifoを関連付けて,時間が来たら1をセット
	timer->settime(50);                 //50msecでタイマー発生

	for(;;){
	  io_cli();
	  if(task->fifo->status() == 0){   //何の動作もないときはスリープ
			task->sleep();
			io_sti();
	  }
	  else{
			i = task->fifo->get();
			io_sti();
			//-----タイマー-----
			if(i<=1){
				if(i!=0){
					timer->init(task->fifo,0);
					cursor_c = COLOR_DGREEN;
				}
				else{
					timer->init(task->fifo,1);
					cursor_c = COLOR_LGREEN;
				}
				timer->settime(50);
				sheet->g->boxfill8(cursor_c,cursor_x,cursor_y,cursor_x+7,cursor_y+15);
				sheet->refresh(cursor_x,28,cursor_x+8,cursor_y+16);
			}
			//-----キーボード-----
			if(256<=i && i<= 511){
				if(i - 256==8){ //backspace
					if(cursor_x>16){
						sheet->g->putfonts8_asc_sht(cursor_x,cursor_y,COLOR_DGREEN,COLOR_WHITE,(unsigned char*)" ",1);
						cursor_x-=8;
					}
					else if(cursor_y>28){
						sheet->g->putfonts8_asc_sht(cursor_x,cursor_y,COLOR_DGREEN,COLOR_WHITE,(unsigned char*)" ",1);
						cursor_y-=28;
						while(cursor_x < sheet->bxsize-20){
							cursor_x+=8;
						}
					}
				}
				else if(i-256==0x0A){ //new line
					sheet->g->putfonts8_asc_sht(cursor_x,cursor_y,COLOR_DGREEN,COLOR_WHITE,(unsigned char*)" ",1);
					cursor_y+=28;
					cursor_x = 16;
				}
				else{           //一般文字
					if(cursor_x  <  sheet->bxsize-20){
						s[0] = i-256;
						s[1] = (char)0;
						sheet->g->putfonts8_asc_sht(cursor_x,cursor_y,COLOR_LGREEN,COLOR_WHITE,(unsigned char*)s,1);
						cursor_x+=8;
					}
				}
			}
	  

	  }
	}
}