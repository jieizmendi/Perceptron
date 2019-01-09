/****************************************************************************
 * JLayer
****************************************************************************/
/************************
 * Constructors
************************/
JLayer::JLayer(size_t _id, size_t _inputsSize, size_t _layerSize, JActivation *activation)
{
    id = _id;
    layerSize = _layerSize;
    inputsSize = _inputsSize;

    activationFunction = std::bind(&JActivation::Calculate, activation, std::placeholders::_1);
    activationDerivatedFunction = std::bind(&JActivation::Derivate, activation, std::placeholders::_1);

    //Init
    inputs.resize(inputsSize);
    outputs.resize(layerSize);
    weights.resize(inputsSize, layerSize);
    biases.resize(layerSize);
    sums.resize(layerSize);
    errorsTerms.resize(layerSize);
}

/************************
 * Sets
************************/
void JLayer::InitWeight(std::function<double()> f)
{
    biases.Fill(f);
    weights.Fill(f);
}

/************************
 * Gets
************************/
JVector<double> JLayer::GetOutput()
{
    return outputs;
}

JVector<double> *JLayer::GetErrorsTerms()
{
    return &errorsTerms;
}

JVector<double> JLayer::GetErrorsFactors()
{
    JVector<double> result(inputsSize);

    for (size_t i = 0; i < inputsSize; i++)
        result.at(i) = (errorsTerms * weights.row(i)).Summation();

    return result;
}

double JLayer::GetSquareError(JVector<double> *targets)
{
    JVector<double> a = (*targets - outputs);
    a *= a;
    return a.Summation() / 2;
}

/************************
 * Run
************************/
JVector<double> JLayer::Run(JVector<double> _inputs)
{
    //Inits
    inputs = _inputs;
    //sums.Fill(0.0);

    //Summation
    sums = biases;

    for (size_t i = 0; i < layerSize; i++)
        sums.at(i) += (weights.col(i) * inputs).Summation();

    //Activation
    outputs = sums.OnFunction(activationFunction);
    /*
    inputs.ConsolePrint("Inputs at " + std::to_string(id));
    weights.ConsolePrint("Weights at " + std::to_string(id));
    biases.ConsolePrint("Biases at " + std::to_string(id));
    sums.ConsolePrint("Sums at " + std::to_string(id));
    outputs.ConsolePrint("Outputs at " + std::to_string(id));
*/
    return outputs;
}

/****************
 * Training 
****************/
void JLayer::UpdateWeight(double lr)
{
    //errorsTerms.ConsolePrint("errorsTerms At " + std::to_string(id));
    //inputs.ConsolePrint("inputs At " + std::to_string(id));
    //weights.ConsolePrint("Old Weights At " + std::to_string(id));
    for (size_t i = 0; i < inputsSize; i++)
    {
        for (size_t j = 0; j < layerSize; j++)
        {
            weights.at(i, j) += errorsTerms.at(j) * inputs.at(i) * lr;
        }
    }

    //biases.ConsolePrint("OLD biases AT " + std::to_string(id));
    for (size_t i = 0; i < layerSize; i++)
    {
        biases.at(i) += errorsTerms.at(i) * lr;
    }
    //biases.ConsolePrint("NEW biases AT " + std::to_string(id));

    //weights.ConsolePrint("NEW Weights At " + std::to_string(id));
}

/****************************************************************************
 * JLayerHidden
****************************************************************************/
JLayerHidden::JLayerHidden(size_t _id, size_t _inputsSize, size_t _layerSize, JActivation *activation) : JLayer(_id, _inputsSize, _layerSize, activation)
{
}

void JLayerHidden::ErrorsTerms(JVector<double> *factors)
{
    errorsTerms = sums.OnFunction(activationDerivatedFunction) * (*factors);
}
/****************************************************************************
 * JLayerOutput
****************************************************************************/
JLayerOutput::JLayerOutput(size_t _id, size_t _inputsSize, size_t _layerSize, JActivation *activation) : JLayer(_id, _inputsSize, _layerSize, activation)
{
}

void JLayerOutput::ErrorsTerms(JVector<double> *targets)
{
    errorsTerms = sums.OnFunction(activationDerivatedFunction) * ((*targets) - outputs);
}