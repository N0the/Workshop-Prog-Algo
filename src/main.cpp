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
            int randomWidth = random_int(0, image.width());
            int randomHeight = random_int(0, image.height());
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
            int offset = 30;
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
    float power = 2.0;
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
    int taille = 4;
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
    float taille = 4;
    // Taille du cercle intérieur
    float thickness = 4.5;
    // Rayon du cercle extérieur
    float rayon1 = image.width() / taille;
    // Rayon du cercle intérieur
    float rayon2 = image.width() / thickness;

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
    int size = 500;
    // Taille du cercle extérieur
    float taille = 4;
    // Taille du cercle intérieur
    float rayon1 = size / taille;

    int numberImage = 0;
    for (int images = 0; images < size; images++)
    {
        sil::Image image{500, 500};

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

int main()
{
    // Seed pour l'aléatoire
    set_random_seed(0);

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
}