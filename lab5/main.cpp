#include <iostream>
#include <vector>
#include <fstream>

class User {
public:
    int id;
    std::string login;
    std::string password;
    std::string name;
};

template<typename T>
class IRepository {
public:
    virtual std::vector<T> GetAll() = 0;
    virtual void Add(T user) = 0;
    virtual void Remove(T user) = 0;
    virtual void Update(T user) = 0;
};

class UserRepository : public IRepository<User> {
public:
    std::vector<User> GetAll() override {
        std::vector<User> users;
        std::ifstream file("users.txt");
        if (file.is_open()) {
            User user;
            while (file >> user.id >> user.login >> user.password >> user.name) {
                users.push_back(user);
            }
            file.close();
        }
        return users;
    }

    void Add(User user) override {
        std::ofstream file("users.txt", std::ios::app);
        if (file.is_open()) {
            file << user.id << " " << user.login << " " << user.password << " " << user.name << std::endl;
            file.close();
        }
    }

    void Remove(User user) override {
        std::vector<User> users = GetAll();
        users.erase(std::remove_if(users.begin(), users.end(), [&](const User& u) {
            return u.id == user.id;
            }), users.end());

        std::ofstream file("users.txt");
        if (file.is_open()) {
            for (const User& u : users) {
                file << u.id << " " << u.login << " " << u.password << " " << u.name << std::endl;
            }
            file.close();
        }
    }

    void Update(User user) override {
        std::vector<User> users = GetAll();
        for (User& u : users) {
            if (u.id == user.id) {
                u = user;
                break;
            }
        }

        std::ofstream file("users.txt");
        if (file.is_open()) {
            for (const User& u : users) {
                file << u.id << " " << u.login << " " << u.password << " " << u.name << std::endl;
            }
            file.close();
        }
    }

    User GetById(int id) {
        std::vector<User> users = GetAll();
        for (const User& user : users) {
            if (user.id == id) {
                return user;
            }
        }
        User user; 
        return user;
    }

    User GetByLogin(std::string login) {
        std::vector<User> users = GetAll();
        for (const User& user : users) {
            if (user.login == login) {
                return user;
            }
        }
        User user; 
        return user;
    }
};

class IUserManager {
public:
    virtual void SignIn(User user) = 0;
    virtual void SignOut(User user) = 0;
    virtual bool isAuthorized() = 0;
};

class UserManager : public IUserManager {
private:
    UserRepository userRepository;
    User currentUser;

public:
    void SignIn(User user) override {
        if (user.login.empty()) {
            User lastLoggedInUser = userRepository.GetByLogin(currentUser.login);
            if (!lastLoggedInUser.login.empty()) {
                currentUser = lastLoggedInUser;
                std::cout << "User " << currentUser.name << " logged in." << std::endl;
                return;
            }
        }
        User foundUser = userRepository.GetByLogin(user.login);
        if (foundUser.login == user.login && foundUser.password == user.password) {
            currentUser = foundUser;
            std::cout << "User " << currentUser.name << " logged in." << std::endl;
        }
        else {
            std::cout << "Error. Incorrect username or password." << std::endl;
        }
    }

    void SignOut(User user) override {
        currentUser = User();
        std::cout << "User logged out." << std::endl;
    }

    bool isAuthorized() override {
        return !currentUser.login.empty();
    }
};

int main() {
    UserRepository userRepository;
    UserManager userManager;

    User user1;
    user1.id = 1;
    user1.login = "user1";
    user1.password = "password1";
    user1.name = "User 1";

    userRepository.Add(user1);

    userManager.SignIn(user1);
    userManager.SignOut(user1);

    return 0;
}