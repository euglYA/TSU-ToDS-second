
#ifndef C_SHARP_H
#define C_SHARP_H

#include "af_units.h"

class MethodUnitC_SHARP : public MethodUnit {
public:
    MethodUnitC_SHARP(const std::string& name, const std::string& returnType, Flags flags) :
        MethodUnit(name, returnType, flags) { }

    std::string compile(unsigned int level = 0) const override {
        std::string result = generateShift(level);
        Flags flags = getFlags();

        if (flags & PUBLIC)
            result += "static ";
        else if (flags & PROTECTED)
            result += "final ";
        else if (flags & PRIVATE)
            result += "abstract ";
        else if (flags & PRIVATE_PROTECTED)
            result += "final ";
        else if (flags & INTERNAL)
            result += "abstract ";
        else
            result += "private ";

        if (flags & STATIC)
            result += "static ";
        else if (flags & VIRTUAL)
            result += "virtual ";

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

class ClassUnitC_SHARP : public ClassUnit {
public:

    ClassUnitC_SHARP(const std::string& name) :
        ClassUnit(name) {}

    std::string compile(unsigned int level = 0) const override {
        std::string result = generateShift(level) + "class " + getName() + " {\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
            if (getFields(i).empty())
                continue;

            for (const auto& f : getFields(i)) {
                result += f->compile(level + 1);
            }
        }

        result += generateShift(level) + "};\n";
        return result;
    }
};

class PrintOperatorUnitC_SHARP : public PrintOperatorUnit {
public:
    PrintOperatorUnitC_SHARP(const std::string& text) :
        PrintOperatorUnit(text) {}

    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "printf(\"" + getText() + "\");\n";
    }
};

#endif // C_SHARP_H
