#ifndef CPP_H
#define CPP_H
#include "af_units.h"

class MethodUnitCPP : public MethodUnit {
public:
    enum Modifier {
        STATIC              = 1,
        CONST               = 1 << 1,
        VIRTUAL             = 1 << 2
    };

    MethodUnitCPP(const std::string& name, const std::string& returnType, Flags flags) :
        MethodUnit(name, returnType, flags) { }

    std::string compile(unsigned int level = 0) const override {
        std::string result = generateShift(level);

        if (getFlags() & STATIC)
            result += "static ";
        else if (getFlags() & VIRTUAL)
            result += "virtual ";

        result += getReturnType() + " ";
        result += getName() + "()";

        if (getFlags() & CONST)
            result += " const";

        result += " {\n";

        for (const auto& b : getBody()) {
            result += b->compile(level + 1);
        }

        result += generateShift(level) + "}\n";
        return result;
    }
};



class ClassUnitCPP : public ClassUnit {
public:

    ClassUnitCPP(const std::string& name) :
        ClassUnit(name) {}

    std::string compile(unsigned int level = 0) const override {
        std::string result = generateShift(level) + "class " + getName() + " {\n";
        std::vector<std::string> ModifiersCPP = {"public", "protected", "private"};
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

class PrintOperatorUnitCPP : public PrintOperatorUnit {
public:
    PrintOperatorUnitCPP(const std::string& text) :
        PrintOperatorUnit(text) {}

    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "printf(\"" + getText() + "\");\n";
    }
};


#endif // CPP_H
