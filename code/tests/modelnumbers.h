#ifndef MODELNUMBERS_H
#define MODELNUMBERS_H

#include <iostream>

#include "pcomodel.h"
#include "scenariobuilder.h"

// The shared variable
static int number = 0;

int getNumber()
{
    return number;
}

class ThreadA : public ObservableThread
{
public:
    explicit ThreadA(std::string id = "")
        : ObservableThread(std::move(id))
    {
        scenarioGraph = std::make_unique<ScenarioGraph>();
        auto scenario = scenarioGraph->createNode(this, -1);
        auto p1 = scenarioGraph->createNode(this, 1);
        auto p2 = scenarioGraph->createNode(this, 2);
        auto p3 = scenarioGraph->createNode(this, 3);
        scenario->next.push_back(p1);
        p1->next.push_back(p2);
        p2->next.push_back(p3);
        scenarioGraph->setInitialNode(scenario);
    }

private:
    void run() override
    {
        startSection(1);
        number = 0;
        startSection(2);
        int reg = number;
        startSection(3);
        number = reg + 7;
        endScenario();
    }
};

class ThreadB : public ObservableThread
{
public:
    explicit ThreadB(std::string id = "")
        : ObservableThread(std::move(id))
    {
        scenarioGraph = std::make_unique<ScenarioGraph>();
        auto scenario = scenarioGraph->createNode(this, -1);
        auto p1 = scenarioGraph->createNode(this, 4);
        auto p2 = scenarioGraph->createNode(this, 5);
        auto p3 = scenarioGraph->createNode(this, 6);
        scenario->next.push_back(p1);
        p1->next.push_back(p2);
        p2->next.push_back(p3);
        scenarioGraph->setInitialNode(scenario);
    }

private:
    void run() override
    {
        startSection(4);
        number = 1;
        startSection(5);
        int reg = number;
        startSection(6);
        number = reg * 2;
        endScenario();
    }
};

class ThreadC : public ObservableThread
{
public:
    explicit ThreadC(std::string id = "")
        : ObservableThread(std::move(id))
    {
        scenarioGraph = std::make_unique<ScenarioGraph>();
        auto scenario = scenarioGraph->createNode(this, -1);
        auto p1 = scenarioGraph->createNode(this, 7);
        auto p2 = scenarioGraph->createNode(this, 8);
        auto p3 = scenarioGraph->createNode(this, 9);
        scenario->next.push_back(p1);
        p1->next.push_back(p2);
        p2->next.push_back(p3);
        scenarioGraph->setInitialNode(scenario);
    }

private:
    void run() override
    {
        startSection(7);
        number = 0;
        startSection(8);
        int reg = number;
        startSection(9);
        number = reg + 1;
        endScenario();
    }
};

class ModelNumbers : public PcoModel
{
public:
    bool checkInvariants() override
    {
        // For testing purpose :
        //std::cout << "Checking invariant" << std::endl;
        return true;
    }

    void build() override
    {
#ifdef PREDEFINED_SCENARIOS

        threads.emplace_back(std::make_unique<ThreadA>("1"));
        threads.emplace_back(std::make_unique<ThreadB>("2"));

        auto t1 = threads[0].get();
        auto t2 = threads[1].get();
        auto builder = std::make_unique<PredefinedScenarioBuilderIter>();
        std::vector<Scenario> scenarios
            = {{{t1, 1}, {t1, 2}, {t1, 3}, {t2, 4}, {t2, 5}, {t2, 6}},
               { {t2, 4},
                 {t2, 5},
                 {t2, 6},
                 {t1, 1},
                 {t1, 2},
                 {t1, 3} }};
        builder->setScenarios(scenarios);
        scenarioBuilder = std::move(builder);

#else // PREDEFINED_SCENARIOS

        threads.emplace_back(std::make_unique<ThreadA>("1"));
        threads.emplace_back(std::make_unique<ThreadB>("2"));
        threads.emplace_back(std::make_unique<ThreadC>("3"));

        scenarioBuilder = std::make_unique<ScenarioBuilderBuffer>();
        scenarioBuilder->init(threads, 9);

#endif // PREDEFINED_SCENARIOS
    }

    void preRun(Scenario & /*scenario*/) override {}

    void postRun(Scenario &scenario) override
    {
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Scenario : ";
        ScenarioPrint::printScenario(scenario);
        std::cout << "Number = " << getNumber() << std::endl;
        possibleNumber.insert(getNumber());
    }

    std::set<int> possibleNumber;

    void finalReport() override
    {
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Possible output number : ";
        for (const int &value : possibleNumber)
            std::cout << value << ", ";
        std::cout << std::endl;
        std::cout << std::flush;
    }
};

#endif // MODELNUMBERS_H
