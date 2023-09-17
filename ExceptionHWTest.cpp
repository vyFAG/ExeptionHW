#include "pch.h"
#include "CppUnitTest.h"
#include "ExceptionHW.h"
#include "ExceptionHW.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ExceptionHWTest
{
	TEST_CLASS(ExceptionHWTest)
	{
	public:
		TEST_METHOD(TestA)
		{
			std::queue<ICommand*> empty;
			std::swap(commands, empty);

			addToCommands(new CBaseCommand(10));

			Assert::IsTrue(commandExecute());
		}

		TEST_METHOD(TestB)
		{
			std::queue<ICommand*> empty;
			std::swap(commands, empty);

			addToCommands(new CBaseCommand(15));

			Assert::IsTrue(!commandExecute());
		}

		TEST_METHOD(LogMessageTest)
		{
			std::queue<ICommand*> empty;
			std::swap(commands, empty);

			mainLog = "";

			addToCommands(new CToLogCommand("Hello world!"));
		
			commandExecute();

			Assert::IsTrue(std::string("Hello world!") == mainLog);
		}

		TEST_METHOD(RepeatableTest)
		{
			std::queue<ICommand*> empty;
			std::swap(commands, empty);

			mainLog = "";

			addToCommands(new CCommandRepeater(new CToLogCommand("Hello world!")));

			commandExecute();

			Assert::IsTrue(std::string("Hello world!") == mainLog);
		}
	};
}
