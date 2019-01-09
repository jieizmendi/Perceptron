class JSigmoidActivation : public JActivation
{
  public:
    JSigmoidActivation() {}

    double Calculate(double x)
    {
        double exp_value;
        exp_value = std::exp((double)-x);

        return 1 / (1 + exp_value);
    }

    double Derivate(double x)
    {
        double y = Calculate(x);
        return y * (1 - y);
    }
};