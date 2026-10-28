#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
 
using namespace std;
// Base class for Electronic Waste
class ElectronicWaste {
protected:
    string deviceID;
    string roomLocation;
    double weight;
 
public:
    ElectronicWaste(string id, string room, double w) 
        : deviceID(id), roomLocation(room), weight(w) {}
 
    virtual ~ElectronicWaste() {}
 
    virtual double calculateImpactScore() const = 0;
    virtual void processForRecycling() const = 0;
 
    string getID() const { return deviceID; }
    string getRoom() const { return roomLocation; }
    double getWeight() const { return weight; }
 
    void displayBaseDetails() const {
        cout << "ID: " << left << setw(10) << deviceID 
<< " | Room: " << setw(12) << roomLocation 
<< " | Weight: " << setw(5) << weight << " kg";
    }
};
 
// Subclass for Computing Devices LIKE Laptops, PCs
class ComputingDevice : public ElectronicWaste {
private:
    bool isDataWiped;
 
public:
    ComputingDevice(string id, string room, double w, bool wiped)
        : ElectronicWaste(id, room, w), isDataWiped(wiped) {}
 
    double calculateImpactScore() const override {
        return weight * 1.8;
    }
 
    void processForRecycling() const override {
        if (!isDataWiped) {
            cout << "\n   >>> ALERT: Secure data wiping required before shredding.";
        }
        cout << "\n   >>> ACTION: Circuit board shredded for precious metal recovery.\n";
    }
};
 
// Subclass for Power Units (Batteries, UPS)
class PowerUnit : public ElectronicWaste {
private:
    string chemicalType;
 
public:
    PowerUnit(string id, string room, double w, string chemical)
        : ElectronicWaste(id, room, w), chemicalType(chemical) {}
 
    double calculateImpactScore() const override {
        return weight * 3.5;
    }
 
    void processForRecycling() const override {
        cout << "\n   >>> ACTION: Safe chemical neutralization performed for " << chemicalType << ".\n";
    }
};
 
// Node structure for Singly Linked List Data Structure
struct Node {
    ElectronicWaste* data;
    Node* next;
 
    Node(ElectronicWaste* item) : data(item), next(nullptr) {}
};
 
// Dynamic Inventory Management using Singly Linked List 
class GreenChainInventory {
private:
    Node* head;
    int itemCount;
 
public:
    GreenChainInventory() : head(nullptr), itemCount(0) {}
 
    ~GreenChainInventory() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp->data;
            delete temp;
        }
    }
 
    // Insert at end (Insertion Operation)
    void insertItem(ElectronicWaste* item) {
        Node* newNode = new Node(item);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        itemCount++;
        cout << "\n[SUCCESS] E-Waste Item logged successfully!\n";
    }
 
    // Traversal and Display Operation
    void displayInventory() const {
        if (head == nullptr) {
            cout << "\n[INFO] Inventory is currently empty.\n";
            return;
        }
 
        cout << "\n==========================================================================";
        cout << "\n                  GREENCHAIN E-WASTE INVENTORY RECORDS";
        cout << "\n==========================================================================\n";
 
        Node* temp = head;
        double totalImpact = 0;
        int count = 1;
 
        while (temp != nullptr) {
            cout << count++ << ". ";
            temp->data->displayBaseDetails();
            double score = temp->data->calculateImpactScore();
            totalImpact += score;
            cout << " | Impact: " << score;
            temp->data->processForRecycling();
            cout << "--------------------------------------------------------------------------\n";
            temp = temp->next;
        }
 
        cout << "TOTAL INSTITUTIONAL SUSTAINABILITY IMPACT SCORE: " << totalImpact << "\n";
        cout << "==========================================================================\n";
    }
 
    // Linear Search Operation
    void searchItem(const string& id) const {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data->getID() == id) {
                cout << "\n[FOUND] Device Record Located:\n";
                temp->data->displayBaseDetails();
                cout << " | Impact: " << temp->data->calculateImpactScore() << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "\n[NOT FOUND] No e-waste record matching ID: " << id << "\n";
    }
 
    // Deletion Operation
    void deleteItem(const string& id) {
        if (head == nullptr) {
            cout << "\n[ERROR] Inventory is empty.\n";
            return;
        }
 
        if (head->data->getID() == id) {
            Node* temp = head;
            head = head->next;
            delete temp->data;
            delete temp;
            itemCount--;
            cout << "\n[DELETED] Device " << id << " removed from records.\n";
            return;
        }
 
        Node* current = head;
        while (current->next != nullptr && current->next->data->getID() != id) {
            current = current->next;
        }
 
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp->data;
            delete temp;
            itemCount--;
            cout << "\n[DELETED] Device " << id << " removed from inventory.\n";
        } else {
            cout << "\n[ERROR] Device ID " << id << " not found for deletion.\n";
        }
    }
};
 
// Console User Interface
int main() {
    GreenChainInventory systemInventory;
    int choice;
 
    // Pre-populating seed data for quick testing
    systemInventory.insertItem(new ComputingDevice("CMP-101", "Lab 402", 2.5, false));
    systemInventory.insertItem(new PowerUnit("CL-701", "DSAL", 15.0, "Lithium-Ion"));
    systemInventory.insertItem(new ComputingDevice("CL-105", "Faculty Room", 1.8, true));
 
    do {
        cout << "\n------------------------------------------------";
        cout << "\n         GREENCHAIN: E-WASTE MANAGEMENT SYSTEM          ";
        cout << "\n------------------------------------------------";
        cout << "\n1. Add Computing Device (Laptop/PC)";
        cout << "\n2. Add Power Unit (Battery/UPS)";
        cout << "\n3. Display All Inventory Records (Traversal)";
        cout << "\n4. Search Device by ID (Linear Search)";
        cout << "\n5. Delete Processed Waste Record";
        cout << "\n6. Exit";
        cout << "\nEnter your choice (1-6): ";
        cin >> choice;
 
        switch (choice) {
        case 1: {
            string id, room;
            double weight;
            char wipedChar;
            cout << "\nEnter Device ID: "; cin >> id;
            cout << "Enter Room Location: "; cin >> room;
            cout << "Enter Weight (kg): "; cin >> weight;
            cout << "Is Data Wiped? (y/n): "; cin >> wipedChar;
            systemInventory.insertItem(new ComputingDevice(id, room, weight, (wipedChar == 'y' || wipedChar == 'Y')));
            break;
        }
        case 2: {
            string id, room, chemical;
            double weight;
            cout << "\nEnter Device ID: "; cin >> id;
            cout << "Enter Room Location: "; cin >> room;
            cout << "Enter Weight (kg): "; cin >> weight;
            cout << "Enter Chemical Type (Lithium-Ion/Lead-Acid): "; cin >> chemical;
            systemInventory.insertItem(new PowerUnit(id, room, weight, chemical));
            break;
        }
        case 3:
            systemInventory.displayInventory();
            break;
        case 4: {
            string id;
            cout << "\nEnter Device ID to Search: "; cin >> id;
            systemInventory.searchItem(id);
            break;
        }
        case 5: {
            string id;
            cout << "\nEnter Device ID to Delete: "; cin >> id;
            systemInventory.deleteItem(id);
            break;
        }
        case 6:
            cout << "\n Exiting System \n";
            break;
        default:
            cout << "\n INVALID\n";
        }
    } while (choice != 6);
 
    return 0;
}
