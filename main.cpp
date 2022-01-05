#include <SFML/Graphics.hpp>

int main()
{
    int w = 800;
    int h = 600;
    int cumX = 0;
    int cumY = 0;
    float cumSensitivity = 0.03f;
    float speed = 0.1f;
    bool moveKeys[6] = {false, false, false, false, false, false};
    bool rotateKeys[12] = {false, false, false, false, false, false, false, false, false, false, false, false};
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
                // move
                if (event.key.code == sf::Keyboard::W) moveKeys[0] = true; //forward
                else if (event.key.code == sf::Keyboard::A) moveKeys[1] = true; // left
                else if (event.key.code == sf::Keyboard::S) moveKeys[2] = true; // back
                else if (event.key.code == sf::Keyboard::D) moveKeys[3] = true; // right
                else if (event.key.code == sf::Keyboard::R) moveKeys[4] = true; // up
                else if (event.key.code == sf::Keyboard::F) moveKeys[5] = true; // down
                // rotate
                else if (event.key.code == sf::Keyboard::Up) rotateKeys[0] = true; // up (xz)
                else if (event.key.code == sf::Keyboard::Down) rotateKeys[1] = true; // down (xz)
                else if (event.key.code == sf::Keyboard::Left) rotateKeys[2] = true; // left (xy)
                else if (event.key.code == sf::Keyboard::Right) rotateKeys[3] = true; // right (xy)

            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::W) moveKeys[0] = false;
                else if (event.key.code == sf::Keyboard::A) moveKeys[1] = false;
                else if (event.key.code == sf::Keyboard::S) moveKeys[2] = false;
                else if (event.key.code == sf::Keyboard::D) moveKeys[3] = false;
                else if (event.key.code == sf::Keyboard::R) moveKeys[4] = false;
                else if (event.key.code == sf::Keyboard::F) moveKeys[5] = false;
                else if (event.key.code == sf::Keyboard::Up) rotateKeys[0] = false;
                else if (event.key.code == sf::Keyboard::Down) rotateKeys[1] = false;
                else if (event.key.code == sf::Keyboard::Left) rotateKeys[2] = false;
                else if (event.key.code == sf::Keyboard::Right) rotateKeys[3] = false;
            }
        }
        if (moveKeys[0]) pos.x+=1* speed;
        else if (moveKeys[2]) pos.x-=1 * speed;
        if (moveKeys[3]) pos.y+=1 * speed;
        else if (moveKeys[1]) pos.y-=1 * speed;
        if (moveKeys[5]) pos.z+=1 * speed;
        else if (moveKeys[4]) pos.z-=1 * speed;
        if (rotateKeys[1]) cumPos.y+=1 * cumSensitivity;
        else if (rotateKeys[0]) cumPos.y-=1 * cumSensitivity;
        if (rotateKeys[2]) cumPos.x+=1 * cumSensitivity;
        else if (rotateKeys[3]) cumPos.x-=1 * cumSensitivity;
        shader.setUniform("u_mouse", cumPos);
        shader.setUniform("u_pos", pos);
        window.draw(emptySprite, &shader);
        window.display();
    }
    return 0;
}
