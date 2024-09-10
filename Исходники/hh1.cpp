int MHookHandler1::OnMouseMove(LONG _x, LONG _y)
{
	int position;
	bool goup=false; // Сразу отпусти клавишу
		
	// При нажатой правой кнопке мыши не передаём её движения в MHVector,
	// НО! продолжаем отслеживать last_x и last_y, не сбрасывая initialized! 
	// теперь по-новому: если есть прилипание к оси, то можно только противоположное
	// или то же. Поворачивать нельзя.
	if(initialized)
	{
		dx=(_x-last_x);
		dy=(_y-last_y);

		// Может, пятую кнопку можно нажать?
		if(MHSettings::flag_enable_speed_button) OnFastMove(dx,dy);

		position=MHVector::NewValues(dx,dy);

		// Если вбок и вниз = просто вбок, меняем позиции 3 и 5 на 4
		if((true==MHSettings::flag_downall)&&(8==MHSettings::GetNumPositions())&&((3==position)||(5==position)))
		{
			if(MHSettings::flag_up_immediately) goup=true; 
			position=4;
		}

		if(!rbutton_pressed) // известно последнее положение мыши, правая кнопка не нажата
		{
			// Новая опция - из конца в конец в два движения (только при 0==alt_offset)
			if((MHSettings::flag_2moves_mode1)&&(0==alt2_offset))
			{
				if(0<=position) // новое направление
				{
					// Это противоположное направление?
					if(IsOpposite(position_mem_opposite,position))
					{
						// 1. (при невыставленном флаге противоположного направления)
						// сбросим нажатую клавишу. Нажать противоположную сможем только после таймаута
						if(false==flag_opposite_direction)
						{
							// запомним время, отпустим кнопки, запомним направление (ниже)
							opposite_time=timeGetTime();
							MHKeypad::Reset(alt2_offset);
#ifdef _DEBUG
		OutputDebugString(L"OppDir keyup");
#endif
							flag_opposite_direction=true;
							position_mem_opposite=position;
							 
							// Почему-то Reset не включает перерисовку
							InvalidateRect(MHhwnd,NULL,TRUE);
						}
						else // при выставленном флаге противоположного направления
						{
							// 2. Как такое случилось?
							// Не дожидаясь времени, когда можно идти назад, снова пошли вперёд
							MHKeypad::Press(position,true,alt2_offset);
							flag_opposite_direction=false;
							position_mem_opposite=position;
							if(goup) MHKeypad::Press(position,false, alt2_offset); // Флаг сказал, что нужно тут же отжать
						}
					}
					else // не противоположное (position_mem содержит всё что угодно),
					{
						if(true==flag_opposite_direction) 
						{
							// 3.
							// ждём выхода в сторону position_mem, а по дороге завернули в сторону
							// только здесь возможен поворот в сторону !!!
							// Но только если прошло время обездвиженности!!!
							if(timeGetTime()-opposite_time>100) // была пауза, можно идти в противоположном направлении
							{
								MHKeypad::Press(position,true, alt2_offset);
								flag_opposite_direction=false;
								position_mem_opposite=position;
								if(goup) MHKeypad::Press(position,false, alt2_offset); // Флаг сказал, что нужно тут же отжать
							}
							else 
							{
								MHVector::Reset(); // Не надо больше слать -1
								opposite_time=timeGetTime(); // паузы в 50 мс неподвижности не было, перевзводим
							}
							//MHKeypad::Press(position,true);
							//flag_opposite_direction=false; // уход в сторону - сброс ожиданий
						}
						else // flag_opposite_direction=false
						{
							// не ждём выхода в сторону position_mem. 
							// Нажимаем, только если -1==position_mem (при прилипании)
							if((-1==position_mem)||(MHSettings::flag_change_direction_ontheway))
							{
								MHKeypad::Press(position,true, alt2_offset);
								position_mem_opposite=position;
								if(goup) MHKeypad::Press(position,false, alt2_offset); // Флаг сказал, что нужно тут же отжать
							}
						}
					
					} // не противоположное направление
				}
				else if(-1==position)
				{
					// 4.
					// Обрабатываем, только если не довели до конца
					if(flag_opposite_direction)
					{
						if(timeGetTime()-opposite_time>100) // была пауза, можно идти в противоположном направлении
						{
							MHKeypad::Press(position_mem_opposite,true, alt2_offset);
							flag_opposite_direction=false;
							if(goup) MHKeypad::Press(position_mem_opposite,false, alt2_offset); // Флаг сказал, что нужно тут же отжать
						}
						else opposite_time=timeGetTime(); // паузы в 50 мс неподвижности не было, перевзводим
					}
				}
				// else осталось только -2, игнорируем
			} //flag_2moves_mode1 и 4 позиции
			else 
			{
				// 5.
				if(0==alt2_offset)
				{
					// Почти по-старому, как было до модификации flag_2moves_mode1
					if(0<=position) // -2=мышь ваще не двигалась, -1= направление не изменилось
					{
						MHKeypad::Press(position,true,alt2_offset);
						if(goup) MHKeypad::Press(position,false, alt2_offset); // Флаг сказал, что нужно тут же отжать
					}
				}
				else // Если это альтернативная раскладка, то взвести таймер
				{
					// 6.
					// как раньше при обработке правой кнопки мыши
					if(0<=position) // -2=мышь подвинулась на недостаточное растояние, -1= направление не изменилось
					{
						MHKeypad::Press(position,true, alt2_offset); // По движению правой кнопки нажимать альтернативные клавиши из первой раскладки
						position_mem=position;
						if(goup) MHKeypad::Press(position,false, alt2_offset); // Флаг сказал, что нужно тут же отжать
						
					}
					// Таймер взводим заново при любом движении мыши, если было хоть что-то нажато ранее
					// то есть -1!=position_mem
					if(-1!=position_mem)
					{
						last_time=timeGetTime();
						SetTimer(MHhwnd,1,MHSettings::timeout_after_move,NULL);

					}
				}
			}
		} // правая кнопка не нажата
		else // нажата правая кнопка. Внимание!!!! Здесь может быть 8 позиций, тогда движение с правой кнопкой игнорируем !!!!
		{
			// Изменение 18.04 - позволяем альтернативным кодировкам  работать и в 8 позициях
			//if(4==MHSettings::GetNumPositions())
			//{
				if(!MHSettings::flag_alt2) // Так было, пока не ввели вторую альтернативную: движения с нажатой правой вызывали нажатия c таймером
				{
					// обработка правой кнопки мыши
					if(0<=position) // -2=мышь подвинулась на недостаточное растояние, -1= направление не изменилось
					{
						//MHKeypad::Press(position,true, 6); // По движению правой кнопки нажимать альтернативные клавиши из первой раскладки
						MHKeypad::Press(position,true, alt2_offset);
						position_mem=position;
					}
					// Таймер взводим заново при любом движении мыши, если было хоть что-то нажато ранее
					// то есть -1!=position_mem
					if(-1!=position_mem)
					{
						last_time=timeGetTime();
						SetTimer(MHhwnd,1,MHSettings::timeout_after_move,NULL);
					}
				}
				else // flag_alt2 - теперь движения с нажатой правой - это выбор раскладки
				{
					// Изменение 18.04 - позволяем альтернативным кодировкам  работать и в 8 позициях
					if(4==MHSettings::GetNumPositions())
					{
						switch(position)
						{
						
						case 1: // стрелка впрваво - первая альтернативная
							// Первым делом - отпустить нажатые клавиши
							MHKeypad::Reset(alt2_offset);
							position_mem=-1;
							switch(alt2_offset)
							{
							case 6: // Включена уже, выключить
								alt2_offset=0;
								break;

							case 0: // основная, поменять
							case 11: // Включена вторая, поменять
								alt2_offset=6;
								break;
							}
							break;

							case 3: // стрелка влево - выбор второй альтернативной
							// Первым делом - отпустить нажатые клавиши
							MHKeypad::Reset(alt2_offset);
							position_mem=-1;
							switch(alt2_offset)
							{
							case 11: // Включена уже, выключить
								alt2_offset=0;
								break;

							case 0: // основная, поменять
							case 6: // Включена вторая, поменять
								alt2_offset=11;
								break;
							}
							break;
							// Остальные направления (стрелки вверх и вниз) игнорируем
						}	// switch
					} // 4 позиции
					else // (8 позиций) Изменение 18.04 - позволяем альтернативным кодировкам  работать и в 8 позициях
					{
						if((position>0)&&(position<4)) // правая полусфера.
						{
							MHKeypad::Reset(alt2_offset);
							position_mem=-1;
							switch(alt2_offset)
							{
							case 6: // Включена уже, выключить
								alt2_offset=0;
								break;

							case 0: // основная, поменять
							case 11: // Включена вторая, поменять
								alt2_offset=6;
								break;
							}
						}
						else if((position>4)) // левая полусфера
						{
							// Первым делом - отпустить нажатые клавиши
							MHKeypad::Reset(alt2_offset);
							position_mem=-1;
							switch(alt2_offset)
							{
							case 11: // Включена уже, выключить
								alt2_offset=0;
								break;

							case 0: // основная, поменять
							case 6: // Включена вторая, поменять
								alt2_offset=11;
								break;
							}
						}
						// Остальные направления (стрелки вверх и вниз) игнорируем
						
					} // 8 позиций
				} // выставлен флаг alt2, меняем раскладки
			// Изменение 18.04 - позволяем альтернативным кодировкам  работать и в 8 позициях
			//} // 4 позиции, а в 8 позициях с правой кнопкой ничего не делаем вообще
			
		} // правая кнопка нажата
	} // if initialized
		

	if(!initialized) initialized=true;

	last_x=_x;
	last_y=_y;
	if(last_x<0) last_x=0;
	if(last_y<0) last_y=0;
	if(last_x>=screen_x_real) last_x=screen_x_real-1;
	if(last_y>=screen_y_real) last_y=screen_y_real-1;

#ifdef _DEBUG
	// Покажите абсолютные значения мвшиных сообщений
	//sprintf(debug_buf,"dx: %d  dy: %d\n", dx,dy);
	//OutputDebugString(debug_buf);
#endif

	return 0; // Новая директива ВЦСПС
}