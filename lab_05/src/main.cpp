#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <thread>
#include <sstream>
#include <chrono>

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class PrintCommand : public Command {
    std::string message;
public:
    PrintCommand(const std::string &msg) : message(msg) {}
    void execute() override {
        std::cout << message << std::endl;
    }
};

class FilePrintCommand : public Command {
    std::string message;
    std::string filename;
public:
    FilePrintCommand(const std::string &msg, const std::string &file) : message(msg), filename(file) {}
    void execute() override {
        std::ofstream outfile(filename, std::ios::app);
        if (outfile.is_open()) {
            outfile << message << std::endl;
            outfile.close();
        }
    }
};

class ArithmeticCommand : public Command {
    char operation;
    double operand1, operand2;
public:
    ArithmeticCommand(char op, double op1, double op2) : operation(op), operand1(op1), operand2(op2) {}
    void execute() override {
        double result;
        switch (operation) {
            case '+': result = operand1 + operand2; break;
            case '-': result = operand1 - operand2; break;
            case '*': result = operand1 * operand2; break;
            case '/': result = operand1 / operand2; break;
            default: std::cerr << "Invalid operation" << std::endl; return;
        }
        std::cout << "Result: " << result << std::endl;
    }
};

class LoopCommand : public Command {
    int count;
    std::vector<std::shared_ptr<Command>> commands;
public:
    LoopCommand(int cnt) : count(cnt) {}
    void addCommand(std::shared_ptr<Command> cmd) {
        commands.push_back(cmd);
    }
    void execute() override {
        for (int i = 0; i < count; ++i) {
            for (auto &cmd : commands) {
                cmd->execute();
            }
        }
    }
};

class ForCommand : public Command {
    int start, end, step;
    std::vector<std::shared_ptr<Command>> commands;
public:
    ForCommand(int s, int e, int st) : start(s), end(e), step(st) {}
    void addCommand(std::shared_ptr<Command> cmd) {
        commands.push_back(cmd);
    }
    void execute() override {
        for (int i = start; i < end; i += step) {
            for (auto &cmd : commands) {
                cmd->execute();
            }
        }
    }
};

class IfCommand : public Command {
    double operand1, operand2;
    char operation;
    std::vector<std::shared_ptr<Command>> trueCommands;
public:
    IfCommand(double op1, double op2, char op) : operand1(op1), operand2(op2), operation(op) {}
    void addTrueCommand(std::shared_ptr<Command> cmd) {
        trueCommands.push_back(cmd);
    }
    void execute() override {
        bool condition = false;
        switch (operation) {
            case '=': condition = operand1 == operand2; break;
            case '>': condition = operand1 > operand2; break;
            case '<': condition = operand1 < operand2; break;
            default: std::cerr << "Invalid comparison operator" << std::endl; return;
        }
        if (condition) {
            for (auto &cmd : trueCommands) {
                cmd->execute();
            }
        }
    }
};

std::vector<std::shared_ptr<Command>> parseCommands(std::istream &input);

std::shared_ptr<ForCommand> parseForCommand(std::istringstream &iss, std::istream &input) {
    int start, end, step;
    iss >> start >> end >> step;
    auto forCmd = std::make_shared<ForCommand>(start, end, step);
    std::string forLine;
    while (std::getline(input, forLine) && forLine != "endfor") {
        std::istringstream forIss(forLine);
        auto forCmds = parseCommands(forIss);
        for (auto &cmd : forCmds) {
            forCmd->addCommand(cmd);
        }
    }
    return forCmd;
}

std::shared_ptr<IfCommand> parseIfCommand(std::istringstream &iss, std::istream &input) {
    double op1, op2;
    char op;
    iss >> op1 >> op >> op2;
    auto ifCmd = std::make_shared<IfCommand>(op1, op2, op);
    std::string ifLine;
    while (std::getline(input, ifLine) && ifLine != "endif") {
        std::istringstream ifIss(ifLine);
        auto ifCmds = parseCommands(ifIss);
        for (auto &cmd : ifCmds) {
            ifCmd->addTrueCommand(cmd);
        }
    }
    return ifCmd;
}

std::shared_ptr<LoopCommand> parseLoopCommand(std::istringstream &iss, std::istream &input) {
    int count;
    iss >> count;
    auto loopCmd = std::make_shared<LoopCommand>(count);
    std::string loopLine;
    while (std::getline(input, loopLine) && loopLine != "endloop") {
        std::istringstream loopIss(loopLine);
        auto loopCmds = parseCommands(loopIss);
        for (auto &cmd : loopCmds) {
            loopCmd->addCommand(cmd);
        }
    }
    return loopCmd;
}

std::vector<std::shared_ptr<Command>> parseCommands(std::istream &input) {
    std::vector<std::shared_ptr<Command>> commands;
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        if (command == "print") {
            std::string msg;
            std::getline(iss, msg);
            commands.push_back(std::make_shared<PrintCommand>(msg));
        } else if (command == "fileprint") {
            std::string msg, filename;
            iss >> filename;
            std::getline(iss, msg);
            commands.push_back(std::make_shared<FilePrintCommand>(msg, filename));
        } else if (command == "add" || command == "sub" || command == "mul" || command == "div") {
            char op = (command == "add") ? '+' : (command == "sub") ? '-' : (command == "mul") ? '*' : '/';
            double op1, op2;
            iss >> op1 >> op2;
            commands.push_back(std::make_shared<ArithmeticCommand>(op, op1, op2));
        } else if (command == "loop") {
            commands.push_back(parseLoopCommand(iss, input));
        } else if (command == "for") {
            commands.push_back(parseForCommand(iss, input));
        } else if (command == "if") {
            commands.push_back(parseIfCommand(iss, input));
        }
    }
    return commands;
}

void executeCommands(const std::vector<std::shared_ptr<Command>> &commands, int lineNumber) {
    auto start = std::chrono::system_clock::now();
    std::cout << "Thread " << lineNumber << " started at " << std::chrono::system_clock::to_time_t(start) << std::endl;
    for (auto &cmd : commands) {
        cmd->execute();
    }
    auto end = std::chrono::system_clock::now();
    std::cout << "Thread " << lineNumber << " finished at " << std::chrono::system_clock::to_time_t(end) << std::endl;
}

int main() {
    std::vector<std::string> lines;
    std::string line;

    std::cout << "Enter commands (type 'end' to finish input):" << std::endl;
    while (std::getline(std::cin, line) && line != "end") {
        lines.push_back(line);
    }

    std::vector<std::thread> threads;
    for (size_t i = 0; i < lines.size(); ++i) {
        std::istringstream iss(lines[i]);
        auto commands = parseCommands(iss);
        threads.emplace_back(executeCommands, commands, i + 1);
    }

    for (auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    return 0;
}



