#include <SFML/Graphics.hpp>
#include "Headers/Sort.h"
#include "Headers/Value.h"
#include <vector>
#include <thread>
#include <iostream>
#include "Headers/SortVisualizer.h"

std::thread launchSort(Sort &sort, std::string type, int delay);
std::vector<sf::RectangleShape> valuesToRectangles(Sort &sort, int width, int height, int offsetX, int offsetY);
float factorToMaximize(float actual, float max);
void drawFromVector(sf::RenderWindow& window, std::vector<sf::RectangleShape> vector);

int WINDOW_WIDTH = 1600;
int WINDOW_HEIGHT = 400;
std::string DRAW_MODE = "LINE";
int NUMBER_OF_ELEMENT = 50;
int DELAY = 10;

int main() {
    std::vector<SortVisualizer> sorts;

    sorts.push_back(SortVisualizer(NUMBER_OF_ELEMENT, 400, "quickSort", sf::Vector2f(0,400), sf::Vector2f(400,400), 40, DELAY));
    sorts.push_back(SortVisualizer(NUMBER_OF_ELEMENT, 400, "mergeSort", sf::Vector2f(400,400), sf::Vector2f(400,400), 40, DELAY));
    sorts.push_back(SortVisualizer(NUMBER_OF_ELEMENT, 400, "bubbleSort", sf::Vector2f(800,400), sf::Vector2f(400,400), 40, DELAY));
    sorts.push_back(SortVisualizer(NUMBER_OF_ELEMENT, 400, "selectionSort", sf::Vector2f(1200,400), sf::Vector2f(400,400), 40, DELAY));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sort Visualizer | Zaleks");

    for(int i(0); i < sorts.size(); i++)
    {
        sorts[i].launchSort();
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        //std::cout << Sort::checkSorted(sortOne) << std::endl;

        window.clear();

        for(int i(0); i < sorts.size(); i++)
        {
            window.draw(sorts[i]);
        }
        window.display();
    }

    for(int i(0); i < sorts.size(); i++)
    {
        sorts[i].detach();
    }

    return 0;
}

std::thread launchSort(Sort &sort, std::string type, int delay) {
    std::thread th;
    sort.setDelay(delay);
    if (type == "quickSort")
        th = std::thread(&Sort::quickSort, &sort, 0, NUMBER_OF_ELEMENT - 1);
    else if (type == "mergeSort")
        th = std::thread(&Sort::mergeSort, &sort, 0, NUMBER_OF_ELEMENT - 1);
    else if (type == "bubbleSort")
        th = std::thread(&Sort::bubbleSort, &sort);
    else if (type == "selectionSort")
        th = std::thread(&Sort::selectionSort, &sort);
    return th;
}

/*
 * Transforme les values en RectangleShape pour qu'ils soient affichés.
 */

std::vector<sf::RectangleShape> valuesToRectangles(Sort &sort, int width, int height, int offsetX, int offsetY) {
    std::vector<sf::RectangleShape> rectangles;
    float multiplierY = factorToMaximize(sort.getMaxValue(), (height- 20));
    float thickness = (width - 20) / sort.getNumberOfElement();


    for (int i(0); i < sort.getValues().size(); i++) {
        int value(sort.getValues()[i].getValue());

        sf::Vector2f size(thickness, value * multiplierY);
        sf::RectangleShape rectangle(size);
        rectangle.setPosition(10 + thickness + offsetX + i * thickness, offsetY - 10);
        rectangle.setRotation(180);

        if(sort.getIsSorted())
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

float factorToMaximize(float actual, float max) {
    return max / actual;
}

void drawFromVector(sf::RenderWindow& window, std::vector<sf::RectangleShape> vector)
{
    for (int i(0); i < vector.size(); i++) {
        window.draw(vector[i]);
    }
}