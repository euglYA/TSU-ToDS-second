#pragma once
#ifndef FACTORIES_H
#define FACTORIES_H

#include "cpp.h"
#include "c_sharp.h"
#include "java.h"

class CodeFactory {
public:
    virtual ~CodeFactory() = default;
    using Flags = unsigned int;

    virtual std::shared_ptr<MethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Flags flags) const = 0;
    virtual std::shared_ptr<ClassUnit> createClassUnit(const std::string& name) const = 0;
    virtual std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(const std::string& text) const = 0;
};

class CodeFactoryCPP : public CodeFactory {
public:
    std::shared_ptr<MethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Flags flags) const override {
        return std::make_shared<MethodUnitCPP>(name, returnType, flags);
    }
    std::shared_ptr<ClassUnit> createClassUnit(const std::string& name) const override {
        return std::make_shared<ClassUnitCPP>(name);
    }
    std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(const std::string& text) const override {
        return std::make_shared<PrintOperatorUnitCPP>(text);
    }
};

class CodeFactoryC_SHARP : public CodeFactory {
public:
    std::shared_ptr<MethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Flags flags) const override {
        return std::make_shared<MethodUnitC_SHARP>(name, returnType, flags);
    }
    std::shared_ptr<ClassUnit> createClassUnit(const std::string& name) const override {
        return std::make_shared<ClassUnitC_SHARP>(name);
    }
    std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(const std::string& text) const override {
        return std::make_shared<PrintOperatorUnitC_SHARP>(text);
    }
};

class CodeFactoryJAVA : public CodeFactory {
public:
    std::shared_ptr<MethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Flags flags) const override {
        return std::make_shared<MethodUnitJAVA>(name, returnType, flags);
    }
    std::shared_ptr<ClassUnit> createClassUnit(const std::string& name) const override {
        return std::make_shared<ClassUnitJAVA>(name);
    }
    std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(const std::string& text) const override {
        return std::make_shared<PrintOperatorUnitJAVA>(text);
    }
};

#endif // FACTORIES_H
