#include<iostream>
#include<string>
using namespace std;

// Strategy Interface for Walk
class WalkableRobot {
public:
    virtual void walk() = 0;
    virtual ~WalkableRobot() {}
};

// Concrete implementation of WalkableRobot
class NormalWalk: public WalkableRobot {
public:
    void walk() override {
        cout << "Walking normally." << endl;
    }
};

class NoWalk: public WalkableRobot {
public:
    void walk() override {
        cout << "Cannot walk." << endl;
    }
};

// Strategy Interface for Talk
class TalkableRobot {
public:
    virtual void talk() = 0;
    virtual ~TalkableRobot() {}
};

// Concrete implementation of TalkableRobot
class NormalTalk: public TalkableRobot {
public:
    void talk() override {
        cout << "Talking normally." << endl;
    }
};

class NoTalk: public TalkableRobot {
public:
    void talk() override {
        cout << "Cannot talk." << endl;
    }
};


// Strategy Interface for Fly
class FlyableRobot {
public:
    virtual void fly() = 0;
    virtual ~FlyableRobot() {}
};

// Concrete implementation of FlyableRobot
class NormalFly: public FlyableRobot {
public:
    void fly() override {
        cout << "Flying normally." << endl;
    }
};

class NoFly: public FlyableRobot {
public:
    void fly() override {
        cout << "Cannot fly." << endl;
    }
};

// Robot base class
class Robot {
    protected:
        WalkableRobot* walkBehavior;
        TalkableRobot* talkBehavior;
        FlyableRobot* flyBehavior;

    public:
        Robot(WalkableRobot* walk, TalkableRobot* talk, FlyableRobot* fly)
            : walkBehavior(walk), talkBehavior(talk), flyBehavior(fly) {}

        void performWalk() {
            walkBehavior->walk();
        }

        void performTalk() {
            talkBehavior->talk();
        }

        void performFly() {
            flyBehavior->fly();
        }

        virtual void projection() = 0; // Abstract method for subclasses

};

// Concrete implementation of Robot class
class CompanionRobot: public Robot {
public:
    CompanionRobot(WalkableRobot* walk, TalkableRobot* talk, FlyableRobot* fly)
        : Robot(walk, talk, fly) {}

    void projection() override {
        cout << "I am a companion robot." << endl;
    }
};

// Another concrete implementation of Robot class
class SecurityRobot: public Robot {
public:
    SecurityRobot(WalkableRobot* walk, TalkableRobot* talk, FlyableRobot* fly)
        : Robot(walk, talk, fly) {}

    void projection() override {
        cout << "I am a security robot." << endl;
    }
};

int main(){
    Robot* r1 = new CompanionRobot(new NormalWalk(), new NormalTalk(), new NormalFly());
    r1->performWalk();
    r1->performTalk();
    r1->performFly();
    r1->projection();

    cout<<"------------------------"<<endl;

    Robot* r2 = new SecurityRobot(new NormalWalk(), new NoTalk(), new NoFly());
    r2->performWalk();
    r2->performTalk();
    r2->performFly();
    r2->projection();

    return 0;
    
}
