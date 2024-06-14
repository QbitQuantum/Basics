#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
#include <type_traits>
#include <variant>
#include <stdarg.h>

using UserID = int;
using UserName = std::string;
using UserPass = int;

class Box {
private:
    std::string message = "";
    enum TypeBoolIndex
    {
        False = 0, // Закрыто
        True = 1 // Открыто
    };
    bool BoolTypeBox = bool(TypeBoolIndex::True);
    std::map <UserID, std::pair<UserName, UserPass>> ActiveUsersKey;
    std::vector <int> Vec;
    int ReturnTrueBoolTypeBox() {
        return TypeBoolIndex::True;
    }
    int ReturnFalseBoolTypeBox() {
        return TypeBoolIndex::False;
    }
    void checkBoolTypeBox() {
        if (ActiveUsersKey.empty()) {
            this->BoolTypeBox = bool(ReturnTrueBoolTypeBox());
        }
        else
        {
            this->BoolTypeBox = bool(ReturnFalseBoolTypeBox());
        }
    }
    bool SearchUserNameAndUserPass(UserName userName, UserPass userPass) {
        for (const auto& user : ActiveUsersKey) {
            if (user.second.first == userName && user.second.second == userPass) {
                return true;
            }
        }
        return false;
    }
public:
    void messages(std::string message, ...) {
        va_list ap;
        va_start(ap, message);
        for (int i = 0; i < this->Vec.size(); i++) {
            int value = va_arg(ap, int);
            this->Vec.push_back(value);
        }
        va_end(ap);
    }
    void Encoding(UserID UserID, UserName UserName, UserPass UserPass) {
        ActiveUsersKey[UserID] = std::make_pair(UserName, UserPass);
        std::cout << "Box Encoding Users: " << UserName << std::endl; // Add in log
        checkBoolTypeBox();
    }
    void Decoding(UserName UserName, UserPass UserPass) {
        std::string UsersName = UserName;
        int UsersPass = UserPass;
        if (ActiveUsersKey.empty()) {
            std::cout << "Box not encoding."; // Add in log
            checkBoolTypeBox();
        }
        if (!ActiveUsersKey.empty()) {
            if (!SearchUserNameAndUserPass(UsersName, UsersPass))
            {
                std::cout << "Erorr Decoding. User: " << UsersName << std::endl; // Add in log
                checkBoolTypeBox();
            }
            else
            {
                for (auto it = ActiveUsersKey.begin(); it != ActiveUsersKey.end();) {
                    if (it->second.first == UsersName && it->second.second == UsersPass) {
                        it = ActiveUsersKey.erase(it);
                        std::cout << "Box Decoding Users: " << UsersName << std::endl; // Add in log
                    }
                    else {
                        ++it;
                    }
                }
            }
            checkBoolTypeBox();
        }
    }
    void Open() {
        if (this->BoolTypeBox) {
            std::cout << "Secret Key = " << this->message << std::endl;
        }
        else
        {
            std::cout << "Error Open Box. Box Decoding" << std::endl;
            /*
            std::cout << "Box Decoding Users:" << std::endl;
            for (const auto& user : ActiveUsersKey) {
                std::cout << "UserID: " << user.first
                    << ", UserName: " << user.second.first
                    ;
                    //<< ", UserPass: " << user.second.second << std::endl;
                std::cout << std::endl;
            }
            */
        }
    }
};

class Alice {
public:
    std::string message;
    Alice() {};
    Alice(std::string message) : message(message) {};
    void print() {
        std::cout << this->message << std::endl;
    }
};

class Bob {
public:
    std::string message;
    Bob() {};
    Bob(std::string message) : message(message) {};
    void print() {
        std::cout << this->message << std::endl;
    }
};

int main() {

    Alice alice("");
    alice.print();
    // Создаём бокс для хранения сообщения
    Box box;
    // Алиса региструется на сайте xxx.com и получает ID=1
    // Боб региструется на сайте xxx.com и получает ID=2
    //Алиса создаёт сообщение
    box.messages("int");
    //Алиса шифрует бокс
    box.Encoding(1, "Alice", 123);
    // Ева перехватывает бокс
    // Ева шифрует бокс под своим именем
    box.Encoding(3, "Eva", 123);
    //-------------> Отправляем Бобу
    // Боб шифрует бокс
    box.Encoding(2, "Bob", 123);
    //------------->Отправляем Алисе
    //Алиса снимает свой ключ
    box.Decoding("Alice", 123);
    //-------------> Отправляем Бобу
    //Боб снимает свой ключ
    box.Decoding("Bob", 123);
    //Открывем бокс
    box.Open();
}
