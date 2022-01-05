#include <SFML/Graphics.hpp>

int main()
{
    int w = 800;
    int h = 600;
    int cumX = 0;
    int cumY = 0;
    float cumSensitivity = 0.05f;
    float moveSensitivity = 0.1f;
    bool keys[10] = {false, false, false, false, false, false, false, false, false, false};
    sf::Vector3f pos = sf::Vector3f(-5.0f, 0.0f, 0.0f);
    sf::Vector2f cumPos = sf::Vector2f(0.0, 0.0);

    sf::RenderWindow window(sf::VideoMode(w, h), "Ray tracing", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::RenderTexture emptyTexture;
    emptyTexture.create(w, h);
    sf::Sprite emptySprite = sf::Sprite(emptyTexture.getTexture());
    sf::Shader shader;
    shader.loadFromFile("/home/supsun/Documents/4D/shader/OutputShader.frag", sf::Shader::Fragment);
    shader.setUniform("u_resolution", sf::Vector2f(w, h));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            //cumX += event.mouseMove.x - w / 2;
            //cumY += event.mouseMove.y - h / 2;
            else if (event.type == sf::Event::KeyPressed)
            {

                if (event.key.code == sf::Keyboard::W) keys[0] = true;
                else if (event.key.code == sf::Keyboard::A) keys[1] = true;
                else if (event.key.code == sf::Keyboard::S) keys[2] = true;
                else if (event.key.code == sf::Keyboard::D) keys[3] = true;
                else if (event.key.code == sf::Keyboard::R) keys[4] = true;
                else if (event.key.code == sf::Keyboard::F) keys[5] = true;
                else if (event.key.code == sf::Keyboard::Up) keys[6] = true;
                else if (event.key.code == sf::Keyboard::Down) keys[7] = true;
                else if (event.key.code == sf::Keyboard::Left) keys[8] = true;
                else if (event.key.code == sf::Keyboard::Right) keys[9] = true;

            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::W) keys[0] = false;
                else if (event.key.code == sf::Keyboard::A) keys[1] = false;
                else if (event.key.code == sf::Keyboard::S) keys[2] = false;
                else if (event.key.code == sf::Keyboard::D) keys[3] = false;
                else if (event.key.code == sf::Keyboard::R) keys[4] = false;
                else if (event.key.code == sf::Keyboard::F) keys[5] = false;
                else if (event.key.code == sf::Keyboard::Up) keys[6] = false;
                else if (event.key.code == sf::Keyboard::Down) keys[7] = false;
                else if (event.key.code == sf::Keyboard::Left) keys[8] = false;
                else if (event.key.code == sf::Keyboard::Right) keys[9] = false;
            }
        }
        if (keys[0]) pos.x+=1* moveSensitivity;
        else if (keys[2]) pos.x-=1 * moveSensitivity;
        if (keys[3]) pos.y+=1 * moveSensitivity;
        else if (keys[1]) pos.y-=1 * moveSensitivity;
        if (keys[5]) pos.z+=1 * moveSensitivity;
        else if (keys[4]) pos.z-=1 * moveSensitivity;
        if (keys[7]) cumPos.y+=1 * cumSensitivity;
        else if (keys[6]) cumPos.y-=1 * cumSensitivity;
        if (keys[8]) cumPos.x+=1 * cumSensitivity;
        else if (keys[9]) cumPos.x-=1 * cumSensitivity;
        shader.setUniform("u_mouse", cumPos);
        shader.setUniform("u_pos", pos);
        window.draw(emptySprite, &shader);
        window.display();
    }
    return 0;
}
