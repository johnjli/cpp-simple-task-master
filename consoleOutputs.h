// @author John Li
// Last Updated: Dec 24 2020
#include <functional>
#include <string>
#include <vector>

class ConsoleLog {
public:
    // Clear the number of lines as specified
    static void ClearConsole(int num);

    // Log function sends a string to console if there is an error, warning, or info message
    enum lvlognum { lverror = 0, lvwarning, lvinfo };
    static void Log (int lv, const std::string& message);
    void ShowConsole();
};

class Object : public ConsoleLog {
protected:
    std::vector<std::string> m_regexCaptures;
public:
    virtual std::string toString() = 0;
//    int getIndex(std::vector<std::string> vec, std::string str);
    void RegexCapture(const std::string& regexStr, const std::string& input);
};

class Project : public ConsoleLog {
private:
    std::string m_projectName;
    // Vector of options
    std::vector<std::string> vec;
    std::vector< std::function<void()> > functVec;
    int numLines{};

    // Sends to console the title of the project
    void Init();
    // Creates a string of chars given the number of the char
    static std::string CreateStr(int num, char c);
    // Takes a float and converts it to a string
    static std::string VersiontoStr(float version);

public:
    int numOptions, numFunctions;

    // Constructors
    Project();
    Project(const std::string& projectname, float version);
    Project(const std::string& projectname, float version, int numoptions);
    Project(const std::string& projectname, float version, int numoptions, int numfunctions);

    // Adds string options that get printed out in ShowOptions()
    void AddOption(const std::string& option);
    void AddOption(const std::vector<std::string>& option);
    void AddOption(std::string option[]);
    int ShowOptions();
    void CancelQuit();

    // Reads a file and outputs a vector of strings
    static std::vector<std::string> ReadFile(const std::string& address);

    // Write to a file using a vector of objects
    static void WriteFile(std::vector<Object> writeVector, const std::string& address);

    // Adds a function to the functVec which is then called in OptionFunction(int)
    void AddFunction(const std::function<void()>& funct);
    void AddFunction(std::function<void()> funct[]);
    void OptionFunction(int option);
};
