int main() {
    Signal<void()> sig;

    HelloWorld hello;
    sig.connect(hello);

    sig();

    return 0;
}