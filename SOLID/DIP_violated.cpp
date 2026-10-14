#include<iostream>
#include<vector>
#include<string>
#include<stdexcept>

using namespace std;

class MySQLDatabase { // Low level module
    public:
        void saveToSQL(string data){
            cout << "Saving data to MySQL: " << data << endl;
        }
};

class MongoDBDatabase { // Low level module
    public:
        void saveToMongo(string data){
            cout << "Saving data to MongoDB: " << data << endl;
        }
};

class UserService { // High level module
    private:
        MySQLDatabase* mySQLDatabase; // Direct dependency on LLM MySQLDatabase
        MongoDBDatabase* mongoDBDatabase; // Direct dependency on LLM MongoDBDatabase
    public:
        void storeUserToSQL(string user) {
            mySQLDatabase->saveToSQL(user);
        }

        void storeUserToMongo(string user) {
            mongoDBDatabase->saveToMongo(user);
        }
};

int main() {
    UserService userService;
    userService.storeUserToSQL("Aditya");
    userService.storeUserToMongo("Raj");
}