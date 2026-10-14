#include<iostream>
#include<vector>
#include<string>
#include<stdexcept>

using namespace std;

// Abstraction (High-level module depends on this interface, not on concrete implementations)
class Database {
    public:
        virtual void save(string data) = 0; // Pure virtual function making this an interface
};

// MySQL implementation (Low-level module)
class MySQLDatabase : public Database {
    public:
        void save(string data) override {
            cout << "Saving data to MySQL: " << data << endl;
        }
};

// MongoDB implementation (Low-level module)
class MongoDBDatabase : public Database {
    public:
        void save(string data) override {
            cout << "Saving data to MongoDB: " << data << endl;
        }
};

// UserService (High-level module)
class UserService {
    private:
        Database* db; // Dependency Injection
    public:
        UserService(Database* database) {
            db = database;
        }

        void storeUser(string user) {
            db->save(user);
        }
};

int main() {
    MySQLDatabase* mySQLDatabase = new MySQLDatabase();
    MongoDBDatabase* mongoDBDatabase = new MongoDBDatabase();

    UserService* userServiceSQL = new UserService(mySQLDatabase);
    userServiceSQL->storeUser("Aditya");

    UserService* userServiceMongo = new UserService(mongoDBDatabase);
    userServiceMongo->storeUser("Raj");
}