int main() {
    Queue x;
    x.add("George").add("Washington").add("was").add("here.");
    cout <<endl;

    // x.add("BREAK!");

    x.remove();
    x.add("NOT!");
    cout <<endl;
    x.remove();
    x.add("Just kidding.");
    cout <<endl;
    x.remove();
    x.add("But seriously.");
    cout <<endl;
    x.remove();

    x.remove();
    x.remove();
    x.add("Would a man joke?").add("Or would he choke?");
    x.remove();
    x.add("How crazy is Hollywood?");
    x.remove();
    x.remove();

    x.remove();

    return 0;
} //main()