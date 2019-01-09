class JFastSigmoidActivation : public JActivation
{
public:
  JFastSigmoidActivation() {}

  double Calculate(double x)
  {
    double y = x;
    if (y < 0)
      y *= -1;
    return x / (1 + y);
  }

  double Derivate(double x)
  {
    if (x < 0)
      x *= -1;
    return 1 / ((1 + x) * (1 + x));
  }

  double SecondDerivate(double &x)
  {
    return 0;
  }
};