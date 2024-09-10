TaskToQuiz::TaskToQuiz()
{
	registerHelper(new TaskGroupToQuiz());
	registerHelper(new TaskQuestionToQuiz());
	registerHelper(new TaskMTRTableToQuiz());
}