#include <iostream>
#include <string>
#include <vector>
#include <locale.h>

class Control {
public:
    virtual void setPosition(int x, int y) = 0;
    virtual std::pair<int, int> getPosition() = 0;
    virtual ~Control() {}
};

class Form : public Control {
public:
    void addControl(Control* control) {
        std::cout << "Add control" << std::endl;
    }

    void setPosition(int x, int y) override {
        std::cout << "setPosition was called" << std::endl;
    }

    std::pair<int, int> getPosition() override {
        std::cout << "getPosition was called" << std::endl;
        return { 0, 0 };
    }
};

class Label : public Control {
public:
    void setText(const std::string& text) {
        std::cout << "Label text set: " << text << std::endl;
    }

    std::string getText() {
        std::cout << "Label getText was called" << std::endl;
        return "Text";
    }

    void setPosition(int x, int y) override {
        std::cout << "Label setPosition was called" << std::endl;
    }

    std::pair<int, int> getPosition() override {
        std::cout << "Label getPosition was called" << std::endl;
        return { 0, 0 };
    }
};

class ComboBox : public Control {
public:
    void setItems(const std::vector<std::string>& items) {
        std::cout << "ComboBox items set: " << std::endl;
    }

    void setSelectedIndex(int index) {
        std::cout << "Selected index in ComboBox set: " << index << std::endl;
    }

    int getSelectedIndex() {
        std::cout << "ComboBox returns the selected index" << std::endl;
        return 0;
    }

    std::vector<std::string> getItems() {
        std::cout << "ComboBox get items was called" << std::endl;
        return { "Item 1", "Item 2" };
    }

    void setPosition(int x, int y) override {
        std::cout << "ComboBox setPosition was called" << std::endl;
    }

    std::pair<int, int> getPosition() override {
        std::cout << "ComboBox getPosition was called" << std::endl;
        return { 0, 0 };
    }
};

class TextBox : public Control {
public:
    void setText(const std::string& text) {
        std::cout << "TextBox text set: " << text << std::endl;
    }

    std::string getText() {
        std::cout << "TextBox getText was called" << std::endl;
        return "Text";
    }

    void OnValueChanged() {
        std::cout << "Value of TextBox has changed" << std::endl;
    }

    void setPosition(int x, int y) override {
        std::cout << "TextBox setPosition was called" << std::endl;
    }

    std::pair<int, int> getPosition() override {
        std::cout << "TextBox getPosition was called" << std::endl;
        return { 0, 0 };
    }
};

class Button : public Control {
public:
    void setText(const std::string& text) {
        std::cout << "Button text set: " << text << std::endl;
    }

    std::string getText() {
        std::cout << "Button getText was called" << std::endl;
        return "Text";
    }

    void Click() {
        std::cout << "Button was clicked" << std::endl;
    }

    void setPosition(int x, int y) override {
        std::cout << "Button setPosition was called" << std::endl;
    }

    std::pair<int, int> getPosition() override {
        std::cout << "Button getPosition was called" << std::endl;
        return { 0, 0 };
    }
};

class AbstractFactory {
public:
    virtual Form* createForm() = 0;
    virtual Label* createLabel() = 0;
    virtual TextBox* createTextBox() = 0;
    virtual ComboBox* createComboBox() = 0;
    virtual Button* createButton() = 0;
    virtual ~AbstractFactory() {}
};

class WindowsFactory : public AbstractFactory {
public:
    Form* createForm() override {
        return new Form();
    }

    Label* createLabel() override {
        return new Label();
    }

    TextBox* createTextBox() override {
        return new TextBox();
    }

    ComboBox* createComboBox() override {
        return new ComboBox();
    }

    Button* createButton() override {
        return new Button();
    }
};

class LinuxFactory : public AbstractFactory {
public:
    Form* createForm() override {
        return new Form();
    }

    Label* createLabel() override {
        return new Label();
    }

    TextBox* createTextBox() override {
        return new TextBox();
    }

    ComboBox* createComboBox() override {
        return new ComboBox();
    }

    Button* createButton() override {
        return new Button();
    }
};

class MacOSFactory : public AbstractFactory {
public:
    Form* createForm() override {
        return new Form();
    }

    Label* createLabel() override {
        return new Label();
    }

    TextBox* createTextBox() override {
        return new TextBox();
    }

    ComboBox* createComboBox() override {
        return new ComboBox();
    }

    Button* createButton() override {
        return new Button();
    }
};

class Client {
public:
    void run(AbstractFactory* factory) {
        Form* form = factory->createForm();
        Label* label = factory->createLabel();
        TextBox* textBox = factory->createTextBox();
        ComboBox* comboBox = factory->createComboBox();
        Button* button = factory->createButton();

        form->addControl(label);
        form->addControl(textBox);
        form->addControl(comboBox);
        form->addControl(button);

        label->setText("Hello, world!");
        label->setPosition(10, 10);

        textBox->setText("Text");
        textBox->setPosition(20, 20);

        comboBox->setItems({ "Item 1", "Item 2" });
        comboBox->setPosition(30, 30);

        button->setText("Click me!");
        button->setPosition(40, 40);

        delete form;
        delete label;
        delete textBox;
        delete comboBox;
        delete button;
    }
};

int main() {
#ifdef _WIN32
    WindowsFactory factory;
#elif __linux__
    LinuxFactory factory;
#elif __APPLE__
    MacOSFactory factory;
#endif

    Client client;
    client.run(&factory);

    return 0;
}
