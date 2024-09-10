// refcard shows a reference card of shapes
void refcard(int width, int height) {
	char *shapenames[] = {
		"Circle",
		"Ellipse",
		"Rectangle",
		"Rounded Rectangle",
		"Line",
		"Polyline",
		"Polygon",
		"Arc",
		"Quadratic Bezier",
		"Cubic Bezier",
		"Image"
	};
	VGfloat shapecolor[4];
	RGB(202, 225, 255, shapecolor);
	VGfloat top = height * .95, sx = 500, sy = top, sw = width * .05, sh = height * .045, dotsize = 7, spacing = 2.0;

	int i, ns = sizeof(shapenames) / sizeof(char *), fontsize = height * .033;
	Start(width, height);
	sx = width * 0.10;

	Fill(128, 0, 0, 1);
	TextEnd(width - 20, height / 2, "OpenVG on the Raspberry Pi", fontsize + (fontsize / 2));
	Fill(0, 0, 0, 1);
	for (i = 0; i < ns; i++) {
		Text(sx + sw + sw / 2, sy, shapenames[i], fontsize);
		sy -= sh * spacing;
	}
	sy = top;
	VGfloat cx = sx + (sw / 2), ex = sx + sw;
	setfill(shapecolor);
	Circle(cx, sy, sw);
	coordpoint(cx, sy, dotsize, shapecolor);
	sy -= sh * spacing;
	Ellipse(cx, sy, sw, sh);
	coordpoint(cx, sy, dotsize, shapecolor);
	sy -= sh * spacing;
	Rect(sx, sy, sw, sh);
	coordpoint(sx, sy, dotsize, shapecolor);
	sy -= sh * spacing;
	Roundrect(sx, sy, sw, sh, 20, 20);
	coordpoint(sx, sy, dotsize, shapecolor);
	sy -= sh * spacing;

	StrokeWidth(1);
	Stroke(204, 204, 204, 1);
	Line(sx, sy, ex, sy);
	coordpoint(sx, sy, dotsize, shapecolor);
	coordpoint(ex, sy, dotsize, shapecolor);
	sy -= sh;

	VGfloat px[5] = { sx, sx + (sw / 4), sx + (sw / 2), sx + ((sw * 3) / 4), sx + sw };
	VGfloat py[5] = { sy, sy - sh, sy, sy - sh, sy };

	Polyline(px, py, 5);
	coordpoint(px[0], py[0], dotsize, shapecolor);
	coordpoint(px[1], py[1], dotsize, shapecolor);
	coordpoint(px[2], py[2], dotsize, shapecolor);
	coordpoint(px[3], py[3], dotsize, shapecolor);
	coordpoint(px[4], py[4], dotsize, shapecolor);
	sy -= sh * spacing;

	py[0] = sy;
	py[1] = sy - sh;
	py[2] = sy - (sh / 2);
	py[3] = py[1] - (sh / 4);
	py[4] = sy;
	Polygon(px, py, 5);
	sy -= (sh * spacing) + sh;

	Arc(sx + (sw / 2), sy, sw, sh, 0, 180);
	coordpoint(sx + (sw / 2), sy, dotsize, shapecolor);
	sy -= sh * spacing;

	VGfloat cy = sy + (sh / 2), ey = sy;
	Qbezier(sx, sy, cx, cy, ex, ey);
	coordpoint(sx, sy, dotsize, shapecolor);
	coordpoint(cx, cy, dotsize, shapecolor);
	coordpoint(ex, ey, dotsize, shapecolor);
	sy -= sh * spacing;

	ey = sy;
	cy = sy + sh;
	Cbezier(sx, sy, cx, cy, cx, sy, ex, ey);
	coordpoint(sx, sy, dotsize, shapecolor);
	coordpoint(cx, cy, dotsize, shapecolor);
	coordpoint(cx, sy, dotsize, shapecolor);
	coordpoint(ex, ey, dotsize, shapecolor);

	sy -= (sh * spacing * 1.5);
	Image(sx, sy, 100, 100, "starx.jpg");

	End();
}