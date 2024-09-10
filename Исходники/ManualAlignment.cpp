/**
 * Creates a point element as visible feedback for the user.
 */
SoNode* ManualAlignment::pickedPointsSubGraph(const SbVec3f& p, const SbVec3f& n, int id)
{
    static const float color_table [10][3] = {
        {1.0f,0.0f,0.0f}, // red
        {0.0f,1.0f,0.0f}, // green
        {0.0f,0.0f,1.0f}, // blue
        {1.0f,1.0f,0.0f}, // yellow
        {0.0f,1.0f,1.0f}, // cyan
        {0.7f,0.0f,0.0f},
        {0.0f,0.7f,0.0f},
        {0.7f,0.7f,0.0f},
        {0.7f,0.0f,0.5f},
        {1.0f,0.7f,0.0f}
    };

    int index = (id-1) % 10;

    SoRegPoint* probe = new SoRegPoint();
    probe->base.setValue(p);
    probe->normal.setValue(n);
    probe->color.setValue(color_table[index][0],color_table[index][1],color_table[index][2]);
    SbString s;
    probe->text.setValue(s.sprintf("RegPoint_%d", id));
    return probe;
}