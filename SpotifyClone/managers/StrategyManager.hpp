#pragma once
#include<iostream>
#include "../strategies/SequentialPlayStrategy.hpp"
#include "../strategies/RandomPlayStrategy.hpp"
#include "../strategies/CustomQueueStrategy.hpp"
#include "../enums/PlayStrategyType.hpp"

using namespace std;

class StrategyManager {
    private:
        static StrategyManager* instance;
        SequentialPlayStrategy* sequentialStrategy;
        RandomPlayStrategy* randomStrategy;
        CustomQueueStrategy* customQueueStrategy;
        
        StrategyManager(){
            sequentialStrategy = new SequentialPlayStrategy();
            randomStrategy = new RandomPlayStrategy();
            customQueueStrategy = new CustomQueueStrategy();
        }

    public:
        static StrategyManager* getInstance() {
            if (instance == nullptr) {
                instance = new StrategyManager();
            }
            return instance;
        }

        

        PlayStrategy* getStrategy(PlayStrategyType strategy) {
            switch(strategy) {
                case PlayStrategyType::SEQUENTIAL:
                    return sequentialStrategy;
                case PlayStrategyType::RANDOM:
                    return randomStrategy;
                case PlayStrategyType::CUSTOM_QUEUE:
                    return customQueueStrategy;
                default:
                    throw runtime_error("Invalid strategy.");
            }
        }
};

StrategyManager* StrategyManager::instance = nullptr;