//
// Created by Fraxinus on 14/11/2019.
//

#ifndef TRISFML_VALUE_H
#define TRISFML_VALUE_H

#include <random>
#include <string>

class Value {
private:
    int value;
    bool isPivot;
    bool isOrdered;
    bool isInUse;
public:
    bool getIsPivot() const;

    void setIsPivot(bool isPivot);

    bool getIsOrdered() const;

    void setIsOrdered(bool isOrdered);

    bool getIsInUse() const;

    void setIsInUse(bool isInUse);

    bool operator==(const Value &rhs) const;

    bool operator!=(const Value &rhs) const;

    bool operator<(const Value &rhs) const;

    bool operator>(const Value &rhs) const;

    bool operator<=(const Value &rhs) const;

    bool operator>=(const Value &rhs) const;

    Value();
    Value(int max);

    int getValue() const;

    void setValue(int value);

    std::string toString() const;
};


#endif //TRISFML_VALUE_H
