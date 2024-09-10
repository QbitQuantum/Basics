void ConfigIO :: loadParam (const char *param)
{
  char line [10240];
  char paramName [10240];
  strncpy_s (line, param, sizeof (line));

  char *div = strchr (line, '=');

  for (size_t f = 0; f < parameters.size (); f ++)
      {
        strcpy_s (paramName, parameters [f].name);
        trimWhiteSpace (paramName);
        if (strnicmp (paramName, line, strlen (paramName)) == 0)
           {
             if (parameters [f].type == INT) *parameters [f].pInt = atoi (div + 1);
             if (parameters [f].type == UNSIGNED) *parameters [f].pUnsigned = atoi (div + 1);
             if (parameters [f].type == BOOL) {
				 std::string boolValue = std::string(div+1);
				 if (boolValue.compare("true") == 0)
					 *parameters [f].pBool = true;
				 else if (boolValue.compare("false") == 0)
					 *parameters [f].pBool = false;
				 else
				 {
					 *parameters [f].pBool = !! atoi (div + 1);
				 }

			 }
             if (parameters [f].type == DOUBLE) *parameters [f].pDouble = atof (div + 1);
             if (parameters [f].type == STRING)
                {
//                  if (div [1] != '"') continue;
//                  if (strchr (div + 2, '"') == NULL) continue;
//                  *strchr (div + 2, '"') = '\0';
//                  *parameters [f].pString = div + 2;
                  if (div [1] == '"')
                     {
                       if (strchr (div + 2, '"') == NULL) continue;
                       *strchr (div + 2, '"') = '\0';
                       *parameters [f].pString = div + 2;
                     }
                  else if (div [1] == '\'')
                     {
                       if (strchr (div + 2, '\'') == NULL) continue;
                       *strchr (div + 2, '\'') = '\0';
                       *parameters [f].pString = div + 2;
                     }
                  else 
                     {  
//                        for (char *p = div + 2; *p != '\0'; p ++)  // already trimmed
//                             if (isspace (*p)) *p = '\0';
                       *parameters [f].pString = div + 1;
                     }
                }
             if (parameters [f].type == ENUM)
             {
                if (strtol(div+1, (char **)NULL, 10)==0)
                {
                   // it is not a number
                   if (parameters [f].enum_map->is_valuename(div+1))
                      *parameters [f].pInt = parameters [f].enum_map->get_value(div+1);
                   else
                      printf("Warning: Invalid enum value name '%s' of '%s', leaving default value.\n",
                             div+1, parameters [f].name); // leave default value_type
                } else
                   *parameters [f].pInt = atoi (div + 1);
             }
           }
      }

  for (size_t f = 0; f < checks.size (); f ++)
      {
        strcpy_s (paramName, checks [f].name);
        trimWhiteSpace (paramName);
        if (strnicmp (paramName, line, strlen (paramName)) == 0)
           {
             if (checks [f].type == INT)
                {
                  int v = atoi (div + 1);
                  if (checks [f].vInt != v) cerr << "Config-file parameter " << paramName << " (" << v << ") does not match to compile time value " << checks [f].vInt << endl;
                  assert (checks [f].vInt == v);
                }
             if (checks [f].type == UNSIGNED)
                {
                  unsigned v = atoi (div + 1);
                  if (checks [f].vUnsigned != v) cerr << "Config-file parameter " << paramName << " (" << v << ") does not match to compile time value " << checks [f].vUnsigned << endl;
                  assert (checks [f].vUnsigned == v);
                }
             if (checks [f].type == BOOL)
                {
                  bool v = !! atoi (div + 1);
                  if (checks [f].vBool != v) cerr << "Config-file parameter " << paramName << " (" << v << ") does not match to compile time value " << checks [f].vBool << endl;
                  assert (checks [f].vBool == v);
                }
             if (checks [f].type == DOUBLE)
                {
                  double v = atof (div + 1);
                  if (checks [f].vDouble != v) cerr << "Config-file parameter " << paramName << " (" << v << ") does not match to compile time value " << checks [f].vDouble << endl;
                  assert (checks [f].vDouble == v);
                }
           }
      }
}