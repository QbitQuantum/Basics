void GroupOfButtons::draw()
{
    drawGradient(Area(Area::CXYWH, cx, cy, getW(), getH()), Color(0,0,0,100), Color(0,0,0,0));

    al_draw_text(font(font_size), Color::white(), cx, cy - getH()/2 + space()*1.5 - font_size/2, ALLEGRO_ALIGN_CENTER, title.c_str());

    for (auto& b: buttons) {
        b.draw();
    }
    for (auto& t: textboxes) {
        t.box.draw();
    }
}