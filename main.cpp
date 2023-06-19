
#include <QCoreApplication>

#include "Factories.h"

std::string generateProgram(const std::shared_ptr<CodeFactory> &factory) {
    std::shared_ptr<ClassUnit> myClass = factory->createClassUnit("MyClass");

    std::shared_ptr<MethodUnit> method = factory->createMethodUnit("testFuncPub", "void", MethodUnit::PUBLIC);
    method->add(factory->createPrintOperatorUnit(R"(Hello, world!)"));
    myClass->add(method);

    myClass->add(factory->createMethodUnit("testFuncStPrv", "void", MethodUnit::STATIC | MethodUnit::PRIVATE));
    myClass->add(factory->createMethodUnit("testFuncVCPro", "void", MethodUnit::VIRTUAL | MethodUnit::CONST | MethodUnit::PROTECTED));
    myClass->add(factory->createMethodUnit("testFuncStPro", "void", MethodUnit::STATIC | MethodUnit::PROTECTED));
    myClass->add(factory->createMethodUnit("testFuncVCPro_Int", "void", MethodUnit::VIRTUAL | MethodUnit::CONST | MethodUnit::PROTECTED_INTERNAL));

    return myClass->compile();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    std::cout << "C++:\n" << generateProgram(std::make_shared<CodeFactoryCPP>()) << std::endl;
    std::cout << "C#:\n" << generateProgram(std::make_shared<CodeFactoryC_SHARP>()) << std::endl;
    std::cout << "Java:\n" << generateProgram(std::make_shared<CodeFactoryJAVA>()) << std::endl;

  return a.exec();
}
