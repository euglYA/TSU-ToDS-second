#ifndef FACTORIES_H
#define FACTORIES_H

#include "cpp.h"
#include "c_sharp.h"

class CodeFactory {
public:
    virtual ~CodeFactory() = default;
    using Flags = unsigned int;

    virtual std::unique_ptr<MethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Flags flags) const = 0;
    virtual std::unique_ptr<ClassUnit> createClassUnit(const std::string& name) const = 0;
    virtual std::unique_ptr<PrintOperatorUnit> createPrintOperatorUnit(const std::string& text) const = 0;
};

class CodeFactoryCPP : public CodeFactory {
public:
    std::unique_ptr<MethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Flags flags) const override{
        return std::unique_ptr<MethodUnit> (new MethodUnitCPP(name, returnType, flags));
    }
    std::unique_ptr<ClassUnit> createClassUnit(const std::string& name) const override {
        return std::unique_ptr<ClassUnit> (new ClassUnitCPP(name));
    }
    std::unique_ptr<PrintOperatorUnit> createPrintOperatorUnit(const std::string& text) const override {
        return std::unique_ptr<PrintOperatorUnit> (new PrintOperatorUnitCPP(text));
    }
};

class CodeFactoryC_SHARP : public CodeFactory {
public:
    std::unique_ptr<MethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Flags flags) const override{
        return std::unique_ptr<MethodUnit> (new MethodUnitC_SHARP(name, returnType, flags));
    }
    std::unique_ptr<ClassUnit> createClassUnit(const std::string& name) const override {
        return std::unique_ptr<ClassUnit> (new ClassUnitC_SHARP(name));
    }
    std::unique_ptr<PrintOperatorUnit> createPrintOperatorUnit(const std::string& text) const override {
        return std::unique_ptr<PrintOperatorUnit> (new PrintOperatorUnitC_SHARP(text));
    }
};


#endif // FACTORIES_H
