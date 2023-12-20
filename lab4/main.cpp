#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread>

struct KeyAction {
    std::string actionName;
};

class VirtualKeyboard {
private:
    std::unordered_map<char, KeyAction> keyActions;
    std::vector<char> keyHistory;

public:
    void remapKey(char key, std::string actionName) {
        keyActions[key] = { actionName };
    }

    void pressKey(char key) {
        if (keyActions.count(key) > 0) {
            KeyAction action = keyActions[key];
            std::cout << "Action is performed: " << action.actionName << std::endl;
        }
        keyHistory.push_back(key);
    }

    void undoLastAction() {
        if (!keyHistory.empty()) {
            char lastKey = keyHistory.back();
            keyHistory.pop_back();
            std::cout << "Undo the last action for the key: " << lastKey << std::endl;
        }
    }
};
int main() {
    VirtualKeyboard keyboard;

    keyboard.remapKey('A', "Action 1");
    keyboard.remapKey('B', "Action 2");

    keyboard.pressKey('A');
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    keyboard.pressKey('B');
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    keyboard.undoLastAction();

    keyboard.remapKey('A', "Action 3");
    keyboard.pressKey('A');

    return 0;
}