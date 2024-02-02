#include <iostream>
#include <string> 

struct ActionAndButton {
    std::string act;
    std::string button;
};

class Keyboard {
public:
    Keyboard() {

    }
    ActionAndButton actionAndButton[100];
    int t = 0;

    void NewAct() {
        std::cout << "Enter the name of the button" << std::endl;
        std::string newButton;
        std::cin >> newButton;
        for (int i = 0; i < t; i++) {
            if (newButton == actionAndButton[i].button) {
                std::cout << "This button already exists. Please choose another one." << std::endl;
                return; 
            }
        }
        actionAndButton[t].button = newButton;
        std::cout << "Enter action" << std::endl;
        std::cin.ignore();
        std::getline(std::cin, actionAndButton[t].act);
        t++;
    }

    void PressButton(std::string s) {
        bool tmp = false;
        for (int i = 0; i < t; i++) {
            if (s == actionAndButton[i].button) {
                std::cout << "Action for button " << s << ": " << actionAndButton[i].act << std::endl;
                tmp = true;
                i = t;
            }
        }
        if (!tmp) {
            std::cout << "This button has no action. Do you want to add it" << std::endl;
            std::cout << "0. No" << std::endl;
            std::cout << "1. Yes" << std::endl;
            int i;
            std::cin >> i;
            if (i == 1) {
                this->NewAct();
            }
        }
    }

    void Help() {
        for (int i = 0; i < t; i++) {
            std::cout << actionAndButton[i].button + " " + actionAndButton[i].act << std::endl;
        }
    }

    void ShowAssignments() {
        std::cout << "List of reassignments:" << std::endl;
        for (int i = 0; i < t; i++) {
            std::cout << "Button: " << actionAndButton[i].button << std::endl;
            std::cout << "Action: " << actionAndButton[i].act << std::endl;
            std::cout << std::endl;
        }
    }
};

class Workflow {
public:
    Workflow() {

    }

    void Undo(Keyboard& m_key) {
        std::cout << "Undo" << std::endl;
        if (nnumberOfActions == 0) {
            m_key.t--;
        }
        for (int i = 0; i < m_key.t; i++) {
            if ((Action[nnumberOfActions - 1].act == m_key.actionAndButton[i].act) && (Action[nnumberOfActions - 1].button == m_key.actionAndButton[i].button)) {
                nnumberOfActions--;
                m_key.t--;
                i = m_key.t;
            }
            else if ((Action[nnumberOfActions - 1].act != m_key.actionAndButton[i].act) && (Action[nnumberOfActions - 1].button == m_key.actionAndButton[i].button)) {
                m_key.actionAndButton[i].act = Action[nnumberOfActions - 1].act;
                nnumberOfActions--;
                i = m_key.t;
            }
        }
    }

    bool Reassignment(std::string s, Keyboard& m_key) {
        std::cout << "Assign another action to this button" << std::endl;
        bool tmp = false;
        for (int i = 0; i < m_key.t; i++) {
            if (s == m_key.actionAndButton[i].button) {
                Action[nnumberOfActions] = m_key.actionAndButton[i];
                nnumberOfActions++;
                std::cin.ignore();
                std::getline(std::cin, m_key.actionAndButton[i].act); 
                tmp = true;
                i = m_key.t;
            }
        }
        if (!tmp) {
            std::cout << "This button has no action. Do you want to add it or cancel the previous action?" << std::endl;
            std::cout << "A. Add" << std::endl;
            std::cout << "C. Cancel" << std::endl;
            char choice;
            std::cin >> choice;
            if (choice == 'A') {
                m_key.NewAct();
                return true;
            }
            else if (choice == 'C') {
                return false;
            }
        }
        return true;
    }

   
private:
    ActionAndButton Action[200];
    int nnumberOfActions = 0;
};

int main()
{
    Keyboard Key;
    Workflow work;

    int choice = 1;

    while (choice != 0) {
        std::cout << "Continue?" << std::endl;
        std::cout << "0 - Exit" << std::endl;
        std::cout << "1 - Add" << std::endl;
        std::cout << "2 - Reassignment" << std::endl;
        std::cout << "3 - Undo" << std::endl;
        std::cout << "4 - Show Assignments" << std::endl;
        std::cout << "Choose action: ";
        std::cin >> choice;

        if (choice == 1) {
            Key.NewAct();
        }
        else if (choice == 2) {
            std::cout << "Enter button to reassignment: ";
            std::string button;
            std::cin >> button;
            bool success = work.Reassignment(button, Key);
            if (success) {
                std::cout << "Successful!" << std::endl;
            }
            else {
                std::cout << "Canceled!" << std::endl;
            }
        }
        else if (choice == 3) {
            work.Undo(Key);
            std::cout << "Undo!" << std::endl;
        }
        else if (choice == 4) {
            Key.ShowAssignments();
        }
        return 0;
    }
}
