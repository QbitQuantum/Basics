		REQUIRE(description.mutexGroups().size() == 8u);
		REQUIRE(description.mutexGroups()[0].facts().size() == 9u);
		CHECK(&description.mutexGroups()[0].facts()[0].value() == &description.variables()[0].values()[0]);
		REQUIRE(description.mutexGroups()[7].facts().size() == 2u);
		CHECK(&description.mutexGroups()[7].facts()[1].value() == &description.variables()[34].values()[1]);

		REQUIRE(description.initialState().facts().size() == 37u);
		CHECK(&description.initialState().facts()[0].value() == &description.variables()[0].values()[8]);
		CHECK(&description.initialState().facts()[36].value() == &description.variables()[36].values()[1]);

		REQUIRE(description.goal().facts().size() == 2u);
		CHECK(&description.goal().facts()[0].value() == &description.variables()[6].values()[0]);
		CHECK(&description.goal().facts()[1].value() == &description.variables()[7].values()[0]);

		REQUIRE(description.operators().size() == 34u);
		CHECK(description.operators()[0].predicate().name() == "activate-trans");
		REQUIRE(description.operators()[0].predicate().arguments().size() == 5u);
		CHECK(description.operators()[0].predicate().arguments()[0] == "philosopher-0");
		CHECK(description.operators()[0].predicate().arguments()[4] == "state-3");
		REQUIRE(description.operators()[0].preconditions().size() == 3u);
		CHECK(&description.operators()[0].preconditions()[0].value() == &description.variables()[4].values()[4]);
		CHECK(&description.operators()[0].preconditions()[1].value() == &description.variables()[16].values()[1]);
		CHECK(&description.operators()[0].preconditions()[2].value() == &description.variables()[0].values()[8]);
		REQUIRE(description.operators()[0].effects().size() == 1u);
		REQUIRE(description.operators()[0].effects()[0].conditions().size() == 0u);
		CHECK(&description.operators()[0].effects()[0].postcondition().value() == &description.variables()[0].values()[0]);
		CHECK(description.operators()[33].predicate().name() == "queue-write");
		REQUIRE(description.operators()[33].predicate().arguments().size() == 4u);
		CHECK(description.operators()[33].predicate().arguments()[0] == "philosopher-1");
		CHECK(description.operators()[33].predicate().arguments()[3] == "fork");