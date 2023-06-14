#ifndef CPP_H
#define CPP_H
#include "af_units.h"

class ClassUnitCPP : public ClassUnit {
public:

    ClassUnitCPP(const std::string& name) :
        ClassUnit(name) {}

    std::string compile(unsigned int level = 0) const override {
        std::string result = generateShift(level) + "class " + getName() + " {\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
            if (getFields(i).empty())
                continue;
            result += ACCESS_MODIFIERS[i] + ":\n";

            for (const auto& f : getFields(i)) {
                result += f->compile(level + 1);
            }
            result += "\n";
        }

        result += generateShift(level) + "};\n";
        return result;
    }
};

class MethodUnitCPP : public MethodUnit {
public:
    MethodUnitCPP(const std::string& name, const std::string& returnType, Flags flags) :
        MethodUnit(name, returnType, flags) { }

    std::string compile(unsigned int level = 0) const override {
        std::string result = generateShift(level);
        Flags flags = getFlags();

        if (flags & STATIC)
            result += "static ";
        else if (flags & VIRTUAL)
            result += "virtual ";

        result += getReturnType() + " ";
        result += getName() + "()";

        if (flags & CONST)
            result += " const";

        result += " {\n";

        for (const auto& b : getBody()) {
            result += b->compile(level + 1);
        }

        result += generateShift(level) + "}\n";
        return result;
    }
};

class PrintOperatorUnitCPP : public PrintOperatorUnit {
public:
    PrintOperatorUnitCPP(const std::string& text) :
        PrintOperatorUnit(text) {}

    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "printf(\"" + getText() + "\");\n";
    }
};


#endif // CPP_H
