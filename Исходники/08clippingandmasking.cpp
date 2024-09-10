static void ClipByMaskExample(kCanvas &canvas)
{
    kPen pen(kColor(255, 127, 39), 4);
    kBrush brush(kColor(255, 201, 14));

    kTransform tfm;
    tfm.scale(0.5f, 0.5f);
    tfm.translateby(-25, 15);
    {
        kCanvasClipper clipper(canvas, *mask, tfm, kExtendType::Wrap, kExtendType::Wrap);

        canvas.Rectangle(kRect(10, 25, 50, 65), &pen, &brush);
        canvas.RoundedRectangle(kRect(60, 25, 100, 65), kSize(5, 5), &pen, &brush);
        canvas.Ellipse(kRect(110, 25, 150, 65), &pen, &brush);

        const kPoint points[] = {
            kPoint(180, 25),
            kPoint(200, 45),
            kPoint(180, 65),
            kPoint(160, 45)
        };
        canvas.Polygon(points, 4, &pen, &brush);
    }
}