#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm> //std::sort
#include <complex>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <vector>

void greenImage(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 0.f;
            image.pixel(x, y).b = 0.f;
        }
    }
};

void switchCanal(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y).r, image.pixel(x, y).b);
        }
    }
};

void BlackAndWhite(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float red = image.pixel(x, y).r;
            float blue = image.pixel(x, y).b;
            float green = image.pixel(x, y).g;

            float luminance = 0.2126 * red + 0.7152 * green + 0.0722 * blue;
            image.pixel(x, y).r = luminance;
            image.pixel(x, y).b = luminance;
            image.pixel(x, y).g = luminance;
        }
    }
}

void Negatif(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float red = 1 - image.pixel(x, y).r;
            float blue = 1 - image.pixel(x, y).b;
            float green = 1 - image.pixel(x, y).g;

            image.pixel(x, y).r = red;
            image.pixel(x, y).b = blue;
            image.pixel(x, y).g = green;
        }
    }
}

sil::Image Gradient()
{
    sil::Image image{300, 200};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float gradientvalue = static_cast<float>(x) / (image.width());
            image.pixel(x, y).r = gradientvalue;
            image.pixel(x, y).b = gradientvalue;
            image.pixel(x, y).g = gradientvalue;
        }
    }
    return image;
}

void Mirror(sil::Image &image)
{
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int xSwitch = image.width() - 1 - x;
            float redOld = image.pixel(x, y).r;
            float greenOld = image.pixel(x, y).g;
            float blueOld = image.pixel(x, y).b;

            float red = image.pixel(xSwitch, y).r;
            float green = image.pixel(xSwitch, y).g;
            float blue = image.pixel(xSwitch, y).b;

            image.pixel(x, y).r = red;
            image.pixel(x, y).g = green;
            image.pixel(x, y).b = blue;

            image.pixel(xSwitch, y).r = redOld;
            image.pixel(xSwitch, y).g = greenOld;
            image.pixel(xSwitch, y).b = blueOld;
        }
    }
}

void Noise(sil::Image &image)
{
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int randomWidth = random_int(0, image.width() - 1);
            int randomHeight = random_int(0, image.height() - 1);
            float randomRed = random_float(0.0, 1.0);
            float randomBlue = random_float(0.0, 1.0);
            float randomGreen = random_float(0.0, 1.0);

            image.pixel(randomWidth, randomHeight).r = randomRed;
            image.pixel(randomWidth, randomHeight).g = randomGreen;
            image.pixel(randomWidth, randomHeight).b = randomBlue;
        }
    }
}

sil::Image Rotate90(sil::Image &image)
{
    // Etant donné que l'on tourne à 90 degré, la largeur devient la hauteur et inversement
    sil::Image new_image{image.height(), image.width()};

    for (int x{0}; x < image.height(); x++)
    {
        for (int y{0}; y < image.width(); y++)
        {
            new_image.pixel(x, y) = image.pixel(y, image.height() - 1 - x);
        }
    }
    return new_image;
}

sil::Image RGBSplit(sil::Image &image)
{
    sil::Image new_image = image;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            // Decalage des couleurs
            int const offset = 30;
            int xr = x - offset;
            int xb = x + offset;
            if (xr <= 0)
            {
                xr = image.width() - 1;
            }
            if (xb >= image.width())
            {
                xb = x;
            }
            new_image.pixel(x, y).r = image.pixel(xr, y).r;
            new_image.pixel(x, y).g = image.pixel(x, y).g;
            new_image.pixel(x, y).b = image.pixel(xb, y).b;
        }
    }
    return new_image;
}

void Lighting(sil::Image &image)
{
    float const power = 2.0;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float redLight = std::pow(image.pixel(x, y).r, 1.0 / power);
            float greenLight = std::pow(image.pixel(x, y).g, 1.0 / power);
            float blueLight = std::pow(image.pixel(x, y).b, 1.0 / power);

            float redDark = std::pow(image.pixel(x, y).r, power);
            float greenDark = std::pow(image.pixel(x, y).g, power);
            float blueDark = std::pow(image.pixel(x, y).b, power);

            // Eclaircir

            // image.pixel(x, y).r = redLight;
            // image.pixel(x, y).g = greenLight;
            // image.pixel(x, y).b = blueLight;

            // Assombrir

            image.pixel(x, y).r = redDark;
            image.pixel(x, y).g = greenDark;
            image.pixel(x, y).b = blueDark;
        }
    }
}

sil::Image Disque()
{
    sil::Image image{500, 500};
    // On peut changer la valeur de la taille pour changer la taille du disque, plus on augmente, plus il est petit
    int const taille = 4;
    float rayon = image.width() / taille;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float xCoordinate = x - (image.width() / 2);
            float yCoordinate = y - (image.height() / 2);
            // Jsp pourquoi le ^ 2 ne marche pas
            if (xCoordinate * xCoordinate + yCoordinate * yCoordinate <= rayon * rayon)
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
    return image;
}

sil::Image Cercle()
{
    sil::Image image{500, 500};
    // Taille du cercle extérieur
    float const thickness = 4;
    // Taille du cercle intérieur
    float const taille = thickness + 0.5;
    // Rayon du cercle extérieur
    float const rayon1 = image.width() / thickness;
    // Rayon du cercle intérieur
    float const rayon2 = image.width() / taille;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float xCoordinate = x - (image.width() / 2);
            float yCoordinate = y - (image.height() / 2);
            // Jsp pourquoi le ^ 2 ne marche pas
            if (xCoordinate * xCoordinate + yCoordinate * yCoordinate <= rayon1 * rayon1)
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;

                if (xCoordinate * xCoordinate + yCoordinate * yCoordinate <= rayon2 * rayon2)
                {

                    image.pixel(x, y).r = 0.f;
                    image.pixel(x, y).g = 0.f;
                    image.pixel(x, y).b = 0.f;
                }
            }
        }
    }
    return image;
}

void Animation()
{
    int const size = 500;
    // Taille de l'image
    float taille = 4;
    // Taille du cercle
    float rayon1 = size / taille;
    // Incrément du nombre d'image
    int numberImage = 0;
    int const increment = size / 50;
    for (int images = 0; images < size; images += increment)
    {
        sil::Image image{size, size};

        float move = images - size / 2;

        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                float xCoordinate = x - (size / 2 + move);
                float yCoordinate = y - (size / 2);
                // Jsp pourquoi le ^ 2 ne marche pas
                if (xCoordinate * xCoordinate + yCoordinate * yCoordinate <= rayon1 * rayon1)
                {
                    image.pixel(x, y).r = 1.f;
                    image.pixel(x, y).g = 1.f;
                    image.pixel(x, y).b = 1.f;
                }
            }
        }
        image.save("output/animation/Animation_" + std::to_string(numberImage) + ".jpg");
        numberImage++;
    }
}

sil::Image Rosace()
{
    sil::Image image{500, 500};
    // Epaisseur du trait
    float const thickness = 2;
    // Rayon du cercle
    float const rayon = image.width() / 4;

    float const pi = 3.141592653589793f;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            // On centre le cercle
            float xCoordinate = x - (image.width() / 2);
            float yCoordinate = y - (image.height() / 2);

            bool draw = false;

            // Cercle central
            float distanceCentre = std::sqrt(xCoordinate * xCoordinate + yCoordinate * yCoordinate);

            // Condition qui permet de dessiner le cercle en fonction de l'épaisseur
            if (std::abs(distanceCentre - rayon) < thickness)
            {
                draw = true;
            }

            // Cercle répété autour
            for (int i{0}; i < 6; i++)
            {
                // On incrémente pour faire le tour complet d'un cercle => 2pi
                float angle = i * pi / 3;
                float xRayon = rayon * cos(angle);
                float yRayon = rayon * sin(angle);
                // Distance entre le point du milieu et celui présent sur le cercle
                float xDistance = xCoordinate - xRayon;
                float yDistance = yCoordinate - yRayon;

                // Cercle qui va être répété, même formule que celui du centre
                float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);
                // Condition qui permet de dessiner le cercle en fonction de l'épaisseur
                if (std::abs(distance - rayon) < thickness)
                {
                    draw = true;
                }
                if (draw)
                {
                    image.pixel(x, y).r = 1.f;
                    image.pixel(x, y).g = 1.f;
                    image.pixel(x, y).b = 1.f;
                }
            }
        }
    }
    return image;
}

sil::Image Mosaique(sil::Image &image)
{
    int const multiply = 5;
    sil::Image imageFinal{image.width() * multiply, image.height() * multiply};
    for (int i = 0; i < multiply; i++)
    {
        for (int j = 0; j < multiply; j++)
        {
            for (int x = 0; x < image.width(); x++)
            {
                for (int y = 0; y < image.height(); y++)
                {
                    imageFinal.pixel(
                        x + i * image.width(),
                        y + j * image.height()) = image.pixel(x, y);
                }
            }
        }
    }

    return imageFinal;
}

sil::Image MosaiqueMirroir(sil::Image &image)
{
    int const multiply = 5;
    sil::Image imageFinal{
        image.width() * multiply,
        image.height() * multiply};

    for (int i = 0; i < multiply; ++i)
    {
        for (int j = 0; j < multiply; ++j)
        {
            for (int x = 0; x < image.width(); ++x)
            {
                for (int y = 0; y < image.height(); ++y)
                {
                    int trueX = x;
                    int trueY = y;
                    if (i % 2 == 1)
                    {
                        trueX = image.width() - 1 - x;
                    }
                    if (j % 2 == 1)
                    {
                        trueY = image.height() - 1 - y;
                    }

                    imageFinal.pixel(
                        x + i * image.width(),
                        y + j * image.height()) = image.pixel(trueX, trueY);
                }
            }
        }
    }

    return imageFinal;
}

void Glitch(sil::Image &image)
{
    int const glitchFactor = 500;
    int const minWidth = 0;
    int const minHeight = 0;
    int const maxWidth = (image.width() - 1) / 10;
    int const maxHeight = (image.height() - 1) / 30;

    for (int k = 0; k < glitchFactor; k++)
    {
        int randomWidth = random_int(0, image.width() - 1);
        int randomHeight = random_int(0, image.height() - 1);

        int glitchWidth = random_int(minWidth, maxWidth);
        int glitchHeight = random_int(minHeight, maxHeight);

        if (
            randomWidth + glitchWidth >= image.width() || randomHeight + glitchHeight >= image.height())
        {
            continue;
        }
        for (int x = 0; x < glitchWidth; x++)
        {
            for (int y = 0; y < glitchHeight; y++)
            {
                image.pixel(randomWidth + x, randomHeight + y) = image.pixel(randomWidth, randomHeight);
                int glitchWidth = random_int(minWidth, maxWidth);
                int glitchHeight = random_int(minHeight, maxHeight);

                if (
                    randomWidth + glitchWidth >= image.width() || randomHeight + glitchHeight >= image.height())
                {
                    continue;
                }
            }
        }
    }
}

void PixelSorting(sil::Image &image)
{
    int const pixelSortingFactor = 1000;
    int width = image.width();
    int height = image.height();
    std::vector<glm::vec3> &pixels = image.pixels();

    for (int k = 0; k < pixelSortingFactor; ++k)
    {

        int maxRectWidth = width / 5;
        int maxRectHeight = height / 100;
        int rectWidth = random_int(1, maxRectWidth);
        int rectHeight = random_int(1, maxRectHeight);
        int randomX = random_int(0, width - 1);
        int randomY = random_int(0, height - 1);

        if (randomX + rectWidth >= width)
            rectWidth = width - randomX;
        if (randomY + rectHeight >= height)
            rectHeight = height - randomY;

        for (int y = 0; y < rectHeight; ++y)
        {
            randomX = random_int(0, width - 1);
            randomY = random_int(0, height - 1);
            auto row_begin = pixels.begin() + (randomY + y) * width + randomX;
            auto row_end = row_begin + rectWidth;

            std::sort(row_begin, row_end,
                      [](const glm::vec3 &a, const glm::vec3 &b)
                      {
                          // Tri sur la luminance
                          float lumA = 0.2126 * a.r + 0.7152 * a.g + 0.0722 * a.b;
                          float lumB = 0.2126 * b.r + 0.7152 * b.g + 0.0722 * b.b;
                          return lumA < lumB;
                      });
        }
    }
}

sil::Image MandelBrot()
{
    int const size = 500;
    int const iteration = 50;
    int const width = size;
    int const height = size;
    float const intervalMin = -2;
    float const intervalMax = 2;

    sil::Image image{width, height};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::complex<float> z{0., 0.};
            int i = 0;
            float reel = intervalMin + (x / float(size - 1)) * (intervalMax - intervalMin);
            float imaginaire = intervalMin + (y / float(size - 1)) * (intervalMax - intervalMin);
            std::complex<float> c{reel, imaginaire};

            while (std::abs(z) < 2 && i < iteration)
            {
                z = z * z + c;
                i++;
                image.pixel(x, y).r = static_cast<float>(i) / static_cast<float>(iteration);
                image.pixel(x, y).g = static_cast<float>(i) / static_cast<float>(iteration);
                image.pixel(x, y).b = static_cast<float>(i) / static_cast<float>(iteration);
            }
            if (i == iteration)
            {
                image.pixel(x, y).r = 1.0;
                image.pixel(x, y).g = 1.0;
                image.pixel(x, y).b = 1.0;
            }
        }
    }
    return image;
}

// Ces deux fonctions sont utilisé pour l'exercice du Oklab
float sRGB_to_linear(float color)
{
    if (color <= 0.04045f)
        return color / 129.f;
    else
        return std::pow((color + 0.055f) / 1.055f, 2.4f);
}
float linear_to_sRGB(float color)
{
    if (color <= 0.0031308f)
        return 12.92f * color;
    else
        return 1.055f * std::pow(color, 1.0f / 2.4f) - 0.055f;
}

sil::Image GradientLab()
{
    sil::Image image{300, 200};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {

            // Couleurs de base
            float R_sRGB = 1 - static_cast<float>(x) / image.width();
            float G_sRGB = static_cast<float>(x) / image.width();
            float B_sRGB = static_cast<float>(x) / image.width() * 2;

            // Conversion sRGB à linear sRGB
            float R_lin = sRGB_to_linear(R_sRGB);
            float G_lin = sRGB_to_linear(G_sRGB);
            float B_lin = sRGB_to_linear(B_sRGB);

            // Conversion linear sRGB Oklab
            float l = 0.4122214708f * R_lin + 0.5363325363f * G_lin + 0.0514459929f * B_lin;
            float m = 0.2119034982f * R_lin + 0.6806995451f * G_lin + 0.1073969566f * B_lin;
            float s = 0.0883024619f * R_lin + 0.2817188376f * G_lin + 0.6299787005f * B_lin;

            float l_ = std::cbrt(l);
            float m_ = std::cbrt(m);
            float s_ = std::cbrt(s);

            float L = 0.2104542553f * l_ + 0.7936177850f * m_ - 0.0040720468f * s_;
            float a = 1.9779984951f * l_ - 2.4285922050f * m_ + 0.4505937099f * s_;
            float b = 0.0259040371f * l_ + 0.7827717662f * m_ - 0.8086757660f * s_;

            // Conversion Oklam linear RGB
            float l2 = L + 0.3963377774f * a + 0.2158037573f * b;
            float m2 = L - 0.1055613458f * a - 0.0638541728f * b;
            float s2 = L - 0.0894841775f * a - 1.2914855480f * b;

            l2 = std::pow(l2, 3.);
            m2 = std::pow(m2, 3.);
            s2 = std::pow(s2, 3.);

            R_lin = 4.0767416621f * l2 - 3.3077115913f * m2 + 0.2309699292f * s2;
            G_lin = -1.2684380046f * l2 + 2.6097574011f * m2 - 0.3413193965f * s2;
            B_lin = -0.0041960863f * l2 - 0.7034186147f * m2 + 1.7076147010f * s2;

            // Conversion linear rgb to SRGB

            R_sRGB = std::max(0.f, std::min(1.f, linear_to_sRGB(R_lin)));
            G_sRGB = std::max(0.f, std::min(1.f, linear_to_sRGB(G_lin)));
            B_sRGB = std::max(0.f, std::min(1.f, linear_to_sRGB(B_lin)));
            // Ne pas sortir du scope du sRGB (entre 0 et 1 en float)

            image.pixel(x, y).r = R_sRGB;
            image.pixel(x, y).g = G_sRGB;
            image.pixel(x, y).b = B_sRGB;
        }
    }
    return image;
}

void TramageV1(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float red = image.pixel(x, y).r;
            float blue = image.pixel(x, y).b;
            float green = image.pixel(x, y).g;

            float luminance = 0.2126 * red + 0.7152 * green + 0.0722 * blue;

            if (static_cast<int>(luminance * 10) % 2 == 0)
            {
                luminance = 1.0;
            }
            else
            {
                luminance = 0.0;
            }
            image.pixel(x, y).r = luminance;
            image.pixel(x, y).b = luminance;
            image.pixel(x, y).g = luminance;
        }
    }
}

void TramageV2(sil::Image &image)
{
    const int bayer_n = 4;
    float bayer_matrix_4x4[][bayer_n] = {
        {-0.5, 0, -0.375, 0.125},
        {0.25, -0.25, 0.375, -0.125},
        {-0.3125, 0.1875, -0.4375, 0.0625},
        {0.4375, -0.0625, 0.3125, -0.1875},
    };
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float red = image.pixel(x, y).r;
            float blue = image.pixel(x, y).b;
            float green = image.pixel(x, y).g;
            float luminance = 0.2126 * red + 0.7152 * green + 0.0722 * blue;

            float bayer_value = bayer_matrix_4x4[x % bayer_n][y % bayer_n];
            float output_color = luminance + bayer_value; // ajuste la luminance

            output_color = std::max(0.f, std::min(1.f, output_color));
            if (output_color < 0.5f)
                output_color = 0.f; // noir
            else
                output_color = 1.f;

            image.pixel(x, y).r = output_color;
            image.pixel(x, y).g = output_color;
            image.pixel(x, y).b = output_color;
        }
    }
}

void Normalisation(sil::Image &image)
{
    float minL = 1.;
    float maxL = 0.;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float red = image.pixel(x, y).r;
            float blue = image.pixel(x, y).b;
            float green = image.pixel(x, y).g;
            float luminance = 0.2126 * red + 0.7152 * green + 0.0722 * blue;

            if (minL > luminance)
            {
                minL = luminance;
            }

            if (maxL < luminance)
            {
                maxL = luminance;
            }
        }
    }

    for (int x2{0}; x2 < image.width(); x2++)
    {
        for (int y2{0}; y2 < image.height(); y2++)
        {
            float red = image.pixel(x2, y2).r;
            float green = image.pixel(x2, y2).g;
            float blue = image.pixel(x2, y2).b;
            float luminance = 0.2126 * red + 0.7152 * green + 0.0722 * blue;

            // si on a la plus petite luminance, alors on a zero, et si on a la plus grand luminance, on a 1
            float normalise = (luminance - minL) / (maxL - minL);

            if (luminance > 0.f)
            {
                float k = normalise / luminance;
                image.pixel(x2, y2).r *= k;
                image.pixel(x2, y2).g *= k;
                image.pixel(x2, y2).b *= k;
            }
            else
            {
                image.pixel(x2, y2).r = 0.f;
                image.pixel(x2, y2).g = 0.f;
                image.pixel(x2, y2).b = 0.f;
            }
        }
    }
}

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

void Vortex(sil::Image &image)
{
    float const pi = 3.141592653589793;
    glm::vec2 center{image.width() / 2.f, image.height() / 2.f};
    float max_distance = 20;
    sil::Image original = image;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            glm::vec2 current_pos{x, y};
            float distance = glm::distance(current_pos, center);

            float angle = (distance / max_distance) * pi / 2.f;

            glm::vec2 source = rotated(current_pos, center, angle);

            int src_x = int(source.x);
            int src_y = int(source.y);

            if (src_x >= 0 && src_x < image.width() && src_y >= 0 && src_y < image.height())
            {
                image.pixel(x, y) = original.pixel(src_x, src_y);
            }
        }
    }
}

sil::Image Convolution(sil::Image &image, std::vector<std::vector<float>> kernel)
{
    sil::Image imageFinal = image;
    int tailleNoyau = kernel.size();
    int offset = tailleNoyau / 2;
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            float sum_r = 0.f;
            float sum_g = 0.f;
            float sum_b = 0.f;

            for (int kx = 0; kx < tailleNoyau; kx++)
            {
                for (int ky = 0; ky < tailleNoyau; ky++)
                {
                    int nx = std::clamp(x + kx - offset, 0, image.width() - 1);
                    int ny = std::clamp(y + ky - offset, 0, image.height() - 1);

                    sum_r += image.pixel(nx, ny).r * kernel[kx][ky];
                    sum_g += image.pixel(nx, ny).g * kernel[kx][ky];
                    sum_b += image.pixel(nx, ny).b * kernel[kx][ky];
                }
            }

            imageFinal.pixel(x, y).r = sum_r;
            imageFinal.pixel(x, y).g = sum_g;
            imageFinal.pixel(x, y).b = sum_b;
        }
    }

    return imageFinal;
}
sil::Image FiltreSeparable(sil::Image &image, std::vector<std::vector<float>> kernel)
{
    int tailleNoyau = kernel.size();
    int offset = tailleNoyau / 2;
    std::vector<float> kernelX(tailleNoyau);
    std::vector<float> kernelY(tailleNoyau);

    for (int i = 0; i < tailleNoyau; ++i)
    {
        kernelX[i] = kernel[0][i];
        kernelY[i] = kernel[i][0];
    }
    sil::Image imageTemp{image.width(), image.height()};
    for (int y = 0; y < image.height(); y++)
    {
        for (int x = 0; x < image.width(); x++)
        {
            float sum_r = 0.f, sum_g = 0.f, sum_b = 0.f;

            for (int kx = 0; kx < tailleNoyau; kx++)
            {
                int nx = std::clamp(x + kx - offset, 0, image.width() - 1);

                sum_r += image.pixel(nx, y).r * kernelX[kx];
                sum_g += image.pixel(nx, y).g * kernelX[kx];
                sum_b += image.pixel(nx, y).b * kernelX[kx];
            }

            imageTemp.pixel(x, y).r = sum_r;
            imageTemp.pixel(x, y).g = sum_g;
            imageTemp.pixel(x, y).b = sum_b;
        }
    }
    for (int y = 0; y < image.height(); y++)
    {
        for (int x = 0; x < image.width(); x++)
        {
            float sum_r = 0.f, sum_g = 0.f, sum_b = 0.f;

            for (int ky = 0; ky < tailleNoyau; ky++)
            {
                int ny = std::clamp(y + ky - offset, 0, image.height() - 1);

                sum_r += imageTemp.pixel(x, ny).r * kernelY[ky];
                sum_g += imageTemp.pixel(x, ny).g * kernelY[ky];
                sum_b += imageTemp.pixel(x, ny).b * kernelY[ky];
            }

            imageTemp.pixel(x, y).r = sum_r;
            imageTemp.pixel(x, y).g = sum_g;
            imageTemp.pixel(x, y).b = sum_b;
        }
    }

    return imageTemp;
}

int main()
{

    {
        sil::Image image{"images/logo.png"};
        greenImage(image);
        image.save("output/greenImage.png");
    }

    {
        sil::Image image{"images/logo.png"};
        switchCanal(image);
        image.save("output/switchCanal.png");
    }

    {
        sil::Image image{"images/logo.png"};
        BlackAndWhite(image);
        image.save("output/BlackAndWhite.png");
    }

    {
        sil::Image image{"images/logo.png"};
        Negatif(image);
        image.save("output/Negatif.png");
    }
    {
        sil::Image image = Gradient();
        image.save("output/Gradient.png");
    }
    {
        sil::Image image{"images/logo.png"};
        Mirror(image);
        image.save("output/Mirror.png");
    }
    {
        sil::Image image{"images/logo.png"};
        Noise(image);
        image.save("output/Noise.png");
    }
    {
        sil::Image image{"images/logo.png"};
        sil::Image new_image = Rotate90(image);
        new_image.save("output/Rotate90.png");
    }
    {
        sil::Image image{"images/logo.png"};
        sil::Image new_image = RGBSplit(image);
        new_image.save("output/RGBSplit.png");
    }
    {
        sil::Image image{"images/photo_faible_contraste.jpg"};
        Lighting(image);
        image.save("output/Lighting.jpg");
    }
    {
        sil::Image image = Disque();
        image.save("output/Disque.png");
    }
    {
        sil::Image image = Cercle();
        image.save("output/Cercle.png");
    }
    {
        sil::Image image = Rosace();
        image.save("output/Rosace.png");
    }
    {
        Animation();
    }
    {
        sil::Image image{"images/logo.png"};
        sil::Image imageFinal = Mosaique(image);
        imageFinal.save("output/Mosaique.png");
    }
    {
        sil::Image image{"images/logo.png"};
        sil::Image imageFinal = MosaiqueMirroir(image);
        imageFinal.save("output/MosaiqueMirroir.png");
    }
    {
        sil::Image image{"images/logo.png"};
        Glitch(image);
        image.save("output/Glitch.png");
    }
    {
        sil::Image image{"images/logo.png"};
        PixelSorting(image);
        image.save("output/PixelSorting.png");
    }
    {
        sil::Image image = MandelBrot();
        image.save("output/MandelBrot.png");
    }
    {
        sil::Image image = GradientLab();
        image.save("output/GradientLab.png");
    }
    {
        sil::Image image{"images/photo_faible_contraste.jpg"};
        TramageV1(image);
        image.save("output/TramageV1.png");
    }
    {
        sil::Image image{"images/photo_faible_contraste.jpg"};
        TramageV2(image);
        image.save("output/TramageV2.png");
    }
    {
        sil::Image image{"images/photo_faible_contraste.jpg"};
        Normalisation(image);
        image.save("output/Normalisation.png");
    }
    {
        sil::Image image{"images/logo.png"};
        Vortex(image);
        image.save("output/Vortex.png");
    }
    {
        sil::Image image{"images/logo.png"};
        std::vector<std::vector<float>> kernel = {{(1 / 9.f), (1. / 9.f), (1. / 9.f)},
                                                  {(1. / 9.f), (1. / 9.f), (1. / 9.f)},
                                                  {(1. / 9.f), (1. / 9.f), (1. / 9.f)}};
        sil::Image imageFinal = Convolution(image, kernel);
        imageFinal.save("output/Convolution.png");
    }
    {
        sil::Image image{"images/logo.png"};
        std::vector<std::vector<float>> kernel = {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}};
        sil::Image imageFinal = Convolution(image, kernel);
        imageFinal.save("output/ConvolutionEmboss.png");
    }
    {
        sil::Image image{"images/logo.png"};
        std::vector<std::vector<float>> kernel = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
        sil::Image imageFinal = Convolution(image, kernel);
        imageFinal.save("output/ConvolutionOutline.png");
    }
    {
        sil::Image image{"images/logo.png"};
        std::vector<std::vector<float>> kernel = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
        sil::Image imageFinal = Convolution(image, kernel);
        imageFinal.save("output/ConvolutionSharpen.png");
    }
    {
        sil::Image image{"images/logo.png"};
        std::vector<std::vector<float>> kernel = {{(1 / 3.f), (1. / 3.f), (1. / 3.f)},
                                                  {(1. / 3.f), 0, 0},
                                                  {(1. / 3.f), 0, 0}};
        sil::Image imageFinal = FiltreSeparable(image, kernel);
        imageFinal.save("output/FiltreSeparable.png");
    }
}