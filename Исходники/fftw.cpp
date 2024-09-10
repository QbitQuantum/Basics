rigor rigor_from(const char *name)
{
    using std::tolower;
    if (name) {
        switch (tolower(name[0])) {
        default:  break;
        case 'm': return measure;
        case 'p': return patient;
        case 'e':
            switch (tolower(name[1])) {
            default:  // Assume estimate
            case 's': return estimate;
            case 'x': return exhaustive;
            }
        case 'w': return wisdom_only;
        }
    }

    return measure;
}