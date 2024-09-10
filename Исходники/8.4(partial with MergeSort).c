int compare(Rich a, Rich b) {
    if(a.wealth != b.wealth)
        return a.wealth - b.wealth;
    else if(a.age != b.age)
        return b.age - a.age;
    else
        return strCmp(b.name, a.name);
}