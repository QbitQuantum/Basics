int main()
{
	LinkedList<std::string> list;

	list.add("Alice");
	list.add("Chuck");
	list.add("Elaine");
	list.add("fran");
	
	std::cout << "Here are the initial names : " << std::endl;
	list.displayList();
	std::cout << std::endl << std::endl;

	std::cout << "Now removing Elaine " <<std::endl<<std::endl;
	list.remove("Elaine");
	std::cout << "Here are the remaining elements." << std::endl;
	list.displayList();
	std::cout << std::endl;

    return 0;
}