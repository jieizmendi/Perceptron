// g++ -std=c++11 main.cpp -o app -lsfml-graphics -lsfml-window -lsfml-system
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Bases/TextTable.h"
#include "Bases/Alg/JRandom.hpp"
#include "Bases/Alg/JVector.hpp"
#include "Bases/Alg/JMatrix.hpp"
#include "Bases/Activations/JActivation.hpp"
#include "Bases/Activations/JFastSigmoidActivation.hpp"
#include "Bases/Activations/JSignActivation.hpp"
#include "Bases/Activations/JSigmoidActivation.hpp"
#include "Bases/JPlotter.hpp"
#include "Perceptron/JLayer.hpp"
#include "Perceptron/JPerceptron.hpp"

//Display Sizes
#define WIDTH 600
#define HEIGHT 600

double ecuation(double x)
{
    //return 0.2 * x + 0.3;
    /*
    
    if (x > 0.0)
        return std::sqrt(x) - 0.15;
    return x * x * x - 0.15;
    */
    //return std::sqrt(0.5*0.5-x*x);
}

double l1(double x)
{
    return x + 0.35;
}

double l2(double x)
{
    return x - 0.35;
}

double sq1(double x)
{
    return std::sqrt(x + 0.3);
}

double sq2(double x)
{
    return -std::sqrt(x + 0.3);
}

int main()
{
    JRandom rd(-1.0, 1.0);

    JMatrix<double> points(500, 2);
    JMatrix<double> targets(500, 2);
    for (int i = 0; i < 500; i++)
    {
        points.at(i, 0) = rd();
        points.at(i, 1) = rd();
        /*
        targets.at(i, 0) = (ecuation(points.at(i, 0)) < points.at(i, 1) ? 1.0 : 0.0);
        targets.at(i, 1) = (ecuation(points.at(i, 0)) >= points.at(i, 1) ? 0.0 : 1.0);
        */
        /*
        if ((points.at(i, 1) < l1(points.at(i, 0))) && (points.at(i, 1) > l2(points.at(i, 0))))
        {
            targets.at(i, 0) = 1.0;
            targets.at(i, 1) = 0.0;
        }
        else
        {
            targets.at(i, 0) = 0.0;
            targets.at(i, 1) = 1.0;
        }
        */

        targets.at(i, 0) = 1.0;
        targets.at(i, 1) = 0.0;
        if (points.at(i, 0) > -0.3)
        {
            if (points.at(i, 1) >= 0)
            {
                if (points.at(i, 1) < sq1(points.at(i, 0)))
                {
                    targets.at(i, 0) = 0.0;
                    targets.at(i, 1) = 1.0;
                }
            }

            if (points.at(i, 1) < 0)
            {
                if (points.at(i, 1) > sq2(points.at(i, 0)))
                {
                    targets.at(i, 0) = 0.0;
                    targets.at(i, 1) = 1.0;
                }
            }
        }
    }

    //Perceptron
    JSigmoidActivation *jsa = new JSigmoidActivation();
    JMatrix<double> outputs;
    JPerceptron jp(0.1);

    jp.AddLayer(LayerType::Input, 2);
    jp.AddLayer(LayerType::Hidden, 16, jsa);
    jp.AddLayer(LayerType::Hidden, 8, jsa);
    jp.AddLayer(LayerType::Hidden, 4, jsa);
    jp.AddLayer(LayerType::Output, 2, jsa);

    jp.InitRandom(rd);

    //View
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 800), "Perceptron Multicapa");
    JPlotter ploter(800, 800, window);
    while (window->isOpen())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        //Windows Events
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        //Training
        outputs = jp.Train(points, targets);

        //Draw
        window->clear();

        //Points
        sf::Color resultColor;
        for (int i = 0; i < outputs.RowsSize(); i++)
        {
            resultColor = sf::Color::Red;
            if ((std::abs(outputs.at(i, 0) - targets.at(i, 0)) < 0.2) &&
                (std::abs(outputs.at(i, 1) - targets.at(i, 1)) < 0.2))
            {
                if (targets.at(i, 0) == 0)
                    resultColor = sf::Color::Green;
                else
                    resultColor = sf::Color::Blue;
            }

            ploter.PlotPoint(points.at(i, 0), points.at(i, 1), resultColor);
        }
        //ploter.PlotPoint(0, 0, sf::Color::Red);

        //Ecuation
        //ploter.PlotFunction(ecuation, sf::Color::White);
        //ploter.PlotFunction(l1, sf::Color::White);
        //ploter.PlotFunction(l2, sf::Color::White);
        ploter.PlotFunction(sq1, sf::Color::White);
        ploter.PlotFunction(sq2, sf::Color::White);

        window->display();
    }

    return 0;
}
