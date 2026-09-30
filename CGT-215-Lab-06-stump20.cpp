// CGT-215-Lab-06-stump20.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main() {
  
    string background = "images1/backgrounds/winter.png"; 
    string foreground = "images1/characters/yoda.png";    

    // Load textures from the image file
    Texture backgroundTex;
    if (!backgroundTex.loadFromFile(background)) {
        cout << "Couldn't Load Background Image" << endl;
        return 1;
    }

    Texture foregroundTex;
    if (!foregroundTex.loadFromFile(foreground)) {
        cout << "Couldn't Load Foreground Image" << endl;
        return 1;
    }

    // Copy texture data to sf::Image buffers so pixel manipulation is possible
    Image backgroundImage = backgroundTex.copyToImage();
    Image foregroundImage = foregroundTex.copyToImage();

    Vector2u sz = backgroundImage.getSize();
    Vector2u fgSz = foregroundImage.getSize();

    
    // Dynamically sample the top-left corner pixel (0,0) of the foreground image
    // to identify the green screen key color.
    Color keyColor = foregroundImage.getPixel(0, 0);

    // Iterate through each pixel across the dimensions of the background image
    for (unsigned int y = 0; y < sz.y; y++) {
        for (unsigned int x = 0; x < sz.x; x++) {
            // Ensure sampling stays within bounds of the foreground image
            if (x < fgSz.x && y < fgSz.y) {
                Color fgPixel = foregroundImage.getPixel(x, y);

                // If the foreground pixel matches the green screen key color,
                // replace it with the corresponding pixel from the background image.
                if (fgPixel == keyColor) {
                    Color bgPixel = backgroundImage.getPixel(x, y);
                    foregroundImage.setPixel(x, y, bgPixel);
                }
            }
        }
    }

    // Create the window matching the background image size
    RenderWindow window(VideoMode(sz.x, sz.y), "Composited Output");

    // Upload the composited sf::Image back to a texture for rendering
    Texture compositeTex;
    compositeTex.loadFromImage(foregroundImage);

    Sprite sprite;
    sprite.setTexture(compositeTex);

    // Render function.
    RenderWindow window(VideoMode(1024, 768), "Here's the output");
    Sprite sprite1;
    Texture tex1;
    tex1.loadFromImage(foregroundImage);
    sprite1.setTexture(tex1);
    window.clear();
    window.draw(sprite1);
    window.display();
    while (true);
}