#ifndef MODEL_BARRIERE_H
#define MODEL_BARRIERE_H

#include <iostream>
#include <memory>

#include "observablethread.h"
#include "pcobarrier.h"
#include "pcoconcurrencyanalyzer.h"
#include "pcomodel.h"
#include "pcosynchro/pcosemaphore.h"

static PcoBarrier barrier{3};

class AccessThread : public ObservableThread
{
public:
    explicit AccessThread(std::string id = "")
        : ObservableThread(std::move(id))
    {
        scenarioGraph = std::make_unique<ScenarioGraph>();
        auto scenario = scenarioGraph->createNode(this, -1);
        auto p1 = scenarioGraph->createNode(this, 1);
        auto p2 = scenarioGraph->createNode(this, 2);
        scenario->next.push_back(p1);
        p1->next.push_back(p2);
        scenarioGraph->setInitialNode(scenario);
    }

    static void init() {}

    static void clean() {}

private:
    static std::unique_ptr<PcoSemaphore> semaphore;
    void run() override
    {
        startSection(1);
        barrier.arrive();
        startSection(2);
        barrier.arrive();
        endScenario();
    }
};

std::unique_ptr<PcoSemaphore> AccessThread::semaphore = nullptr;

class ModelBarrier : public PcoModel
{
    bool checkInvariants() override { return true; }

    void build() override
    {
        threads.emplace_back(std::make_unique<AccessThread>("1"));
        threads.emplace_back(std::make_unique<AccessThread>("2"));
        threads.emplace_back(std::make_unique<AccessThread>("3"));

        scenarioBuilder = std::make_unique<ScenarioBuilderBuffer>();
        scenarioBuilder->init(threads, 6);
    }

    void preRun(Scenario & /*scenario*/) override {}

    void postRun(Scenario &scenario) override {}

    void finalReport() override {}
};

#endif // MODEL_BARRIERE_H
