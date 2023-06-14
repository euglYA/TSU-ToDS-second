
#include <QCoreApplication>

#include "Factories.h"

std::string generateProgram(const std::shared_ptr<CodeFactory> &factory) {
    std::unique_ptr<ClassUnit> myClass = factory->createClassUnit("MyClass");
    myClass->add(factory->createMethodUnit("testFunc1", "void", MethodUnit::PUBLIC));

    myClass->add(factory->createMethodUnit("testFunc2", "void", MethodUnit::STATIC | MethodUnit::PRIVATE));

    myClass->add(factory->createMethodUnit("testFunc3", "void", MethodUnit::VIRTUAL | MethodUnit::CONST | MethodUnit::PROTECTED));

    std::shared_ptr<MethodUnit> method = factory->createMethodUnit("testFunc4", "void", MethodUnit::STATIC | MethodUnit::PROTECTED);
    method->add(factory->createPrintOperatorUnit(R"(Hello, world!)"));

    myClass->add(method);

    myClass->add(factory->createMethodUnit("testFunc5", "void", MethodUnit::VIRTUAL | MethodUnit::CONST | MethodUnit::PROTECTED_INTERNAL));

    return myClass->compile();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << "C++: \n\n" << generateProgram(std::make_shared<CodeFactoryC_SHARP>()) << std::endl;
  return a.exec();
}
