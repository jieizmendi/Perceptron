class JRandom
{
  public:
    JRandom(double low, double high)
        : r(std::bind(std::uniform_real_distribution<>(low, high), std::default_random_engine(time(0)))) {}

    double operator()() { return r(); }

  private:
    std::function<double()> r;
};