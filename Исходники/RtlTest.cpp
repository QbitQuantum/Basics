void RtlTest::testVisitor()
{
	StmtVisitorStub* visitor = new StmtVisitorStub();

	/* rtl */
	RTL *rtl = new RTL();
	rtl->accept(visitor);
	CPPUNIT_ASSERT(visitor->a);
	delete rtl;

	/* jump stmt */
	GotoStatement *jump = new GotoStatement;
	jump->accept(visitor);
	CPPUNIT_ASSERT(visitor->b);
	delete jump;

	/* branch stmt */
	BranchStatement *jcond = new BranchStatement;
	jcond->accept(visitor);
	CPPUNIT_ASSERT(visitor->c);
	delete jcond;

	/* nway jump stmt */
	CaseStatement *nwayjump = new CaseStatement;
	nwayjump->accept(visitor);
	CPPUNIT_ASSERT(visitor->d);
	delete nwayjump;

	/* call stmt */
	CallStatement *call = new CallStatement;
	call->accept(visitor);
	CPPUNIT_ASSERT(visitor->e);
	delete call;

	/* return stmt */
	ReturnStatement *ret = new ReturnStatement;
	ret->accept(visitor);
	CPPUNIT_ASSERT(visitor->f);
	delete ret;

	/* "bool" assgn */
	BoolAssign *scond = new BoolAssign(0);
	scond->accept(visitor);
	CPPUNIT_ASSERT(visitor->g);
	delete scond;

	/* assignment stmt */
	Assign *as = new Assign;
	as->accept(visitor);
	CPPUNIT_ASSERT(visitor->h);
	delete as;

	/* polymorphic */
	Statement* s = new CallStatement;
	s->accept(visitor);
	CPPUNIT_ASSERT(visitor->e);
	delete s;

	/* cleanup */
	delete visitor;
}