
#include "modelnumbers.h"
#include "modeltemplate.h"
#include "pcomodelchecker.h"

#include <pcosynchro/pcomanager.h>

int main(int /*argc*/, char * /*argv*/[])
{
    // Uncommenting the following line allows to easily observe the PcoManager in the debugger
    //    auto pcoManager = PcoManager::getInstance();

    // Model template
    {
        // TemplateModelBlock model;
        // PcoModelChecker checker;
        // checker.setModel(&model);
        // checker.run();
    }
    {
        ModelNumbers model;
        PcoModelChecker checker;
        checker.setModel(&model);
        checker.run();
    }

    return 0;
}
