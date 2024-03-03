#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_SIZE = 100;

struct Task {
    string description;
    string notes;
    bool completed;
    string editedDescription;
    int priority;
    
    Task(const string& desc, int prio) {
        description = desc;
        notes = "";
        completed = false;
        editedDescription = "";
        priority = prio;
    }
};

struct Stack {
    Task* tasks[MAX_SIZE];
    int top;

    Stack() {
        top = -1;
    }

    bool isFull() {
        return top == MAX_SIZE - 1;
    }

    bool isEmpty() {
        return top == -1;
    }

    void push(Task* newTask) {
        if (!isFull()) {
            tasks[++top] = newTask;
            cout << "Task added successfully!" << endl;
        } else {
            cout << "Stack Overflow! Cannot add more tasks." << endl;
        }
    }

    Task* pop() {
        if (!isEmpty()) {
            Task* popped = tasks[top--];
            cout << "Task deleted successfully!" << endl;
            return popped;
        } else {
            cout << "Stack Underflow! No tasks to delete." << endl;
            return NULL;
        }
    }

    Task* peek() {
        if (!isEmpty()) {
            return tasks[top];
        } else {
            cout << "Stack is empty. No task to display." << endl;
            return NULL;
        }
    }

    int size() {
        return top + 1;
    }
    
    void MarkTaskAsCompleted() {
        if (isEmpty()) {
            cout << "ToDo List is empty. Cannot mark any task completed." << endl;
        }
        Display();
        cout << "Enter task number to mark as completed: ";
        int index;
        cin >> index;
        if (index >= 1 && index <= size()) {
            Task* task = tasks[index - 1];
            task->completed = true;
            cout << "Task marked as completed!" << endl;
        } else {
            cout << "Invalid task index." << endl;
        }
    }
    
    void EditTask() {
        if (isEmpty()) {
            cout << "ToDo List is empty. Cannot edit any task." << endl;
        }
        Display();
        cout << "Enter task number to edit: ";
        int index;
        cin >> index;
        cin.ignore();
        if (index >= 1 && index <= size()) {
            Task* task = tasks[index - 1];
            cout << "Enter new task description: ";
            string newDesc;
            getline(cin, newDesc);
            task->editedDescription = task->description;
            task->description = newDesc;
            cout << "Task updated successfully!" << endl;
        } else {
            cout << "Invalid task index." << endl;
        }
    }
    
    void DeleteTask() {
        if (isEmpty()) {
            cout << "ToDo List is empty. Cannot delete any task." << endl;
        }
        Display();
        cout << "Enter task number to delete: ";
        int index;
        cin >> index;
        cin.ignore();
        if (index >= 1 && index <= size()) {
            delete tasks[index - 1];
            for (int i = index - 1; i < size() - 1; ++i) {
                tasks[i] = tasks[i + 1];
            }
            --top;
            cout << "Task deleted successfully!" << endl;
        } else {
            cout << "Invalid task index." << endl;
        }
    }
    
    void SearchTask() {
        cout << "Enter task description to search: ";
        string taskDesc;
        cin.ignore();
        getline(cin, taskDesc);
        searchTask(taskDesc);
    }
    
    void searchTask(const string& taskDesc) {
        bool found = false;
        for (int i = 0; i < size(); ++i) {
            if (tasks[i]->description.find(taskDesc) != string::npos) {
                cout << "Found task at index " << i + 1 << ": " << tasks[i]->description << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Task not found." << endl;
        }
    }

    void viewPreviousTask() {
        if (isEmpty()) {
            cout << "ToDo List is empty." << endl;
            return;
        }

        cout << "Previous Task:\n";
        Task* PreviousTask = peek();
        cout << "- " << PreviousTask->description << endl;
    }

    void viewAllTasks() {
        if (isEmpty()) {
            cout << "ToDo List is empty." << endl;
        } else {
            cout << setw(40) << left << "Task Description" << setw(15) << left << "Priority" << "Notes" << endl;
            cout << "----------------------------------------------------------" << endl;

            for (int i = 0; i < size(); ++i) {
                Task* current = tasks[i];
                cout << i + 1 << ". ";
                if (current->completed) {
                    cout << "[Done] ";
                }
                cout << setw(40) << left << current->description << setw(15) << left << current->priority << current->notes << endl;
            }
        }
    }

    void undoLastAction() {
        Task* removedTask = pop();
        if (removedTask != NULL) {
            cout << "Last action undone: Removed task - " << removedTask->description << endl;
            delete removedTask;
        }
    }

    void deleteList() {
        while (!isEmpty()) {
            delete pop();
        }
        cout << "All tasks cleared!" << endl;
    }
    
    void clearAllTasks() {
        deleteList();
    }

    void checkIfListEmpty() {
        if (isEmpty()) {
            cout << "ToDo List is empty." << endl;
        } else {
            cout << "ToDo List is not empty." << endl;
        }
    }

    void sortTasks() {
        for (int i = 0; i < size() - 1; ++i) {
            for (int j = 0; j < size() - i - 1; ++j) {
                if (tasks[j]->priority > tasks[j + 1]->priority) {
                    swap(tasks[j], tasks[j + 1]);
                }
            }
        }
        cout << "Tasks sorted by priority successfully!" << endl;
    }

    ~Stack() {
        deleteList();
    }
    
    void markHighestPriorityAsDone() {
        if (!isEmpty()) {
            int highestPriorityIndex = 0;
            int highestPriority = tasks[0]->priority;

            for (int i = 0; i <= top; ++i) {
                if (tasks[i]->priority > highestPriority) {
                    highestPriority = tasks[i]->priority;
                    highestPriorityIndex = i;
                }
            }

            tasks[highestPriorityIndex]->completed = true;
            cout << "Task with highest priority marked as done!" << endl;
        } else {
            cout << "Stack is empty. No task to mark as done." << endl;
        }
    }
    
    void Display() {
        if (isEmpty()) {
            cout << "ToDo List is empty." << endl;
        } else {
            cout << setw(40) << left << "Task Description" << "Priority" << endl;
            cout << "----------------------------------------------------------" << endl;

            for (int i = 0; i <= top; ++i) {
                cout << i + 1 << ". ";
                Task* current = tasks[i];
                cout << setw(40) << left << current->description << current->priority << endl;
            }
        }
    }
    
    void addNotes() {
        Display();
        int index;
        cout << "Enter task number to add notes: ";
        cin >> index;
        if (index >= 1 && index <= size()) {
            cout << "Enter additional notes for the task: ";
            string newNotes;
            cin.ignore();
            getline(cin, newNotes);
            tasks[index - 1]->notes = newNotes;
            cout << "Notes added successfully!" << endl;
        } else {
            cout << "Invalid task index." << endl;
        }
    }
};

void showMenu() {
    cout << "---------" << endl;
    cout << " Menu:  >" << endl;
    cout << "---------" << endl << endl;
    cout << " 1.\t Add Task            \t\t9.\t Clear All Tasks" << endl;
    cout << " 2.\t View Tasks          \t\t10.\t Check if List is Empty" << endl;
    cout << " 3.\t Mark Task as Completed \t11.\t Search Task" << endl;
    cout << " 4.\t Edit Task           \t\t12.\t Sort Task" << endl;
    cout << " 5.\t Count Tasks         \t\t13.\t Mark Task With Highest Priority as Done" << endl;
    cout << " 6.\t Delete Task         \t\t14.\t Add Notes in Task" << endl;
    cout << " 7.\t View Next Task      \t\t15.\t Exit." << endl;
    cout << " 8.\t Undo Last Action " << endl;
    cout << "Enter your choice: ";
}

// Main
int main() {
    system("color f5"); // to change color
    system("cls"); // to clear screen
     
    cout << "\n\t¦¦¦¦¦¦¦¦  ¦¦¦¦¦¦      ¦¦¦¦¦¦   ¦¦¦¦¦¦      ¦¦      ¦¦ ¦¦¦¦¦¦¦ ¦¦¦¦¦¦¦¦ " << endl;
    cout << "\t   ¦¦    ¦¦    ¦¦     ¦¦   ¦¦ ¦¦    ¦¦     ¦¦      ¦¦ ¦¦         ¦¦    " << endl;
    cout << "\t   ¦¦    ¦¦    ¦¦     ¦¦   ¦¦ ¦¦    ¦¦     ¦¦      ¦¦ ¦¦¦¦¦¦¦    ¦¦    " << endl;
    cout << "\t   ¦¦    ¦¦    ¦¦     ¦¦   ¦¦ ¦¦    ¦¦     ¦¦      ¦¦      ¦¦    ¦¦    " << endl;
    cout << "\t   ¦¦     ¦¦¦¦¦¦      ¦¦¦¦¦¦   ¦¦¦¦¦¦      ¦¦¦¦¦¦¦ ¦¦ ¦¦¦¦¦¦¦    ¦¦    " << endl;
                                                                    
    Stack todo;

    int choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1: {
                char addMore;
                do {
                    system("cls");
                    string description;
                    int priority;

                    do {
                        cout << "Enter task description: ";
                        getline(cin, description);
                        if (description.empty()) {
                            cout << "Please enter a valid task description!" << endl;
                        }
                    } while (description.empty()); // Prompt until a non-empty description is entered

                    do {
                        cout << "Enter priority (1-5, 1 being the highest): ";
                        cin >> priority;
                        if (priority < 1 || priority > 5) {
                            cout << "Invalid priority! Please enter a priority between 1 and 5." << endl;
                        }
                    } while (priority < 1 || priority > 5); // Prompt until a valid priority is entered

                    Task* newTask = new Task(description, priority);
                    todo.push(newTask);

                    cout << "Do you want to add another task? (y/n): ";
                    cin >> addMore;
                    cin.ignore();
                } while (addMore == 'y' || addMore == 'Y');

                break;
            }
           
            case 2: {
                system("cls");
                todo.viewAllTasks();
                break;
            }
            
            case 3: {
                system("cls");
                todo.MarkTaskAsCompleted();
                break;
            }
            case 4: {
                system("cls");
                todo.EditTask();
                break;
            }
            case 5: {
                system("cls");
                cout << "Total Tasks: " << todo.size() << endl;
                break;
            }
            case 6: {
                system("cls");
                todo.DeleteTask();
                break;
            }
            case 7: {
                system("cls");
                todo.viewPreviousTask();
                break;
            }
            
            case 8: {
                system("cls");
                todo.undoLastAction();
                break;
            }
            case 9: {
                system("cls");
                todo.clearAllTasks();
                break;
            }
            case 10: {
                system("cls");
                todo.checkIfListEmpty();
                break;
            }
            case 11: {
                system("cls");
                todo.SearchTask();
                break;
            }
            
            case 12: {
                system("cls");
                todo.sortTasks();
                break;
            }
            case 13: {
                system("cls");
                todo.markHighestPriorityAsDone();
                break;
            }
            case 14: {
                system("cls");
                todo.addNotes();
                break;
            }
            case 15: {
                system("cls");
                cout << "Exiting program..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice! Please enter a valid option." << endl;
                break;
            }
        }
        
        cout << "Press Enter to continue...";
        cin.get();
        system("cls");
    } while (choice != 15);

    return 0;
}

