#include <iostream>
#include <string>

struct ActionAndButton {
    std::string act;
    std::string button;
};

class Keyboard {
public:
    Keyboard() {
        n = 0;
    }

    void NewAct() {
        std::cout << "Enter the name of the button:" << std::endl;
        std::string newButton;
        std::cin >> newButton;

        for (int i = 0; i < n; i++) {
            if (newButton == actionAndButton[i].button) {
                std::cout << "This button already exists. Please choose another one." << std::endl;
                return;
            }
        }

        actionAndButton[n].button = newButton;

        std::cout << "Enter the action:" << std::endl;
        std::string newAction;
        std::cin.ignore();
        std::getline(std::cin, newAction);

        actionAndButton[n].act = newAction;

        n++;
    }

    void PressButton(const std::string& button) {
        std::string action;
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (button == actionAndButton[i].button) {
                action = actionAndButton[i].act;
                found = true;
                break;
            }
        }

        if (found) {
            std::cout << "Action for button " << button << ": " << action << std::endl;
        }
        else {
            std::cout << "This button has no action. Do you want to add it?" << std::endl;
            std::cout << "0. No" << std::endl;
            std::cout << "1. Yes" << std::endl;

            int choice;
            std::cin >> choice;

            if (choice == 1) {
                NewAct();
            }
        }
    }

    void ShowAssignments() {
        std::cout << "List of assignments:" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "Button: " << actionAndButton[i].button << std::endl;
            std::cout << "Action: " << actionAndButton[i].act << std::endl;
            std::cout << std::endl;
        }
    }

    ActionAndButton* GetActionAndButton() {
        return actionAndButton;
    }

    int GetN() {
        return n;
    }
    void DecreaseN() {
        n--;
    }
private:
    ActionAndButton actionAndButton[100];
    int n;
};

class Workflow {
public:
    Workflow() {
        numberOfActions = 0;
    }

    void ReassignAction(const std::string& button, int n, ActionAndButton* actionAndButton) {
        std::cout << "Assign another action to button " << button << ":" << std::endl;
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (button == actionAndButton[i].button) {
                actions[numberOfActions] = actionAndButton[i];
                numberOfActions++;

                std::string newAction;
                std::cin.ignore();
                std::getline(std::cin, newAction);

                actionAndButton[i].act = newAction;
                found = true;
                break;
            }
        }
    }
    void Undo(Keyboard& keyboard, ActionAndButton* actionAndButton) {
        std::cout << "Undo" << std::endl;
        if (numberOfActions == 0) {
            keyboard.DecreaseN();
        }
        for (int i = 0; i < keyboard.GetN(); i++) {
            if ((actions[numberOfActions - 1].act == keyboard.GetActionAndButton()[i].act) && (actions[numberOfActions - 1].button == keyboard.GetActionAndButton()[i].button)) {
                numberOfActions--;
                keyboard.DecreaseN();
                i = keyboard.GetN();
            }
            else if ((actions[numberOfActions - 1].act != keyboard.GetActionAndButton()[i].act) && (actions[numberOfActions - 1].button == keyboard.GetActionAndButton()[i].button)) {
                keyboard.GetActionAndButton()[i].act = actions[numberOfActions - 1].act;
                numberOfActions--;
                i = keyboard.GetN();
            }
        }
    }
private:
    ActionAndButton actions[100];
    int numberOfActions;
};

int main() {
    Keyboard keyboard;
    Workflow workflow;

    char option;
    std::string button;

    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. New Action" << std::endl;
        std::cout << "2. Assign Action" << std::endl;
        std::cout << "3. Press Button" << std::endl;
        std::cout << "4. Show Assignments" << std::endl;
        std::cout << "5. Undo" << std::endl;
        std::cout << "0. Exit" << std::endl;

        std::cin >> option;

        switch (option) {
        case '1':
            keyboard.NewAct();
            break;
        case '2':
            std::cout << "Enter the button you want to assign an action to:" << std::endl;
            std::cin >> button;
            workflow.ReassignAction(button, keyboard.GetN(), keyboard.GetActionAndButton());
            break;
        case '3':
            std::cout << "Enter the button you want to press:" << std::endl;
            std::cin >> button;
            keyboard.PressButton(button);
            break;
        case '4':
            keyboard.ShowAssignments();
            break;
        case '5':
            workflow.Undo(keyboard, keyboard.GetActionAndButton());
            break;
        }
    } while (option != '0');

    return 0;
}
