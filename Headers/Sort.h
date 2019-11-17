//
// Created by Fraxinus on 14/11/2019.
//

#ifndef TRISFML_SORT_H
#define TRISFML_SORT_H

#include "Value.h"
#include <vector>
#include <chrono>
#include <string>
#include <thread>

class Sort {
private:
    std::vector<Value> values;
    int pivotIndex;
    int startPivotIndex;
    int numberOfElement;
    int delay;
    bool isSorted;
    int maxValue;
    std::vector<int> sortedIndexes;
public:
    Sort();

    Sort(int numberOfElement);

    Sort(int numberOfElement, int max);

    void mergeSort(int lo, int hi);

    void merge(int lo, int m, int hi);

    void quickSort(int lo, int hi);

    void bubbleSort();

    void selectionSort();

    void swap(int a, int b);

    void sleepDelay();

    std::string toString() const;

    int getNumberOfElement() const;

    void setNumberOfElement(int numberOfElement);

    const std::vector<Value> &getValues() const;

    void setValues(const std::vector<Value> &values);

    int getPivotIndex() const;

    void setPivotIndex(int pivotIndex);

    int getStartPivotIndex() const;

    void setStartPivotIndex(int startPivotIndex);

    void setDelay(int delay);

    int getDelay() const;

    bool getIsSorted() const;

    void setIsSorted(bool isSorted);

    int getMaxValue() const;

    void setMaxValue(int maxValue);

    const std::vector<int>& getSortedIndexes() const;

    void setSortedIndexes(std::vector<int> sortedIndexes);

    bool static checkSorted(Sort sort);
};


#endif //TRISFML_SORT_H
