int main() {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::strchr;
   
    Worker* in[SIZE]; // array of pointers to Worker based classes
    int ct;
	// get input from user and store in Worker*
    for (ct=0; ct<SIZE; ct++) { 
        char choice;
        cout<<"Enter the employee category:\n"<<"w: waiter s: singer "
             <<"t: singing waiter q: quit\n";
        cin>>choice;
        while(strchr("wstq", choice)==nullptr) {
            cout<<"Bad input! Please enter a w, s, t, or q choice: ";
            cin>>choice;
        }
		if(choice=='q')
			break;		//not to take through Set process
        switch(tolower(choice)) {
		case 'w':
            in[ct]=new Waiter;
            break;
        case 's':
            in[ct]=new Singer;
            break;
        case 't':
            in[ct]=new SingingWaiter;
            break;
        }
        cin.get();
        in[ct]->Set(); // get information about chosen worker
    }

    //Exam Simulation: uses pointers to workers : waiters, singers, and singingwaiters take mandatory exam
    // required for continued employment. Only 1 person can take exam at a time in manager's room.

    QueueTP<Worker*> exam(ct);
    Worker* out[SIZE];

    int total_exam_mins=0;
    int empl_exam_mins=1;
    int failed=0;
    int passed=0;
    int index=0;
    bool correct_answer=false;
	std::srand(time(0));
    // Time limit for exam = 10 mins, if employee can't provide correct answer within 10 mins, employee fails the exam.
	int timelimit = 10;

    while (!exam.isfull()) {
        exam.enqueue(in[index]);
        index++;
    }
	index=0; // reset array index to 0
	cout<<"\nThe number of employees taking exam: " <<exam.queuecount()
		<<", Exam time limit = "<< timelimit<<" minutes."<<endl;

    while (!exam.isempty()) {
        correct_answer = passedexam(10); // passedexam randomly generates a number and compares to answer(argument), true if equal
		if (correct_answer && (empl_exam_mins<timelimit) && !exam.isempty()) { 
            exam.dequeue(out[index]);	//remove from queue, and move on to next employee
            cout<<"\nPASSED! Employee ["<<out[index]->Worker::Name()<<", "<<
				out[index]->Worker::ID()<<"], exam time: "<<empl_exam_mins<<"minutes.";
            empl_exam_mins=1; // reset individual time of exam for the next employee
            index++;
            passed++; // increase Passed Employee count
        } else 
			if (!correct_answer && (empl_exam_mins>timelimit) && !exam.isempty()) { 
				exam.dequeue(out[index]);	//remove from queue and move on to the next employee
				cout<<"\nFAILED! Employee ["<< out[index]->Worker::Name()<<", "<<
					out[index]->Worker::ID()<<"], exam time: "<<empl_exam_mins<<" minutes.";
				empl_exam_mins=1;
				index++;
				failed++;
			} else
				if (!correct_answer && !exam.isempty()) // if correct answer is not generated and time is within the timelimit,
					empl_exam_mins++;       // move on to the next cycle (minute) and try again to generate an answer

        total_exam_mins++;
    }
    
    cout<<"\n\nTotal exam time: "<< total_exam_mins<<" minutes.";
    cout<<"\nPassed: "<<passed;
    cout<<"\nFailed: "<<failed;

    // Employee overview, doublechecking that Worker* array of pointers contains correct information and values
    cout<<"\n\nEmployee overview: \n\n";
    for(int i=0; i<ct; i++) {
        out[i]->Show();		// display info
        delete in[i];		// delete stored pointer objects
        cout<<endl;
    }

    cout << "\nBye.";
    return 0;
}