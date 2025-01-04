#include <iostream>
using namespace std;

struct Node {
    int energy;
    Node* next;
};

void trackEnergyUsingArray(int energy[], int days) {
    int totalEnergy = 0;

    cout << "\nEnergy Generation Tracking (Array):\n";
    for (int i = 0; i < days; ++i) {
        cout << "Day " << i + 1 << ": " << energy[i] << " kWh\n";
        totalEnergy += energy[i];
    }

    cout << "Total Energy Generated: " << totalEnergy << " kWh\n";
    cout << "Average Daily Energy: " << static_cast<double>(totalEnergy) / days << " kWh\n";
}

void trackEnergyUsingLinkedList(Node* head) {
    int totalEnergy = 0, days = 0;
    Node* current = head;

    cout << "\nEnergy Generation Tracking (Linked List):\n";
    while (current != NULL) {
        ++days;
        cout << "Day " << days << ": " << current->energy << " kWh\n";
        totalEnergy += current->energy;
        current = current->next;
    }

    cout << "Total Energy Generated: " << totalEnergy << " kWh\n";
    cout << "Average Daily Energy: " << static_cast<double>(totalEnergy) / days << " kWh\n";
}

int main() {
    int days;

    cout << "Enter the number of days to track energy generation: ";
    cin >> days;

    int energyArray[days];
    cout << "\nEnter energy generation (in kWh) for each day using an array:\n";
    for (int i = 0; i < days; ++i) {
        cout << "Day " << i + 1 << ": ";
        cin >> energyArray[i];
    }

    Node* head = NULL;
    Node* tail = NULL;
    cout << "\nEnter energy generation (in kWh) for each day using a linked list:\n";
    for (int i = 0; i < days; ++i) {
        int energy;
        cout << "Day " << i + 1 << ": ";
        cin >> energy;

        Node* newNode = new Node{energy, NULL};
        if (head == NULL) {
            head = newNode; // First node
            tail = newNode;
        } else {
            tail->next = newNode; // Add to the end
            tail = newNode;
        }
    }

    trackEnergyUsingArray(energyArray, days);
    trackEnergyUsingLinkedList(head);

    // Free memory for linked list
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
