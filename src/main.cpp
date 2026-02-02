#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/logo.png"};
    for (int x{0}; x < image.width(); x++)
{
    for (int y{0}; y < image.height(); y++)
    {
        image.pixel(x, y).r = 0.f;
        image.pixel(x, y).b = 0.f;
    }
}
    // TODO: modifier l'image
    image.save("output/pouet.png");
}