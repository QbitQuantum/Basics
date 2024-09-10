static bool eval_dice(sourceinfo_t *si, char *s_input)
{
	static char buffer[1024], result[32];

	char op = '\0', *c = s_input;
	unsigned int dice, roll, x, y, z = 0;
	double total;

	while (*c && isspace(*c))
		++c;
	if (!*c || !isdigit(*c))
	{
		gs_command_report(si, _("Syntax: XdY [ {-|+|*|/} Z ]"));
		return false;
	}

	x = strtoul(c, &c, 10);
	if (x == 0 || c == NULL || ToLower(*c++) != 'd' || !isdigit(*c))
	{
		if (x < 1 || x > DICE_MAX_DICE)
		{
			gs_command_report(si, _("Only 1-100 dice may be thrown at once."));
			return false;
		}

		gs_command_report(si, _("Syntax: XdY [ {-|+|*|/} Z ]"));
		return false;
	}

	y = strtoul(c, &c, 10);
	if (c != NULL)
	{
		while (*c && isspace(*c))
			++c;

		if (*c && strchr("-+*/", *c) == NULL)
		{
			gs_command_report(si, _("Syntax: XdY [ {-|+|*|/} Z ]"));
			return false;
		}
	}

	if (x < 1 || x > 100)
	{
		gs_command_report(si, _("Syntax: XdY [ {-|+|*|/} Z ]"));
		return false;
	}

	if (y < 1 || y > DICE_MAX_SIDES)
	{
		gs_command_report(si, _("Only 1-100 sides may be used on a dice."));
		return false;
	}

	if (*c)
	{
		op = *c++;

		z = strtoul(c, &c, 10);

		while (*c && isspace(*c))
			++c;

		if (*c)
		{
			gs_command_report(si, _("Syntax: XdY [ {-|+|*|/} Z ]"));
			return false;
		}
		else if (op == '/' && z == 0)
		{
			gs_command_report(si, _("Can't divide by zero."));
			return false;
		}
	}

	total = 0.0;
	snprintf(buffer, 1024, "\2%s\2 rolled %ud%u: ", si->su->nick, x, y);
	for (roll = 0; roll < x; ++roll)
	{
		snprintf(result, 32, "%d ", dice = (1 + (arc4random() % y)));
		mowgli_strlcat(buffer, result, sizeof(buffer));
		total += dice;
	}

	if (op == '\0')
		snprintf(result, 32, " <Total: %g>", total);
	else
	{
		snprintf(result, 32, " <Total: %g(%c%u) = ", total, op, z);
		mowgli_strlcat(buffer, result, sizeof(buffer));
		switch (op)
		{
		  case '+':
			  total += z;
			  break;
		  case '-':
			  total -= z;
			  break;
		  case '/':
			  total /= z;
			  break;
		  case '*':
			  total *= z;
			  break;
		  default:
			  break;
		}
		snprintf(result, 32, "%g>", total);
	}
	mowgli_strlcat(buffer, result, sizeof(buffer));

	gs_command_report(si, "%s", buffer);
	return true;
}