#include "ExceptionHW.h"

std::string mainLog = "";

void ExceptionHandler::handle(BaseException* exception, ICommand* command)
{
    if ("RepeatableException" == exception->getMsg())
    {
        if ("commandRepeater" == command->commandType)
        {
            commands.push(new CToLogCommand(std::string(exception->what() + std::string(" ") + command->commandType)));
        }
        else
        {
            commands.push(new CCommandRepeater(command));
        }
    }
}