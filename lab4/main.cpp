#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class VirtualKeyboard
{
protected:
    std::unordered_map<std::string, std::string> actions;

public:
    void setAction(const std::string& key, const std::string& virtualKey)
    {
        actions[key] = virtualKey;
    }

    std::string getVirtualKey(const std::string& key)
    {
        if (actions.find(key) == actions.end()) {
            return "";
        }
        return actions[key];
    }

    void undoAction()
    {
        if (!actions.empty()) {
            actions.erase(actions.end());   
        }
    }

};

class Command
{
private:
    std::string key;
    std::string virtualKey;

public:
    Command(const std::string& key, const std::string& virtualKey)
        : key(key), virtualKey(virtualKey)
    {
    }

    std::string getKey() const
    {
        return key;
    }

    std::string getVirtualKey() const
    {
        return virtualKey;
    }
};

int main()
{
    Command copy("c", "ctrl+c");
    Command paste("p", "ctrl+v");

    std::cout << "List of commands: \n";
    std::cout << "Reassign keys - settings\n";
    std::cout << "Continue usage - continue \n";
    std::cout << "Undo previous action - undo \n";
    std::cout << "Exit - exit\n\n";

    VirtualKeyboard virtualKeyboard;
    virtualKeyboard.setAction(copy.getKey(), copy.getVirtualKey());
    virtualKeyboard.setAction(paste.getKey(), paste.getVirtualKey());

    std::string key;

    while (true) {
        std::cout << "Enter a key or combination: \n";
        std::getline(std::cin, key);

        if (key == "continue") {
            break;
        }
        if (key == "exit") {
            return 0;
        }
        if (key == "undo") {
            virtualKeyboard.undoAction();
        }
        else {
            std::cout << "Enter a new key or combination: ";
            std::string virtualKey;
            std::getline(std::cin, virtualKey);

            if (key.find('+') != std::string::npos && virtualKey.find('+') != std::string::npos) {
                Command command(key, virtualKey);
            }
            else {
                virtualKeyboard.setAction(key, virtualKey);
            }
        }
    }

    const std::vector<std::string> VIRTUAL_KEYBOARD = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "=", "tab", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
        "shift", "a", "s", "d", "f", "g", "h", "j", "k", "l", "enter", "space", "ctrl", "z", "x", "c", "v", "b", "n", "m", "ctrl", "backspace"
    };

    for (const std::string& key : VIRTUAL_KEYBOARD) {
        if (virtualKeyboard.getVirtualKey(key).empty()) {
            virtualKeyboard.setAction(key, key);
        }
    }

    std::string str = "";
    std::string copiedString = "";
    std::vector<std::string> actions;

    std::cout << "\nPress a key: \n";
    while (true) {
        std::cout << "Enter a key or combination: ";
        std::getline(std::cin, key);

        if (key == "continue") {
            break;
        }
        if (key == "exit") {
            return 0;
        }
        if (key == "undo") {
            str = str.substr(0, str.size() - 1);
        }
        else if (key == "undo settings") {
            virtualKeyboard.setAction(actions.back(), actions.back());
            actions.pop_back();
        }
        else if (key == "settings") {
            std::cout << "Reassign keys mode enabled: \n";
            std::cout << "Enter a key or combination: ";
            std::string reassignKey;
            std::getline(std::cin, reassignKey);
            actions.push_back(reassignKey);
            std::cout << "Enter a new key or combination: ";
            std::string virtualKey;
            std::getline(std::cin, virtualKey);
            virtualKeyboard.setAction(reassignKey, virtualKey);
            std::getline(std::cin, key);
            if (key == "continue") {
                continue;
            }
            if (key == "exit") {
                return 0;
            }
            if (key == "undo") {
                virtualKeyboard.undoAction();
                virtualKeyboard.setAction(reassignKey, reassignKey);
            }
        }
        else {
            std::string virtualKey = virtualKeyboard.getVirtualKey(key);
            if (virtualKey.find('+') == std::string::npos) {
                str += virtualKey;
            }
            else if (virtualKey == "ctrl+c") {
                copiedString = str;
            }
            else {
                str += copiedString;
            }
        }
        std::cout << str << "\n";
    }

    return 0;
}
