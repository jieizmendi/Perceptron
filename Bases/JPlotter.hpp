
class JPlotter
{
    double height, width;
    sf::RenderWindow *window;

    double MapX(double x)
    {
        return (width / 2) + x * (width / 2);
    }

    double MapY(double y)
    {
        return (height / 2) - y * (height / 2);
    }

  public:
    JPlotter(size_t _width, size_t _height, sf::RenderWindow *_window)
    {
        height = _height;
        width = _width;
        window = _window;
    }

    void PlotPoint(double x, double y, sf::Color color)
    {
        double radius = height / 200;
        sf::CircleShape shape(radius);
        shape.setFillColor(color);

        shape.setPosition(this->MapX(x) - radius, this->MapY(y) - radius);
        window->draw(shape);
    }

    void PlotFunction(std::function<double(double)> f, sf::Color color)
    {
        double step = 0.0025;
        sf::VertexArray curve(sf::PrimitiveType::LineStrip, std::ceil(width / step));

        for (double x = -1.0; x <= 1.0; x += step)
        {
            curve.append(sf::Vertex(sf::Vector2f(this->MapX(x), this->MapY(f(x))), color));
        }
        window->draw(curve);
    }
};