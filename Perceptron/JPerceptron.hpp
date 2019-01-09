//#include <bits/stdc++.h>
//#include "JVector.hpp"
//#include "JMatrix.hpp"
//#include "JPlotter.hpp"
//#include "JActivation.hpp"
//#include "JLayer.hpp"
//#include "JRandom.hpp"

class JPerceptron
{
    JVector<JLayer *> layers;
    double previousSize;

    double learnRate;

  public:
    JPerceptron(double _learnRate)
    {
        learnRate = _learnRate;
        previousSize = 0;
    }

    void AddLayer(LayerType layerType, size_t size, JActivation *activation = NULL)
    {
        if (layerType == LayerType::Hidden)
        {
            layers.push_back(new JLayerHidden(layers.size(), previousSize, size, activation));
        }

        if (layerType == LayerType::Output)
        {
            layers.push_back(new JLayerOutput(layers.size(), previousSize, size, activation));
        }
        previousSize = size;
    }

    void InitRandom(std::function<double()> f)
    {
        for (size_t i = 0; i < layers.size(); i++)
            layers.at(i)->InitWeight(f);
        //it->InitWeight(f);
    }

    JVector<double> Run(JVector<double> inputs)
    {
        for (size_t i = 0; i < layers.size(); i++)
            inputs = layers.at(i)->Run(inputs);

        return inputs;
    }

    JMatrix<double> Train(JMatrix<double> inputs, JMatrix<double> targets)
    {
        JMatrix<double> results(targets.RowsSize(), targets.ColsSize());
        JVector<double> a;

        for (int i = 0; i < inputs.RowsSize(); i++)
        {
            a = this->Train(inputs.row(i), targets.row(i));
            for (int j = 0; j < a.size(); j++)
                results.at(i, j) = a.at(j);
        }

        return results;
    }

    JVector<double> Train(JVector<double> inputs, JVector<double> targets)
    {
        JVector<double> factors, outputs = this->Run(inputs);

        //Errors Terms
        layers.at(layers.size() - 1)->ErrorsTerms(&targets);
        for (int i = layers.size() - 2; i >= 0; i--)
        {
            factors = layers.at(i + 1)->GetErrorsFactors();
            layers.at(i)->ErrorsTerms(&factors);
        }

        //Weight Update
        for (size_t i = 0; i < layers.size(); i++)
            layers.at(i)->UpdateWeight(learnRate);

        return outputs;
        //return (std::abs(targets.at(0) - outputs.at(0)) < 0.2);
        //return ((std::abs(targets.at(0) - outputs.at(0)) < 0.5) && (std::abs(targets.at(1) - outputs.at(1)) < 0.5));
    }
};

#include "JPerceptron.cpp"
