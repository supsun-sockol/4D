#include <SFML/Graphics.hpp>

int main()
{
    int w = 800;
    int h = 600;
    sf::RenderWindow window(sf::VideoMode(w, h), "4D");
    window.setFramerateLimit(60);
    sf::RenderTexture emptyTexture;
    emptyTexture.create(w, h);
    sf::Sprite emptySprite = sf::Sprite(emptyTexture.getTexture());
    sf::Shader shader;
    shader.loadFromFile("/home/supsun/Documents/4D/shader/OutputShader.frag", sf::Shader::Fragment);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.draw(emptySprite, &shader);
        window.display();
    }
    return 0;
}
