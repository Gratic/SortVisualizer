//
// Created by Fraxinus on 14/11/2019.
//

#include "../Headers/Value.h"
#include <random>
#include <string>

Value::Value() {
    //srand(time(NULL));
    setValue(rand() % 100);
}

Value::Value(int max) {
    //srand(time(NULL));
    setValue(rand() % max);
}

int Value::getValue() const {
    return value;
}

void Value::setValue(int value) {
    Value::value = value;
}

bool Value::getIsPivot() const {
    return isPivot;
}

void Value::setIsPivot(bool isPivot) {
    Value::isPivot = isPivot;
}

bool Value::getIsOrdered() const {
    return isOrdered;
}

void Value::setIsOrdered(bool isOrdered) {
    Value::isOrdered = isOrdered;
}

bool Value::getIsInUse() const {
    return isInUse;
}

void Value::setIsInUse(bool isInUse) {
    Value::isInUse = isInUse;
}

bool Value::operator==(const Value &rhs) const {
    return value == rhs.value;
}

bool Value::operator!=(const Value &rhs) const {
    return !(rhs == *this);
}

bool Value::operator<(const Value &rhs) const {
    return value < rhs.value;
}

bool Value::operator>(const Value &rhs) const {
    return rhs < *this;
}

bool Value::operator<=(const Value &rhs) const {
    return !(rhs < *this);
}

bool Value::operator>=(const Value &rhs) const {
    return !(*this < rhs);
}

std::string Value::toString() const {
    return std::to_string(getValue());
}
