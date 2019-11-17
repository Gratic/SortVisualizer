//
// Created by Fraxinus on 14/11/2019.
//

#include "../Headers/Sort.h"
#include <vector>
#include <chrono>
#include <string>
#include <thread>

Sort::Sort() : delay(10), numberOfElement(100), pivotIndex(-1), startPivotIndex(-1), maxValue(100), sortedIndexes(std::vector<int>()) {
    srand(time(NULL));
    std::vector<Value> values;
    for (int i(0); i < 100; i++) {
        values.push_back(Value());
    }
    setValues(values);
    setIsSorted(false);
}

Sort::Sort(int numberOfElement) : delay(10), numberOfElement(numberOfElement), pivotIndex(-1), startPivotIndex(-1), maxValue(100), sortedIndexes(std::vector<int>()) {
    srand(time(NULL));
    std::vector<Value> values;
    for (int i(0); i < numberOfElement; i++) {
        values.push_back(Value());
    }
    setValues(values);
    setIsSorted(false);
}

Sort::Sort(int numberOfElement, int max) : delay(10), numberOfElement(numberOfElement), pivotIndex(-1), startPivotIndex(-1), maxValue(max), sortedIndexes(std::vector<int>()) {
    srand(time(NULL));
    std::vector<Value> values;
    for (int i(0); i < numberOfElement; i++) {
        values.push_back(Value(max));
    }
    setValues(values);
    setIsSorted(false);
}

// Implémentation d'un mergeSort
void Sort::mergeSort(int lo, int hi) {
    sleepDelay();
    if (lo < hi) {
        int m(lo + (hi - lo) / 2);
        mergeSort(lo, m);
        mergeSort(m + 1, hi);
        merge(lo, m, hi);
    }
}

// Fusion et tri de deux parties
void Sort::merge(int lo, int m, int hi) {
    sortedIndexes.clear();

    int n1(m - lo + 1); // Nombre d'éléments de la première partie
    int n2(hi - m);     // Nombre d'éléments de la deuxième partie

    std::vector<Value> a, b; // Vectors buffers

    // Copie des éléments dans leurs buffers
    for (int i(0); i < n1; i++)
    {
        a.push_back(getValues()[lo + i]);
        setStartPivotIndex(lo + i);
    }
    for (int i(0); i < n2; i++)
    {
        b.push_back(getValues()[m + 1 + i]);
        setPivotIndex(m + 1 + i);
    }

    // k = index dans le vector global, i et j = index dans les buffers
    int k(lo);
    int i(0), j(0);

    while (i < n1 && j < n2) {
        sleepDelay();
        if (a[i] < b[j]) {
            values[k] = a[i];
            i++;
        } else {
            values[k] = b[j];
            j++;
        }
        sortedIndexes.push_back(k);
        k++;
    }

    while (i < n1) {
        sleepDelay();
        values[k] = a[i];
        i++;
        sortedIndexes.push_back(k);
        k++;
    }

    while (j < n2) {
        sleepDelay();
        values[k] = b[j];
        j++;
        sortedIndexes.push_back(k);
        k++;
    }
}

// Implémentation d'un quickSort
void Sort::quickSort(int lo, int hi) {
    if (lo < hi) {
        setStartPivotIndex(hi);
        int pivot(hi);
        int i(lo);
        while (i <= pivot) {
            if (getValues()[i] > getValues()[pivot]) {
                sleepDelay();
                swap(i, pivot - 1);
                sleepDelay();
                swap(pivot - 1, pivot);

                pivot--;
            } else
                i++;

            setPivotIndex(pivot);
        }
        sortedIndexes.push_back(pivot);

        quickSort(lo, pivot - 1);
        quickSort(pivot + 1, hi);
    }
    else
        sortedIndexes.push_back(lo);
}

void Sort::bubbleSort() {
    int size(getValues().size());
    for(int i(0); i < size; i++)
    {
        for(int j(0); j < size - 1 - i; j++)
        {
            setPivotIndex(j);
            if(getValues()[j] > getValues()[j + 1])
            {
                sleepDelay();
                swap(j, j + 1);
            }
        }
        sortedIndexes.push_back(size - i - 1);
    }

}

void Sort::selectionSort() {
    for(int i(0); i < getNumberOfElement(); i++)
    {
        int min(getNumberOfElement() - 1);
        for(int j(i); j < getNumberOfElement(); j++)
        {
            sleepDelay();
            if(getValues()[j] < getValues()[min])
                min = j;
            setPivotIndex(min);
        }
        swap(i, min);
        sortedIndexes.push_back(i);
    }
}

// Permet d'échanger deux valeurs au sein du vector de l'objet
void Sort::swap(int a, int b) {
    Value buffer(values[a]);
    values[a] = values[b];
    values[b] = buffer;
}

std::string Sort::toString() const {
    std::string msg("");
    for (int i(0); i < getValues().size(); i++) {
        msg += getValues()[i].toString() + " ";
    }
    return msg;
}

// Méthode static : Renvoie true si le vector est trié.
bool Sort::checkSorted(Sort sort) {
    if (!sort.getIsSorted()) {
        bool isSorted = true;
        for (int i(0); i < sort.getValues().size() - 1; i++) {
            if (sort.getValues()[i] > sort.getValues()[i + 1]) {
                isSorted = false;
                break;
            }
        }
        sort.setIsSorted(isSorted);
        return isSorted;
    } else
        return sort.getIsSorted();
}

void Sort::sleepDelay() {
    std::this_thread::sleep_for(std::chrono::milliseconds(getDelay()));
}

const std::vector<Value> &Sort::getValues() const {
    return values;
}

void Sort::setValues(const std::vector<Value> &values) {
    Sort::values = values;
}

int Sort::getPivotIndex() const {
    return pivotIndex;
}

void Sort::setPivotIndex(int pivotIndex) {
    Sort::pivotIndex = pivotIndex;
}

int Sort::getNumberOfElement() const {
    return numberOfElement;
}

void Sort::setNumberOfElement(int numberOfElement) {
    Sort::numberOfElement = numberOfElement;
}

int Sort::getDelay() const {
    return delay;
}

void Sort::setDelay(int delay) {
    Sort::delay = delay;
}

bool Sort::getIsSorted() const {
    return isSorted;
}

void Sort::setIsSorted(bool isSorted) {
    Sort::isSorted = isSorted;
}

int Sort::getStartPivotIndex() const {
    return Sort::startPivotIndex;
}

void Sort::setStartPivotIndex(int startPivotIndex) {
    Sort::startPivotIndex = startPivotIndex;
}

int Sort::getMaxValue() const {
    return Sort::maxValue;
}

void Sort::setMaxValue(int maxValue) {
    Sort::maxValue = maxValue;
}

const std::vector<int>& Sort::getSortedIndexes() const {
    return sortedIndexes;
}

void Sort::setSortedIndexes(std::vector<int> sortedIndexes) {
    Sort::sortedIndexes = sortedIndexes;
}