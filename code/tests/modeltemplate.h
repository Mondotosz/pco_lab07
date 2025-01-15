#ifndef MODELTEMPLATE_H
#define MODELTEMPLATE_H

#include <iostream>

#include "pcoconcurrencyanalyzer.h"
#include "pcomodel.h"
#include "pcosynchro/pcosemaphore.h"

class TemplateThreadBlock : public ObservableThread
{
public:
    explicit TemplateThreadBlock(std::string id = "")
        : ObservableThread(std::move(id))
    {}

    static void init() {}

    static void clean() {}

private:
    static std::unique_ptr<PcoSemaphore> semaphore;
    void run() override {}
};

std::unique_ptr<PcoSemaphore> TemplateThreadBlock::semaphore = nullptr;

class TemplateModelBlock : public PcoModel
{
    bool checkInvariants() override { return true; }

    void build() override {}

    void preRun(Scenario & /*scenario*/) override {}

    void postRun(Scenario &scenario) override {}

    void finalReport() override {}
};

#endif // MODELTEMPLATE_H
