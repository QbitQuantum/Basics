void GLTouchScreen::analyze(float x, float y) {
	//x = roundf(x * width / context->width);
	//y = roundf(y * height / context->height);
	
	if (clientRatio > viewRatio) { // Экран уже чем треубется
		x = roundf(x * clientWidth / viewWidth);
		y = roundf((((y / viewHeight) - 0.5f) * clientRatio / viewRatio + 0.5f) * clientHeight);
	} else {
		x = roundf((((x / viewWidth) - 0.5f) * viewRatio / clientRatio + 0.5f) * clientWidth);
		y = roundf(y * clientHeight / viewHeight);
	}

	recordTrack(x, y, true);
	
	if (touchTimeout != 0) {
		touchTimeout = 0;
	}
	if (touchCancel) {
		touchCancel = false;
		return;
	}
	
	int32_t listlength = touchList.count();
	Vec3* list = touchList.items();
	if (listlength > 0) {
		CString type;
		
		GLfloat x1 = list[0].x;
		GLfloat y1 = list[0].y;
		GLfloat x2 = list[listlength - 1].x;
		GLfloat y2 = list[listlength - 1].y;
		
		if (listlength == 1) {
			int32_t count = clickList.count();
			if (count > 0) {
				GLTouchObject** items = clickList.items();
				for (int i = count - 1; i >= 0; i--) {
					GLfloat ww = items[i]->w;
					GLfloat hh = items[i]->h;
					GLfloat xx = items[i]->x;
					GLfloat yy = items[i]->y;
					if ((x1 >= xx) && (x1 < (xx + ww)) &&
						(y1 >= yy) && (y1 < (yy + hh))
					) {
						type = L"click ";
						type += items[i]->name;
						if (items[i]->onevent(type, NULL, NULL, NULL, items[i]->userData)) {
							break;
						}
					}
				}
			}
			if (type.m_length == 0)
				type = L"none";
		} else {
			// Определение кругового движения по часовой стрелке или против
			GLfloat cx, cy;
			{
				// Вычисляем центр окружности описывающей точки
				GLfloat xmin, xmax, ymin, ymax;
				xmin = xmax = x1;
				ymin = ymax = y1;
				for (int i = 0; i < listlength; i++) {
					GLfloat xx = list[i].x;
					GLfloat yy = list[i].y;
					if (xx < xmin) xmin = xx;
					if (xx > xmax) xmax = xx;
					if (yy < ymin) ymin = yy;
					if (yy > ymax) ymax = yy;
				}
				cx = (xmin + xmax) / 2.0f;
				cy = (ymin + ymax) / 2.0f;
				
				// Вычисляем средний радиус и определяем число смещений по кругу
				GLfloat mr = 0; // Средний радиус
				GLfloat cw = 0; // Число смещений по часовой стрелке
				GLfloat bw = 0; // Число смещений против часовой стрелки
				GLfloat ca = 0; // Угол смещения по часовой стрелке
				GLfloat ba = 0;	// Угол смещения против часовой стрелки
				GLfloat lx = x2 - cx;
				GLfloat ly = y2 - cy;
				GLfloat la = atan2f(ly, lx); // Угол последней точки
				for (int i = 0; i < listlength; i++) {
					// Координаты относительно центра
					GLfloat xx = list[i].x - cx;
					GLfloat yy = list[i].y - cy;
					// Растояние до точки
					GLfloat r = floorf(sqrtf(xx * xx + yy * yy));
					// Направление движения по часовой стрелке или против
					GLfloat s = lx * yy - ly * xx;
					GLfloat na = atan2f(yy, xx);
					GLfloat a = (na - la) * 180.0f / (GLfloat)M_PI;
					while (a < -180.0f) a += 360.0f;
					while (a > 180.0f) a -= 360.0f;
					if (i != 0) {
						if (s > 0) { cw++; ca += a; }
						else if (s < 0) { bw++; ba -= a; }
					}
					// Кешируем вычисления
					list[i].z = r;
					mr += r;
					la = na;
					lx = xx;
					ly = yy;
				}
				mr = floorf(mr / (GLfloat)listlength);
				
				// Вычисляем процентное соотношение смещений и направление
				GLfloat md = 0;
				if ((cw != 0) || (bw != 0)) {
					if (cw > bw) {
						md = floorf((cw - bw) * 100.0f / cw);
					} else {
						md = -floorf((bw - cw) * 100.0f / bw);
					}
				}
				// Угол смещения
				GLfloat a = fabsf(ba - ca);
				
				// Проверяем ровность круга (допустимое искажение радиуса 50% на каждую точку)
				if ((mr > minimalDistance) && (fabsf(md) > 90.0f)) {
					bool circle = true;
					GLfloat drm = 0;
					for (int i = 0; i < listlength; i++) {
						GLfloat dr = floorf(fabsf((list[i].z / mr) - 1.0f) * 100.0f);
						if (dr > drm) drm = dr;
						if (dr > 50.0f) {
							circle = false;
							break;
						}
					}
					if (circle) {
						int ac = (int)roundf(a / 90.0f);
						if (ac > 2) {
							type = L"circle";
						} else {
							type = L"arc";
						}
						if (md > 0) type += L" right";
						else type += L" left";
						if (ac > 5) {
							type += L" ";
							type += (ac * 90);
						}
					}
				}
			}
			
			// Определение свайпов и их направления
			if (type.m_length == 0) {
				// Вычисляем расстояние
				GLfloat dx = x2 - x1;
				GLfloat dy = y2 - y1;
				GLfloat d = floorf(sqrtf(dx * dx + dy * dy));
				
				// Отбрасываем случайные или короткие свайпы
				uint64_t time = currentTimeMillis();
				time -= touchStart;
				if ((d > minimalDistance) && ((listlength < 15) || (d >= swipeDistance))) {
					
					// Проверяем ровность линии (допустимое искажение 25% от длины прямой)
					bool swipe = true;
					GLfloat c = x1 * y2 - x2 * y1;
					for (int i = listlength - 2; i > 0; i--) {
						// Расстояние до точки от отрезка (+ знак стороны)
						GLfloat p = (list[i].y * dx - list[i].x * dy + c) / d;
						GLfloat dp = floorf(fabsf(p) * 100.0f / d);
						if (dp > 25) {
							swipe = false;
							break;
						}
					}
					
					if (swipe) {
						type = L"swipe";
						
						GLfloat ax = fabsf(dx);
						GLfloat ay = fabsf(dy);
						GLfloat ad = 0;
						if (ax > ay) {
							if (d > swipeDistance) type += L" long";
							ad = floorf((ax - ay) * 100.0f / ax);
							if (ad > 50) {
								if (dx > 0) type += L" right";
								else type += L" left";
							} else if (dx > 0) {
								if (dy < 0) type += L" right top";
								else type += L" right bottom";
							} else {
								if (dy < 0) type += L" left top";
								else type += L" left bottom";
							}
						} else {
							if (d > swipeDistance) type += L" long";
							ad = floorf((ay - ax) * 100.0f / ay);
							if (ad > 50) {
								if (dy < 0) type += L" top";
								else type += L" bottom";
							} else if (dy < 0) {
								if (dx > 0) type += L" right top";
								else type += L" left top";
							} else {
								if (dx > 0) type += L" right bottom";
								else type += L" left bottom";
							}
						}
					}
				}
			}
		}
		
		if (type.m_length != 0) {
			onTouch(type);
		}
	}
}