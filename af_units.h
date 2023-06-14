#ifndef AF_UNITS_H
#define AF_UNITS_H
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <vector>


class AbstractFactory {

};



class Unit {
public:
    using Flags = unsigned int;

    virtual ~Unit() = default;

    virtual void add(const std::shared_ptr<Unit>&) {
        throw std::runtime_error("Not supported");
    }

    virtual std::string compile(unsigned int level = 0) const = 0;

    virtual Flags getFlags() const = 0;

protected:
    virtual std::string generateShift(unsigned int level) const {
        static const auto DEFAULT_SHIFT = "    ";
        std::string result;
        for (unsigned int i = 0; i < level; i++) {
            result += DEFAULT_SHIFT;
        }
        return result;
    }
};



class MethodUnit : public Unit {
public:
    enum Modifier {
        STATIC              = 1,
        CONST               = 1 << 1,
        VIRTUAL             = 1 << 2,
        PUBLIC              = 1 << 3,
        PROTECTED           = 1 << 4,
        PRIVATE             = 1 << 5,
        FINAL               = 1 << 6,
        ABSTRACT            = 1 << 7,
        INTERNAL            = 1 << 8,
        PROTECTED_INTERNAL  = 1 << 9,
        PRIVATE_PROTECTED   = 1 << 10
    };

    MethodUnit(const std::string& name, const std::string& returnType, Flags flags) :
        m_name(name), m_returnType(returnType), m_flags(flags) { }

    void add(const std::shared_ptr<Unit>& unit) {
        m_body.push_back(unit);
    }
    std::string compile(unsigned int level = 0) const {
        throw std::runtime_error("Not supported");
    }

protected:
    std::string getName() const {
        return m_name;
    }

    std::string getReturnType() const {
        return m_returnType;
    }

    Flags getFlags() const {
        return m_flags;
    }

    std::vector<std::shared_ptr<Unit>> getBody() const {
        return m_body;
    }

private:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;
    std::vector<std::shared_ptr<Unit>> m_body;
};



class ClassUnit : public Unit {
public:
    enum AccessModifier {
        PUBLIC,
        PROTECTED,
        PRIVATE,
        INTERNAL,
        PROTECTED_INTERNAL,
        PRIVATE_PROTECTED
    };

    static const std::vector<std::string> ACCESS_MODIFIERS;

    explicit ClassUnit(const std::string& name) : m_name(name) {
        m_fields.resize(ACCESS_MODIFIERS.size());
    }

    void add(const std::shared_ptr<Unit>& unit) {
        int accessModifier = PRIVATE;
        Flags flags = unit->getFlags();

        if (flags & MethodUnit::PUBLIC)
            accessModifier = PUBLIC;
        else if (flags & MethodUnit::PROTECTED)
            accessModifier = PROTECTED;
        else if (flags & MethodUnit::INTERNAL)
            accessModifier = INTERNAL;
        else if (flags & MethodUnit::PROTECTED_INTERNAL)
            accessModifier = PROTECTED_INTERNAL;
        else if (flags & MethodUnit::PRIVATE_PROTECTED)
            accessModifier = PRIVATE_PROTECTED;

        m_fields[accessModifier].push_back(unit);
    }

    std::string compile(unsigned int level = 0) const {
        throw std::runtime_error("Not supported");
    }

protected:
    std::string getName() const {
        return m_name;
    }

private:
    std::string m_name;
    using Fields = std::vector<std::shared_ptr<Unit>>;
    std::vector<Fields> m_fields;
};

const std::vector<std::string> ClassUnit::ACCESS_MODIFIERS = {"public", "protected", "private", "internal", "protected internal", "private protected"};

class PrintOperatorUnit : public Unit {
public:
    explicit PrintOperatorUnit(const std::string& text) :
        m_text(text) {}

    std::string compile(unsigned int level = 0) const {
        throw std::runtime_error("Not supported");
    }

private:
    std::string m_text;
};


#endif // AF_UNITS_H
