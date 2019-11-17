//
// Created by Fraxinus on 17/11/2019.
//

#ifndef SORTVISUALIZER_SORTVISUALIZER_H
#define SORTVISUALIZER_SORTVISUALIZER_H


#include "../Headers/SortVisualizer.h"
#include "../Headers/Sort.h"
#include <string>
#include <vector>
#include <thread>
#include "SFML/Graphics.hpp"
#include <iostream>

class SortVisualizer : public sf::Drawable {
private:
    int numberOfElements;
    int maxValue;
    Sort sort;
    std::string sortType;
    sf::Vector2f position;
    sf::Vector2f size;
    int margin;
    std::thread thread;
    int delay;
public:
    SortVisualizer(int numberOfElements, int maxValue, std::string sortType, sf::Vector2f position, sf::Vector2f size, int margin, int delay);
    void launchSort();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        int thickness(1);

        sf::Font font;
        font.loadFromFile("Roboto-Regular.ttf");
        sf::Text text;
        text.setFont(font);
        text.setString(sortType);
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::White);

        int pxSizeText(12 * sortType.size());

        text.setPosition(position.x + (size.x)/2 - pxSizeText/2, size.y - 30);

        target.draw(text);


        sf::RectangleShape marginUp = sf::RectangleShape();
        marginUp.setPosition(sf::Vector2f(position.x + margin / 2, margin / 2));
        marginUp.setSize(sf::Vector2f(size.x - margin, thickness));
        target.draw(marginUp);

        sf::RectangleShape marginLeft = sf::RectangleShape();
        marginLeft.setPosition(sf::Vector2f(position.x + margin / 2, margin / 2));
        marginLeft.setSize(sf::Vector2f(thickness, size.x - margin));
        target.draw(marginLeft);

        sf::RectangleShape marginRight = sf::RectangleShape();
        marginRight.setPosition(sf::Vector2f(position.x + size.x - margin / 2, margin / 2));
        marginRight.setSize(sf::Vector2f(thickness, size.x - margin));
        target.draw(marginRight);

        std::vector<sf::RectangleShape> rectangles = valuesToRectangles();
        for (int i(0); i < rectangles.size(); i++) {
            target.draw(rectangles[i]);
        }
    }
    std::vector<sf::RectangleShape> valuesToRectangles() const;
    float factorToMaximize(float actual, float max) const;
    void drawFromVector(sf::RenderWindow& window, std::vector<sf::RectangleShape> vector);
    const std::thread& getThread() const;

    void detach();
};


#endif //SORTVISUALIZER_SORTVISUALIZER_H
