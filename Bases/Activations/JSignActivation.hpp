class JSignActivation : public JActivation
{
public:
  double Calculate(double x)
  {
    if (x < 0)
      return 0;
    return 1;
  }

  double Derivate(double x)
  {
    return 0;
  }
};
