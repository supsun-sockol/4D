#include <SFML/Graphics.hpp>
#include <iostream>
//#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

int main()
{
    int w = 800;
    int h = 600;
    int cumX = 0;
    int cumY = 0;
    float cumSensitivity = 0.03f;
    float speed = 0.1f;
    bool moveKeys[8] = {false, false, false, false, false, false, false, false};
    bool rotateKeys[6] = {false, false, false, false, false, false};
    glm::vec4 pos(-5.0f, 0.0f, 0.0f, 0.0f);
    sf::Vector3f rotation = sf::Vector3f(0.0, 0.0, 0.0);

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
                else if (event.key.code == sf::Keyboard::Z) moveKeys[6] = true; // hyper up
                else if (event.key.code == sf::Keyboard::X) moveKeys[7] = true; // hyper down
                // rotate
                else if (event.key.code == sf::Keyboard::Up) rotateKeys[0] = true; // up (xz)
                else if (event.key.code == sf::Keyboard::Down) rotateKeys[1] = true; // down (xz)
                else if (event.key.code == sf::Keyboard::Left) rotateKeys[2] = true; // left (xy)
                else if (event.key.code == sf::Keyboard::Right) rotateKeys[3] = true; // right (xy)
                else if (event.key.code == sf::Keyboard::RShift) rotateKeys[4] = true; // hyper up (xw)
                else if (event.key.code == sf::Keyboard::RControl) rotateKeys[5] = true; // hyper down (xw)

            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::W) moveKeys[0] = false;
                else if (event.key.code == sf::Keyboard::A) moveKeys[1] = false;
                else if (event.key.code == sf::Keyboard::S) moveKeys[2] = false;
                else if (event.key.code == sf::Keyboard::D) moveKeys[3] = false;
                else if (event.key.code == sf::Keyboard::R) moveKeys[4] = false;
                else if (event.key.code == sf::Keyboard::F) moveKeys[5] = false;
                else if (event.key.code == sf::Keyboard::Z) moveKeys[6] = false;
                else if (event.key.code == sf::Keyboard::X) moveKeys[7] = false;
                else if (event.key.code == sf::Keyboard::Up) rotateKeys[0] = false;
                else if (event.key.code == sf::Keyboard::Down) rotateKeys[1] = false;
                else if (event.key.code == sf::Keyboard::Left) rotateKeys[2] = false;
                else if (event.key.code == sf::Keyboard::Right) rotateKeys[3] = false;
                else if (event.key.code == sf::Keyboard::RShift) rotateKeys[4] = false;
                else if (event.key.code == sf::Keyboard::RControl) rotateKeys[5] = false;
            }
        }
        glm::vec4 dir(0.0f, 0.0f, 0.0f, 0.0f);
        sf::Vector3f dirTemp;

        if (rotateKeys[1]) rotation.y+=1 * cumSensitivity;
        else if (rotateKeys[0]) rotation.y-=1 * cumSensitivity;
        if (rotateKeys[2]) rotation.x+=1 * cumSensitivity;
        else if (rotateKeys[3]) rotation.x-=1 * cumSensitivity;
        if (rotateKeys[4]) rotation.z+=1 * cumSensitivity;
        else if (rotateKeys[5]) rotation.z-=1 * cumSensitivity;

        if (moveKeys[0]) dir.x += 1;
        else if (moveKeys[2]) dir.x -= 1;
        if (moveKeys[3]) dir.y += 1;
        else if (moveKeys[1]) dir.y -= 1;
        if (moveKeys[5]) dir.z += 1;
        else if (moveKeys[4]) dir.z -= 1;
        if (moveKeys[7]) dir.w += 1;
        else if (moveKeys[6]) dir.w -= 1;

        glm::mat4 trans(1.0f);
        glm::mat4 rotmat(1.0f);
        rotmat[0][0] = rotmat[1][1] = cos(rotation.x);
        rotmat[0][1] = -sin(rotation.x);
        rotmat[1][0] = sin(rotation.x);
        trans *= rotmat;
        /*rotmat=glm::mat4(1.0f);
        rotmat[0][0] = rotmat[2][2] = cos(-rotation.y);
        rotmat[0][2] = -sin(-rotation.y);
        rotmat[2][0] = sin(-rotation.y);
        trans *= rotmat;*/
        dir = trans*dir;

        pos+=dir*speed;
        sf::Glsl::Vec4 poss;
        poss = sf::Glsl::Vec4(pos.x, pos.y, pos.z, pos.w);
        shader.setUniform("u_mouse", rotation);
        shader.setUniform("u_pos", poss);
        window.draw(emptySprite, &shader);
        window.display();
    }
    return 0;
}
