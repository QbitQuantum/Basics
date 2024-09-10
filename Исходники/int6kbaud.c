int main (int argc, char const * argv [])

{
	static char const * optv [] =
	{
		"B:c:D:F:m:p:P:q:S:uvw",
		"",
		"Atheros Serial Line Device Settings",
		"B n\tbaud rate is (n) [" LITERAL (UART_BAUDRATE) "]",
		"c s\tsend custom serial line command (s)",
		"D n\tuse (n) data bits [" LITERAL (UART_DATABITS) "]",
		"F n\tflow control is (n) ["LITERAL (UART_FLOWCTRL) "]",
		"m n\tcommand mode is (n)",
		"p f\tserial port is (f) [" DEVICE "]",
		"P n\tuse (n) parity bits [" LITERAL (UART_PARITY) "]",
		"q\tquiet mode",
		"S n\tuse (n) stop bits [" LITERAL (UART_STOPBITS) "]",
		"u\tforce default host port settings [115200 8N1]",
		"v\tverbose mode",
		"w\twake device [+++]",
		(char const *) (0)
	};
	struct uart uart =
	{
		{
			0,
			DEVICE
		},
		(char *)(0),
		UART_MODE,
		UART_BAUDRATE,
		UART_DATABITS,
		UART_PARITY,
		UART_STOPBITS,
		UART_FLOWCTRL,
		0
	};
	signed c;
	if (getenv (UART_PORT))
	{
		uart.port.name = strdup (getenv (UART_PORT));
	}
	while ((c = getoptv (argc, argv, optv)) != -1)
	{
		switch (c)
		{
		case 'B':
			_setbits (uart.flags, UART_ATBR);
			uart.baudrate = (uint64_t)(uintspec (optarg, 1, ULONG_MAX));
			break;
		case 'c':
			_setbits (uart.flags, UART_COMMAND);
			uart.string = optarg;
			break;
		case 'D':
			_setbits (uart.flags, UART_ATBR);
			uart.databits = (byte)(uintspec (optarg, 7, 8));
			break;
		case 'F':
			_setbits (uart.flags, UART_ATBR);
			uart.flowctrl = (byte)(uintspec (synonym (optarg, flowctrls, FLOWCTRLS), 0, UCHAR_MAX));
			break;
		case 'm':
			_setbits (uart.flags, UART_ATBR);
			uart.mode = (byte)(uintspec (synonym (optarg, modes, MODES), 0, UCHAR_MAX));
		case 'P':
			_setbits (uart.flags, UART_ATBR);
			uart.parity = (byte)(uintspec (synonym (optarg, paritybits, PARITYBITS), 0, UCHAR_MAX));
			break;
		case 'q':
			_setbits (uart.flags, UART_SILENCE);
			break;
		case 'p':
			uart.port.name = optarg;
			break;
		case 'S':
			_setbits (uart.flags, UART_ATBR);
			uart.stopbits = (unsigned)(uintspec (optarg, 1, 2));
			break;
		case 'u':
			_setbits (uart.flags, UART_DEFAULT);
			break;
		case 'v':
			_setbits (uart.flags, UART_VERBOSE);
			break;
		case 'w':
			_setbits (uart.flags, UART_WAKE);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (argc)
	{
		error (1, ENOTSUP, ERROR_TOOMANY);
	}
	openport (&uart.port, uart.flags);
	manager (&uart);
	closeport (&uart.port);
	return (0);
}