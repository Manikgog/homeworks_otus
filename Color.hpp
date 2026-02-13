#pragma once

#include <fstream>

class Color {
  public:
    Color();
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;

  private:
    double r{};
    double g{};
    double b{};
};

inline std::istream& operator>>(std::istream& is, Color& p) {
  double red;
  double green;
  double blue;
  is >> red >> green >> blue;
  Color color(red, green, blue);
  p = color;
  return is;
}
