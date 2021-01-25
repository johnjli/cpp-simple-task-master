#include "consoleOutputs.h"
#include <functional>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <algorithm>

void Project::Init() {
    int nameLength = m_projectName.size();
    std::string str;

    std::cout << "\n\n";
    str = "\t\t\t\t  " + CreateStr(nameLength + 2, '_') + "\n";
    std::cout << str;
    str = "\t\t\t\t /" + CreateStr(nameLength + 1, '_') + "/ |\n";
    std::cout << str;
    str = "\t\t\t\t|" + CreateStr(nameLength + 2, '-') + "| |\n";
    std::cout << str;
    str = "\t\t\t\t| " + m_projectName + " | |\n";
    std::cout << str;
    str = "\t\t\t\t|" + CreateStr(nameLength + 2, '_') + "|/\n";
    std::cout << str << "\n\n\n";
}
std::string Project::CreateStr(int num, char c) {
    std::string temp;
    for (int i = 0; i < num; i++)
        temp.push_back(c);
    return temp;
}
std::string Project::VersiontoStr(float version) {
    std::string str;
    std::ostringstream ss;
    ss << version;
    str = ss.str();
    return str;
}
Project::Project() {
    m_projectName = "";
    numOptions = 0;
    numFunctions = 0;
    Init();
}
Project::Project(const std::string& projectname, float version) {
    m_projectName = projectname + VersiontoStr(version);
    numOptions = 0;
    numFunctions = 0;
    Init();
}
Project::Project(const std::string& projectname, float version, int numoptions) {
    m_projectName = projectname + VersiontoStr(version);
    numOptions = numoptions;
    numFunctions = 0;
    Init();
}
Project::Project(const std::string& projectname, float version, int numoptions, int numfuncts) {
    m_projectName = projectname + VersiontoStr(version);
    numOptions = numoptions;
    numFunctions = numfuncts;
    Init();
}
void Project::AddOption(const std::string& option) { vec.push_back(option); }
void Project::AddOption(const std::vector<std::string>& option) {
    for (const auto & i : option)
        vec.push_back(i);
}
void Project::AddOption(std::string option[]) {
    for (int i = 0; i < numOptions; i++)
        vec.push_back(option[i]);
}
int Project::ShowOptions() {
    std::string s;
    int temp;
    std::cout << "\tOptions:\n";
    std::cout << "\t-----------\n";

    for (int i = 0; i < vec.size(); i++)
        std::cout << "\t(" << i + 1 << "): " << vec.at(i) << std::endl;

    std::cout << "\n\t(q): Quit";

    std::cout << "\nMy Choice: ";
    std::getline(std::cin, s);
    if (s == "q") {
        temp = -1;
    } else {
        try {
            temp = std::stoi(s);
        } catch (std::invalid_argument e) {
            s = "";
            for (int i = 0; i < vec.size(); i++)
                s += "(" + std::to_string(i + 1) + ") ";
            ClearConsole(5 + vec.size());
            std::cout << "\033[A\33[2K";
            Log(lverror, "Please enter the correct option, choose from " + s + "\n");
            temp = ShowOptions();
        }
    }

    if (temp > numOptions) {
        s = "";
        for (int i = 0; i < vec.size(); i++)
            s += "(" + std::to_string(i + 1) + ") ";
        ClearConsole(5 + vec.size());
        std::cout << "\033[A\33[2K";
        Log(lverror, "Please enter the correct option, choose from " + s + "\n");
        temp = ShowOptions();
    }

    return temp;
}
void Project::CancelQuit() {

}
std::vector<std::string> Project::ReadFile(const std::string& address) {
    std::vector<std::string> fileVec;
    std::string line;
    std::ifstream myFile(address);

    if (myFile.is_open()) {
        Log(lvinfo, "File \"" + address + "\" opened");
        while (getline(myFile,line)) {
            fileVec.push_back(line);
        }
        myFile.close();
    } else {
        Log(lverror, "File \"" + address + "\" cannot open");
    }

    return fileVec;
}
void Project::WriteFile(std::vector<Object> writeVector, const std::string& address) {
    std::ofstream myFile(address);
    if (myFile.is_open()) {
        for (auto & i : writeVector)
            myFile << i.toString() << std::endl;
        Log(lvinfo, "File \"" + address + "\" writtedn in");
        myFile.close();
    } else {
        Log(lverror, "File \"" + address + "\" cannot be written");
    }
}
void Project::AddFunction(const std::function<void()>& funct) { functVec.push_back(funct); }
void Project::AddFunction(std::function<void()> funct[]) {
    for (int i = 0; i < numFunctions; i++)
        functVec.push_back(funct[i]);
}
void Project::OptionFunction(int option) { functVec.at(option - 1)(); }


void Object::RegexCapture(const std::string& regexStr, const std::string& input) {
    std::regex myRegex(regexStr);
    std::smatch match;
    if (std::regex_search(input,match,myRegex))
        for (int i = 0; i < match.size(); i++)
            m_regexCaptures.push_back(match.str(i));
    else
        Log(lverror, "Message doesn't match regex");
}
//int Object::getIndex(std::vector<std::string> vec, std::string) {
//    auto temp = std::find(vec.begin(), vec.end(), obj);
//    if (temp != vec.end())
//        return temp - vec.begin();
//    else
//        return -1;
//}


void ConsoleLog::Log(int lv, const std::string& message) {
    switch (lv) {
        case lverror:
            std::cout << "\x1B[31m[ERROR]:\033[0m " << message;
            break;
        case lvwarning:
            std::cout << "\x1B[33m[WARNING]:\033[0m " << message;
            break;
        case lvinfo:
        default:
            std::cout << "\x1B[32m[INFO]:\033[0m " << message;
            break;
    }
    std::cout << std::endl;
}
void ConsoleLog::ClearConsole(int num) {
    for (int i = 0; i < num; i++)
        std::cout << "\33[2K\033[A";
}
