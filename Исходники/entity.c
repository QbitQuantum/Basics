int is_abs_walkable(Entity** entities, int x, int y) {
    int walkable = is_walkable(entities[DIV(x)][DIV(y)]);
    if(MOD(x) != 0 && MOD(y) != 0)
        walkable = walkable && is_walkable(entities[DIV(x) + 1][DIV(y) + 1]);
    if(MOD(x) != 0)
        walkable = walkable && is_walkable(entities[DIV(x) + 1][DIV(y)]);
    if(MOD(y) != 0)
        walkable = walkable && is_walkable(entities[DIV(x)][DIV(y) + 1]);
    return walkable;
}