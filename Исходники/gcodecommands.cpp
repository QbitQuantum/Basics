QString toCommand(GCommands gcode, QChar &c)
{
    switch (gcode) {
    case G28: {
        if(c.isNull())
            return QString("G28");
        else
            return QString("G28 %1").arg(c.toUpper());
    }
    case G32:
        return QString("G32 S1");
    case G90:
        return QString("G90");
    case G91:
        return QString("G91");
    default:
        return QString("Not implemented or not supported!");

    }
}