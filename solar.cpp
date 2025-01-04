#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main() {
    queue<string> irrigationQueue; // Queue to manage irrigation tasks
    int numTasks;

    // Taking input for the number of tasks
    cout << "Enter the number of irrigation tasks: ";
    cin >> numTasks;
    cin.ignore(); // To ignore the newline character after entering the number

    // Adding tasks to the irrigation queue
    for (int i = 0; i < numTasks; ++i) {
        string task;
        cout << "Enter task " << i + 1 << ": ";
        getline(cin, task); // Taking task input
        irrigationQueue.push(task);
    }

    // Processing and displaying the tasks
    cout << "\nIrrigation Queue Processing:\n";
    while (!irrigationQueue.empty()) {
        cout << irrigationQueue.front() << endl; // Access and display the task at the front
        irrigationQueue.pop();                  // Remove the processed task
    }

    return 0; // Indicating successful execution
}

