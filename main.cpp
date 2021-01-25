#include <iostream>
#include <string>
#include <utility>
#include "consoleOutputs.h"

class Task : public Object {
public:
    std::string taskName;
    bool reminder;
    int time;

    Task() {
        taskName = "";
        reminder = false;
        time = 0;
    }
    explicit Task(const std::string& str) {
        RegexCapture(R"(([A-Za-z]+.*)\s(\d+)\s(yes|no))", str);
        taskName = m_regexCaptures.at(1);
        time = std::stoi(m_regexCaptures.at(2));
        reminder = (m_regexCaptures.at(3) == "yes");
    }
    std::string toString() override {
        std::string str;
        str = "\n[TASKNAME]: " + taskName +
              " [TIME]: " + std::to_string(time) +
              " [REMINDER]: " + ((reminder) ? "is on" : "isn't on");
        return str;
    }
};

class TaskList : public Object {
private:
    std::vector<Task> taskVec;
public:
    void AddTask(const Task& task) {
        taskVec.push_back(task);
    }
    void RemoveTask(int taskNum) {
        taskVec.erase(taskVec.begin() + taskNum - 1);
    }
    void ModifyTask(int taskNum) {
        Task task = taskVec.at(taskNum - 1);

        std::string str;
        std::cout << "\n[TASKNAME]: ";
        getline(std::cin, str);
        task.taskName = str;

        std::cout << "\n[TIME]: ";
        getline(std::cin, str);
        task.time = std::stoi(str);

        std::cout << "\n[REMINDER]: ";
        getline(std::cin, str);
        task.reminder = (str == "yes");
        Task newTask = task;

        RemoveTask(taskNum - 1);
        taskVec.insert(taskVec.begin() + taskNum - 1, newTask);
    }
    std::string toString() override {
        std::string str;
        for (int i = 0; i < taskVec.size(); i++)
            str += " (" + std::to_string(i+1) + ") " + taskVec.at(i).toString() + "\n";
        return str;
    }
};

TaskList taskList;
Project proj("Schedule Maker", 1.0, 4);
ConsoleLog log1;

void CreateTask() {
    std::string input;
    std::cout << "Please enter your task: ";
    getline(std::cin, input);
    Task task(input);
    taskList.AddTask(task);
}

void RemoveTask() {
    std::string input;
    taskList.toString();
    std::cout << "Enter the task to be removed: ";
    getline(std::cin, input);
    taskList.RemoveTask(std::stoi(input));
}

void ModifyTask() {
    std::string input;
    taskList.toString();
    std::cout << "Enter the task need to be modified: ";
    getline(std::cin, input);
    taskList.ModifyTask(std::stoi(input));

}

void ViewTasks() {
    taskList.toString();
}

int main() {
    std::string arrOption[] = {
            "Add a new task",
            "Remove an task",
            "Modify an task",
            "View tasks list"
    };

    std::vector<std::string> dataVec = proj.ReadFile("data.txt");
    std::vector<std::string> userVec = proj.ReadFile("user.txt");
    proj.AddOption(arrOption);
    int temp = proj.ShowOptions();

    while (temp != -1) {
        log1.Log(log1.lvwarning, "My Option: " + std::to_string(temp));

        switch (temp) {
            case 1:
                CreateTask();
                break;
            case 2:
                RemoveTask();
                break;
            case 3:
                ModifyTask();
                break;
            case 4:
                ViewTasks();
                break;
        }
        temp = proj.ShowOptions();
    }


    return 0;
}
