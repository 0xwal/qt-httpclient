//
// Created by MINE on 15/03/2020.
//
#define CATCH_CONFIG_RUNNER

#include <qapplication.h>
#include "dependency/catch.hpp"

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    int result = Catch::Session().run(argc, argv);

    return result;
}
