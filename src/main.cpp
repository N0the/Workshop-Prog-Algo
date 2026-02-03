#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>
#include <string>

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
    int const glitchFactor = 400;
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
            }
        }
    }
}

void PixelSorting(sil::Image &image)
{

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 0.f;
            image.pixel(x, y).b = 0.f;
        }
    }
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
}