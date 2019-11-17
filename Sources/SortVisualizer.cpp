//
// Created by Fraxinus on 17/11/2019.
//

#include "../Headers/SortVisualizer.h"
#include "../Headers/Sort.h"
#include <string>
#include <vector>
#include <thread>
#include "SFML/Graphics.hpp"
#include <iostream>

SortVisualizer::SortVisualizer(int numberOfElements, int maxValue, std::string sortType, sf::Vector2f position, sf::Vector2f size, int margin, int delay)
: numberOfElements(numberOfElements), maxValue(maxValue), sortType(sortType), position(position), size(size), margin(margin), delay(delay)
{
    sort = Sort(numberOfElements, maxValue);
}

void SortVisualizer::launchSort() {
//    std::thread th;
//    sort.setDelay(delay);
//    if (type == "quickSort")
//        th = std::thread(&Sort::quickSort, &sort, 0, numberOfElements - 1);
//    else if (type == "mergeSort")
//        th = std::thread(&Sort::mergeSort, &sort, 0, numberOfElements - 1);
//    else if (type == "bubbleSort")
//        th = std::thread(&Sort::bubbleSort, &sort);
//    else if (type == "selectionSort")
//        th = std::thread(&Sort::selectionSort, &sort);
//    return th;
    sort.setDelay(delay);
    if (sortType == "quickSort")
        thread = std::thread(&Sort::quickSort, &sort, 0, numberOfElements - 1);
    else if (sortType == "mergeSort")
        thread = std::thread(&Sort::mergeSort, &sort, 0, numberOfElements - 1);
    else if (sortType == "bubbleSort")
        thread = std::thread(&Sort::bubbleSort, &sort);
    else if (sortType == "selectionSort")
        thread = std::thread(&Sort::selectionSort, &sort);
}

std::vector<sf::RectangleShape> SortVisualizer::valuesToRectangles() const {
    std::vector<sf::RectangleShape> rectangles;
    float multiplierY = factorToMaximize(maxValue, (size.y - margin * 2));
    float thickness = (size.x - margin * 2) / numberOfElements;


    for (int i(0); i < sort.getValues().size(); i++) {
        int value(sort.getValues()[i].getValue());

        sf::Vector2f r_size(thickness, value * multiplierY);
        sf::RectangleShape rectangle(r_size);
        rectangle.setPosition(thickness + position.x + margin + i * thickness, position.y - margin);
//        rectangle.setPosition(0, 0);
        rectangle.setRotation(180);

        if(Sort::checkSorted(sort))
            rectangle.setFillColor(sf::Color::Blue);

        rectangles.push_back(rectangle);
    }

    if(!sort.getIsSorted())
    {
        if(sort.getPivotIndex() != -1)
            rectangles[sort.getPivotIndex()].setFillColor(sf::Color::Red);

        if(sort.getStartPivotIndex() != -1)
            rectangles[sort.getStartPivotIndex()].setFillColor(sf::Color::Green);

        for(int i(0); i < sort.getSortedIndexes().size(); i++)
        {
            rectangles[sort.getSortedIndexes()[i]].setFillColor(sf::Color::Blue);
        }
    }


    return rectangles;
}

float SortVisualizer::factorToMaximize(float actual, float max) const {
    return max / actual;
}

void SortVisualizer::drawFromVector(sf::RenderWindow& window, std::vector<sf::RectangleShape> vector) {
    for (int i(0); i < vector.size(); i++) {
        window.draw(vector[i]);
    }
}

const std::thread& SortVisualizer::getThread() const {
    return thread;
}

void SortVisualizer::detach() {
    thread.detach();
}