int main() {
    try {
        test_cal();
        test_fail_create();
        test_fail_call();

        u_cleanup();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}