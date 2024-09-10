					inline Val parseVal()
					{
						// Check value type
						switch(getC())
						{
							case '{': return parseObj();
							case '[': return parseArr();
							case '"': return parseStr();
							case 't': return parseBlnTrue();
							case 'f': return parseBlnFalse();
							case 'n': return parseNll();
						}

						// Check if value is a number
						if(isNumStart(getC())) return parseNum();

						throwError("Invalid value", std::string{"No match for values beginning with `"} + getC() + "`");

						return Val{Nll{}};
					}