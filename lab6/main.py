class Control:
    def setPosition(self, x, y):
        print(f"Установка позиции по ({x}, {y})")

    def getPosition(self):
        print("Получение позиции")

class ControlFactory:
    def createForm(self):
        pass

    def createLabel(self):
        pass

    def createTextBox(self):
        pass

    def createComboBox(self):
        pass

    def createButton(self):
        pass

class WindowsControlFactory(ControlFactory):
    def createForm(self):
        return WindowsForm()

    def createLabel(self):
        return WindowsLabel()

    def createTextBox(self):
        return WindowsTextBox()

    def createComboBox(self):
        return WindowsComboBox()

    def createButton(self):
        return WindowsButton()

class WindowsForm(Control):
    def addControl(self, control):
        print(f"Добавление контролла Control в форму Windows")

class WindowsLabel(Control):
    def setText(self, text):
        print(f"Установка текста '{text}' для метки Windows")

    def getText(self):
        print("Получение текста из метки Windows")

class WindowsTextBox(Control):
    def setText(self, text):
        print(f"Установка текста '{text}' для текстового поля Windows")

    def getText(self):
        print("Получение текста из текстового поля Windows")

    def onValueChanged(self):
        print("Событие OnValueChanged для текстового поля Windows")

class WindowsComboBox(Control):
    def setSelectedIndex(self, index):
        print(f"Установка выбранного индекса {index} для комбинированного поля Windows")

    def getSelectedIndex(self):
        print("Получение выбранного индекса из комбинированного поля Windows")

    def setItems(self, items):
        print(f"Установка элементов {items} для комбинированного поля Windows")

    def getItems(self):
        print("Получение элементов из комбинированного поля Windows")

class WindowsButton(Control):
    def setText(self, text):
        print(f"Установка текста '{text}' для кнопки Windows")

    def getText(self):
        print("Получение текста из кнопки Windows")

    def click(self):
        print("Событие клика для кнопки Windows")

windowsFactory = WindowsControlFactory()
windowsForm = windowsFactory.createForm()
windowsLabel = windowsFactory.createLabel()
windowsTextBox = windowsFactory.createTextBox()
windowsComboBox = windowsFactory.createComboBox()
windowsButton = windowsFactory.createButton()

windowsForm.setPosition(10, 10)
windowsForm.addControl(windowsLabel)
windowsLabel.setText("Пример текста")
windowsLabel.getText()
windowsTextBox.setPosition(20, 20)
windowsTextBox.setText("Введенный текст")
windowsTextBox.getText()
windowsTextBox.onValueChanged()
windowsComboBox.setPosition(30, 30)
windowsComboBox.setSelectedIndex(0)
windowsComboBox.getSelectedIndex()
windowsComboBox.setItems(["Элемент 1", "Элемент 2"])
windowsComboBox.getItems()
windowsButton.setPosition(40, 40)
windowsButton.setText("Нажми меня")
windowsButton.getText()
windowsButton.click()
