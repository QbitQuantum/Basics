int main() {
    try {
        test_read();

        u_cleanup();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}