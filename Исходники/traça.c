    char *name;
    bool active;
    int option;
    int maxcalls;
    int numcalls;
    char *s;
    // ... whatever else
};


#define REG_SYSC(x) [x] = {x, #x, false, 0, 0, 0, NULL}
static struct one_call global_call_list[] = {
#include "reg_sysc.c"
    {-1, NULL, false, 0, 0, 0, NULL}
};
static const int NUMCALLS = LENGTH(global_call_list);

static char *call_name(int syscall)
{
    int i = 0;
    struct one_call *c = global_call_list;
    while (i < NUMCALLS) {
        if (c[i].syscall == syscall)
            return c[i].name;
        i += 1;
    }
    return NULL;
}

/*
 * signal stuff