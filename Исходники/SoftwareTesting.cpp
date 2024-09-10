//this function takes the command from the cmd into commands that the program knows
void ParseCommand(Command cmd, std::vector<std::string> payload)
{
	if (cmd == Invalid)
	{
		printMessage("Invalid command.");
	}

	//adds a student
	else if (cmd == Add)
	{
		//Add a student
		if (payload.size() != 6)
		{
			//bad news throw the user an error.
			printMessage("Command add recieved incorrect # of arguments.");
		}
		else
		{
			//constuct the student
			Student toAdd = Student(payload[0], payload[1], payload[2],
				std::stoi(payload[3]), std::stoi(payload[4]), std::stoi(payload[5]));

			//make sure that id dosent exsist
			std::vector<Student> toCheck = students.searchStudents(students.ID, toAdd.getUID());

			//if to check == 0 then student doesnt exsist
			if (toCheck.size() < 100)
			{
				//make sure the student is valid
				if (!toAdd.isValidStudent())
				{
					printMessage("Invalid student attribute.");
					return;
				}

				//add
				students.addStudent(toAdd);
				students.saveStudent();
				std::cout << toAdd.getName() + " successfully added" << std::endl;
			}
			else
			{
				std::cout << "Student already exists" << std::endl;
			}
		}
	}

	//remove a student
	else if (cmd == Remove)
	{
		//see if student exsists
		std::vector<Student> toCheck = students.searchStudents(students.ID, payload[0]);

		//see if student exsist
		if (toCheck.size() != 0)
		{
			std::cout << "Student does not exist." << std::endl;
		}
		else
		{
			//delete student
			students.deleteStudent(toCheck[0]);
			students.saveStudent();
			std::cout << "Student deleted successfully" << std::endl;
		}
	}

	//search for student
	else if (cmd == Search)
	{
		//make sure there are arguments 
		if (payload.size() == 0)
		{
			std::cout << "Printing all students:" << std::endl;
			students.printAllStudents();
			return;
		}
		else
		{
			//slit the payload
			std::vector<std::string> commands = fileIO::split(payload[0], '=');

			//make sure the format  is correct
			if (commands.size() < 2)
			{
				printMessage("Search argument recieved invalid. Format should be [email protected].");
			}
			else
			{
				Students queryList = Students(students.searchStudents(commands[0],commands[1]));

				//iterate through rest of the arguments
				for (int i = 1; i < payload.size(); i++)
				{
					std::vector<std::string> commands = fileIO::split(payload[i], '=');

					if (commands.size() != 2)
					{
						printMessage("Search argument recieved invalid. Format should be [email protected].");
					}

					queryList = queryList.searchStudents(commands[0], commands[1]);
				}
			
				queryList.printAllStudents();
			}
		}
	}

	//update the student
	else if (cmd == Update)
	{
		//search for the student
		std::vector<Student> tempStudents = students.searchStudents(Students::ID, payload[0]);
		
		//for each argument update that one
		for (int i = 1; i < payload.size(); i++)
		{
			std::vector<std::string> commands = fileIO::split(payload[i], '=');
			students.updateInfo(tempStudents[0], commands);
		}

		students.saveStudent();
	}
	//you need help so print it
	else if (cmd == Help)
	{
		std::cout << "Here are a list of all the example commands: " << std::endl;
		std::cout << "add <name>,<UID>,<email>,<firstscore>,<secondscore>,<thirdscore>" << std::endl;
		std::cout << "remove <UID>" << std::endl;
		std::cout << "search UID=<id>,name=<bob>" << std::endl;
		std::cout << "update <UID>,UID=<id>,name=<new name>" << std::endl;
	}
}