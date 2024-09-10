int test12() {
    int n = 35;
    int east = 4000;
    int north = -3933;
    Airways* pObj = new Airways();
    clock_t start = clock();
    double result = pObj->distance(n, east, north);
    clock_t end = clock();
    delete pObj;
    double expected = 5629.6661763113625;
    if(result == expected) {
        cout << "Test Case 12: Passed! Time: " << static_cast<double>(end-start)/CLOCKS_PER_SEC << " seconds" << endl;
        return 0;
    } else {
        cout << "Test Case 12: Failed! Time: " << static_cast<double>(end-start)/CLOCKS_PER_SEC << " seconds" << endl;
        return 1;
    }
}