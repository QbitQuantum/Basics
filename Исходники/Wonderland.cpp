int main()
{
	// Our application initialization params
	Application::InitializationParams initParams = {};
	initParams.sApplicationName = "Chronicles of a Fallen Soul";
	initParams.sEngineName = "Wonderland";
	initParams.sApplicationVersion = VK_MAKE_VERSION(0, 0, 1);
	initParams.sEngineVersion = VK_MAKE_VERSION(0, 0, 1);
	initParams.sTotalNumberPeonThreads = 4;
	initParams.sThreadRingBufferSize = 65000;

	// Create and initialize the main application
	Application mainApplication = {};
	if (!mainApplication.Initialize(initParams))
	{
		return false;
	}

	// Run the main loop
	mainApplication.MainLoop();

	//

	bool result;

	//

	// Get all creator a register instances we need
	Flux::ClassCreator* classCreatorInstance = Flux::ClassCreator::GetInstance();
	Flux::ClassRegister* classRegisterInstance = Flux::ClassRegister::GetInstance();
	Flux::TypeCreator* typeCreatorInstance = Flux::TypeCreator::GetInstance();
	Flux::TypeRegister* typeRegisterInstance = Flux::TypeRegister::GetInstance();
	Flux::DynamicMemberFunctionCreator* memberFunctionCreatorInstance = Flux::DynamicMemberFunctionCreator::GetInstance();

	// Basic type registration //
	Flux::Type* intType = typeCreatorInstance->CreateType("int");
	Flux::Type* floatType = typeCreatorInstance->CreateType("float");
	Flux::Type* charType = typeCreatorInstance->CreateType("char");
	Flux::Type* stringType = typeCreatorInstance->CreateType("string");
	Flux::Type* booleanType = typeCreatorInstance->CreateType("bool");
	Flux::Type* vectorType = typeCreatorInstance->CreateType("vector");

	// Class creation //

	// Create a new class
	Flux::Class* newClass = classCreatorInstance->CreateClass("Car");
	if (newClass == nullptr)
	{
		return false;
	}

	// Create a variable from the created class
	Flux::MemberVariable speedVariable;
	result = speedVariable.Build(floatType, "m_Speed");
	if (!result)
	{
		return false;
	}

	// Add the member variable
	result = newClass->AddMemberVariable(speedVariable);
	if(!result)
	{
		return false;
	}

	// Create a variable from the created class
	Flux::MemberVariable distanceVariable;
	result = distanceVariable.Build(intType, "m_CurrentDistance");
	if (!result)
	{
		return false;
	}

	// Add the member variable
	result = newClass->AddMemberVariable(speedVariable);
	if (!result)
	{
		return false;
	}

	// Create a variable from the created class
	Flux::MemberVariable costVariable;
	result = costVariable.Build(floatType, "m_CostPerDistance");
	if (!result)
	{
		return false;
	}

	// Add the member variable
	result = newClass->AddMemberVariable(speedVariable);
	if (!result)
	{
		return false;
	}

	// Function creation //

	// Create the nem member function
	Flux::DynamicMemberFunction* newFunction = memberFunctionCreatorInstance->CreateDynamicMemberFunction("CalculateTime", *newClass);
	if (newFunction == nullptr)
	{
		return false;
	}

	/*

		- Handle precisa ter um id de versão
	*/

	/*
		
		=> Dynamic Function:

		- Head		-> Definições de uma função (qual o nome, se pertence à uma classe, quais entradas... etc)
		- Body		-> Como esta definido o seu corpo, quais funções (boxes) são utilizados, quais foram as ligações efetuadas, variáveis utilizadas... etc
		- Linker	-> Realização da compilação da DynamicFunction em realtime.
	*/

	/*
		- Vamos ter uma nova classe que vai ser tipo um box, ele vai contar o ponto inicial, final e vai possuir blocos que vão se ligar entre si, esses blocos fazem referência
		à um box conectado.
		- Começando no bloco inicial, vamos ir para o proximo, aqui podemos ter por exemplo uma função membro, nosso objetivo será pegar os dados da função membro, fazer a chamada
		com ela utilizando as variáveis linkadas (nota que não foi incluido a geração dos nomes das variáveis).
		- Após isso vamos para a proxima função, que pode ser um loop por exemplo, o loop deve criar uma variável que vai ser o contador e usar os parâmetros de entrada para realizar
		as chamadas seguintes.

		- Da pra perceber que o ideal é fechar cada bloco, por exemplo no primeiro, podemos passar as variáveis linkadas aos sockets de entrada para o "fechador" da função membro
		utilizada e ela fica responsável por usar essas entradas e gerar a chamada, podendo até mesmo retornar e assim seguimos para a proxima box ou continuar por conta propria.
		- No segundo exemplo nos iriamos para um loop, ele vai ter os valores de entrada (index inicial, final, etc) e provavelmente deveriamos continuar a execução por conta
		propria.

		- Temos que pensar em como vamos fazer os ifs, os sequences, sets, gets, for eachs, prints, etc... São todas funções standard, intrinsic.
		- Talvez devemos separar tipo, funções membro, funções normais, loop for, if, set, get e assim vai... Só que as funções (tanto membro quando normais) existiriam de várias
		formas precisando serem registradas enquanto os outros seriam classes especializadas que não precisariam serem registradas, afinal já teriamos uma de cada tipo.
		- O ideal seria que tivermos uma forma de criar essas funções intrinsics, talvez seja possível faze-las na parte de funções normais ou quem sabe fazer um criador para elas.
	*/

	/*
		- Uma box pode ter inputs e outputs, não importa qual o tipo de box.
		- Uma input/output pode ser de vários tipos.

		- Uma box pode ser uma função, uma caixa de debug, um start ou end dentro de uma função, etc.
		- Uma input/output pode ser uma variável, um valor absoluto, uma constante, etc.
		- Uma input/output pode ter um valor temporário para teste na engine.
		- Uma input/output pode ser uma array, nesse caso ele não pode possuir um valor absoluto e sim deve ser uma variável.

		- Uma box SEMPRE deve ter (se tiver) apenas UMA entrada.
		- Uma box pode ter várias saídas desde que mantenha em mente que as saídas serão executadas em sequência (depende da interpretação da box)

		
	
	
	
	
	*/

	////////////////
	// INITIALIZE //
	////////////////
	MainViewController viewController;
	viewController.Initialize();

	////////////////////////
	////////////////////////
	////////////////////////

    return 0;
}