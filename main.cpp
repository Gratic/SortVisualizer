#include <SFML/Graphics.hpp>
#include "Headers/Sort.h"
#include "Headers/Value.h"
#include <vector>
#include <thread>
#include <iostream>

std::thread launchSort(Sort &sort, std::string type, int delay);

std::vector<sf::RectangleShape> valuesToRectangles(Sort &sort, int width, int height, int offsetX, int offsetY);

float factorToMaximize(float actual, float max);

void drawFromVector(sf::RenderWindow& window, std::vector<sf::RectangleShape> vector);

int WINDOW_WIDTH = 1200;
int WINDOW_HEIGHT = 400;
std::string DRAW_MODE = "LINE";
int NUMBER_OF_ELEMENT = 100;
std::vector<std::thread> threads;

int main() {
    Sort sortOne(NUMBER_OF_ELEMENT, 400);
    Sort sortTwo(NUMBER_OF_ELEMENT, 400);
    Sort sortThree(NUMBER_OF_ELEMENT, 400);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sort Visualizer | Zaleks");

    //std::sortThread th1(quickSort, std::ref(list), 0, NUMBER_OF_ELEMENT-1);
    threads.push_back(launchSort(sortOne, "quickSort", 10));
    threads.push_back(launchSort(sortTwo, "mergeSort", 10));
    threads.push_back(launchSort(sortThree, "bubbleSort", 10));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        //std::cout << Sort::checkSorted(sortOne) << std::endl;

        std::vector<sf::RectangleShape> rectanglesOne(
                valuesToRectangles(sortOne, 400, WINDOW_HEIGHT, 0, WINDOW_HEIGHT));
        std::vector<sf::RectangleShape> rectanglesTwo(
                valuesToRectangles(sortTwo, 400, WINDOW_HEIGHT, 400, WINDOW_HEIGHT));
        std::vector<sf::RectangleShape> rectanglesThree(
                valuesToRectangles(sortThree, 400, WINDOW_HEIGHT, 800, WINDOW_HEIGHT));
        window.clear();

        drawFromVector(window, rectanglesOne);
        drawFromVector(window, rectanglesTwo);
        drawFromVector(window, rectanglesThree);

        window.display();
    }

    for (int i(0); i < threads.size(); i++) {
        threads[i].detach();
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
    return th;
}

/*
 * Transforme les values en RectangleShape pour qu'ils soient affichés.
 */

std::vector<sf::RectangleShape> valuesToRectangles(Sort &sort, int width, int height, int offsetX, int offsetY) {
    std::vector<sf::RectangleShape> rectangles;
    float multiplierY = factorToMaximize(sort.getMaxValue(), height);
    float thickness = width / sort.getNumberOfElement();


    for (int i(0); i < sort.getValues().size(); i++) {
        int value(sort.getValues()[i].getValue());

        sf::Vector2f size(thickness, value * multiplierY);
        sf::RectangleShape rectangle(size);
        rectangle.setPosition(offsetX + i * thickness, offsetY);
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