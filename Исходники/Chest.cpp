void Chest::ExamineUnit(ui::Gui &table, const Point &start, const Point &range) const
{
    Point nameplate = start.Moved(Point(1, 0));
    // name
    table.SetTextColor(Color(1, 1, 1));
    table.Write(nameplate, "Chest");
    table.Write(nameplate.Moved(Point(0, 2)), "Press E");
    table.Write(nameplate.Moved(Point(0, 3)), "to loot");
}