int main()
{
	/*all the error checking in exec is same as lock/cv so no need to repeat */

	PrintF("\nTrying invalid address in Fork:\n", sizeof("\nTrying invalid address in Fork:\n"), 0, 0);
	Fork((void*)4000);
	PrintF("\nTesting Exec\n", sizeof("\nTesting Exec\n"), 0, 0);
    Exec("../test/testfiles", 17);
    Fork(test);
    PrintF("\nTrying invalid address in Exec:\n", sizeof("\nTrying invalid address in Exec:\n"), 0, 0);
    Exec((char*) 33201, 4);
    PrintF("\nTrying invalid size in Exec:\n", sizeof("\nTrying invalid size in Exec:\n"), 0, 0);
    Exec("../test/testfiles", -1);
    PrintF("\nTrying executable name that doesn't exist:\n", sizeof("\nTrying executable name that doesn't exist:\n"), 0, 0);
    Exec("../test/nonsense", 16);
    PrintF("\nTesting Exec again\n", sizeof("\nTesting Exec again\n"), 0, 0);
    Exec("../test/testfiles", 17);

    /* DOESN"T PRINT CORRECT OUTPUT, BUT SHOWS THAT YOU CAN HAVE TWO PROCESSES GOING AT SAME TIME
    Exec("../test/lock_test", 17);
    Exec("../test/lock_test", 17);*/
}