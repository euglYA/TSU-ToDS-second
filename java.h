#pragma once
#ifndef JAVA_H
#define JAVA_H
#include "af_units.h"

class ClassUnitJAVA : public ClassUnit {
public:

    ClassUnitJAVA(const std::string& name) :
        ClassUnit(name) {}

    std::string compile(unsigned int level = 0) const override {
        std::string result = generateShift(level) + "class " + getName() + " {\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
            if (getFields(i).empty())
                continue;

            for (const auto& f : getFields(i)) {
                result += f->compile(level + 1);
            }
            result += "\n";
        }

        result += generateShift(level) + "};\n";
        return result;
    }
};

class MethodUnitJAVA : public MethodUnit {
public:
    MethodUnitJAVA(const std::string& name, const std::string& returnType, Flags flags) :
        MethodUnit(name, returnType, flags) { }

    std::string compile(unsigned int level = 0) const override {
        std::string result = generateShift(level);
        Flags flags = getFlags();

        if (flags & PUBLIC)
            result += "public ";
        else if (flags & PROTECTED)
            result += "protected ";
        else
            result += "private ";

        if (flags & STATIC)
            result += " static ";
        else if (flags & FINAL)
            result += " final ";
        else if (flags & ABSTRACT)
            result += " abstract ";

        result += getReturnType() + " ";
        result += getName() + "()";

        result += " {\n";

        for (const auto& b : getBody()) {
            result += b->compile(level + 1);
        }

        result += generateShift(level) + "}\n";
        return result;
    }
};

class PrintOperatorUnitJAVA : public PrintOperatorUnit {
public:
    PrintOperatorUnitJAVA(const std::string& text) :
        PrintOperatorUnit(text) {}

    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "printf(\"" + getText() + "\");\n";
    }
};


#endif // JAVA_H
