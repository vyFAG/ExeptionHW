#pragma once



#include <exception>
#include <string>
#include <vector>
#include <queue>
#include <any>
#include <iostream>

extern std::string mainLog;

class BaseException : public std::exception
{
public:
    explicit BaseException(const char* message)
        : exceptionMsg(message) {}

    explicit BaseException(const std::string& message)
        : exceptionMsg(message) {}

    virtual ~BaseException() noexcept {}

    virtual const char* what() const noexcept {
        return exceptionMsg.c_str();
    }

    virtual const std::string getMsg() const noexcept {
        return exceptionMsg.c_str();
    }

protected:
    std::string exceptionMsg;
};



class RepeatableException : public BaseException
{
public:
    explicit RepeatableException(const char* message)
        : BaseException(message) {}

    explicit RepeatableException(const std::string& message)
        : BaseException(message) {}

    ~RepeatableException() noexcept {}
};



class ICommand
{
public:
    ICommand(std::string setCommandType)
    {
        commandType = setCommandType;
    }

    virtual void Execute() = 0;

    std::string commandType = "";
};



std::queue<ICommand*> commands = {};



void addToCommands(ICommand* command)
{
    commands.push(command);
}



class CBaseCommand : public ICommand
{
public:
    CBaseCommand(int setCommand) : ICommand("baseCommand")
    {
        command = setCommand;
    }

    void Execute()
    {
        // Some work with command
        if (9 < command)
        {
            command -= 1;
            throw new RepeatableException("RepeatableException");
        }

        else
        {
            return;
        }
    }

private:
    int command = 0;
};



class CToLogCommand : public ICommand
{
public:
    CToLogCommand(std::string setMessage) : ICommand("toLogCommand")
    {
        message = setMessage;
    }

    void Execute()
    {
        mainLog += message;
    }

private:
    std::string message;
};



class ExceptionHandler
{
public:
    static void handle(BaseException* exception, ICommand* command);
};



class CCommandRepeater : public ICommand
{
public:
    CCommandRepeater(ICommand* setCommand) : ICommand("commandRepeater")
    {
        command = setCommand;
    }

    void Execute()
    {
        try
        {
            command->Execute();
        }
        catch (BaseException* e)
        {
            ExceptionHandler::handle(e, this);
        }
    }

private:
    ICommand* command;
    int repeatCount = 0;
};



bool commandExecute()
{
    bool stop = false;
    bool isGood = true;

    while (!stop && commands.size() > 0)
    {
        ICommand* cmd = commands.front();

        try
        {
            if ("toLogCommand" == cmd->commandType)
            {
                isGood = false;
            }

            cmd->Execute();
        }
        catch (BaseException* e)
        {
            ExceptionHandler::handle(e, commands.front());
        }

        commands.pop();
    }

    return isGood;
}

