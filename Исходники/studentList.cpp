void removeStudent ( BST<Student> & studentList )
{
	if ( studentList.isEmpty() )
		cout << "No student information has been entered." << endl;
	else
	{
		Student delStudent;
	
		cout << "Enter the ID of the student you want to remove: ";
		cin >> delStudent.id;

		if ( studentList.remove(delStudent) )
		{
			cout << "Student Removed.\n"
				<< "--- Student's Info ---\n" << delStudent << endl;
		}
		else
			cout << "No Student with that ID was found.\n\n";
	}
}