int main(int argc, char* argv[])
{
    const pie p1(1);
    const pie p2{2};

    pie p3 = pie(3);
    p3 = pie(4);

    pie p5{1, 2, 3, 4};

    pie p6 = {1, 2, 3, 4};

    assertEqual(p1, p2);
    assertEqual(p1, p3);

    {
        std::vector<int> v1(1);
        std::vector<int> v2{2};

        assertEqual(v1, v2);
    }
    {
        std::vector<int> v3{3, 4, 5};
        std::vector<int> v4 = {3, 4, 5};
        assertEqual(v3, v4);
    }
    {
        std::vector<int> v5(2, 1);
        std::vector<int> v6{2, 1};
        assertEqual(v5, v6);
    }
}