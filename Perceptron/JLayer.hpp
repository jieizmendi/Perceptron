enum LayerType
{
    Input,
    Hidden,
    Output
};

class JLayer
{
protected:
  JVector<double> inputs;
  JVector<double> outputs;

  JMatrix<double> weights;

  JVector<double> biases;
  JVector<double> sums;

  JVector<double> errorsTerms;

  std::function<double(double)> activationFunction;
  std::function<double(double)> activationDerivatedFunction;

  size_t layerSize;
  size_t inputsSize;
  size_t id;

public:
  JLayer(size_t, size_t, size_t, JActivation *); // id, inputsSize, layerSize, activation obj
  ~JLayer() {}

  //Sets
  void InitWeight(std::function<double()>);

  //Gets
  JVector<double> GetOutput();
  JVector<double> GetErrorsFactors();
  JVector<double> *GetErrorsTerms();
  double GetSquareError(JVector<double> *); //Targets

  //Output
  JVector<double> Run(JVector<double>);

  //Train
  void UpdateWeight(double);                   //learn rate
  virtual void ErrorsTerms(JVector<double> *) {} //Errorsfactors of next layer
};

class JLayerHidden : public JLayer
{
public:
  JLayerHidden(size_t, size_t, size_t, JActivation *); // id, inputsSize, layerSize, activation obj

  void ErrorsTerms(JVector<double> *); //Errorsfactors of next layer
};

class JLayerOutput : public JLayer
{
public:
  JLayerOutput(size_t, size_t, size_t, JActivation *); // id, inputsSize, layerSize, activation obj

  void ErrorsTerms(JVector<double> *); //Errorsfactors of next layer
};

#include "JLayer.cpp"