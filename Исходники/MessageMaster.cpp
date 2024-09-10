char *get_dragged_file(char *buffer, WPARAM wParam)
{
    HDROP hDrop = (HDROP) wParam;
    buffer[0] = 0;
    DragQueryFile(hDrop, 0, buffer, MAX_PATH);
    DragFinish(hDrop);
    return buffer;
}