static void rec(int* list, int place, uint32_t* primelist, int index)
{
    if (place == 6) {
        int total = 0;
        int i;
        for (i = 1; i < 6; i++)
            total += list[i];
        if (total < min) {
            min = total;
            int n;
            for (n = 1; n < 6; n++) {
                minlist[n] = list[n];
            }
        }
        return;
    }
    int i;
    for (i = index; primelist[i]; i++) {
        list[place] = primelist[i];
        int works = true;
        int n;
        for (n = 1; n < place; n++) {
            if (!Concatenate(list[n], list[place])) {
                works = false;
                break;
            }
        }
        if (works)
            rec(list, place + 1, primelist, i + 1);
    }
    return;
}