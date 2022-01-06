#include <SFML/Graphics.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <fstream>

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
    glm::vec4 pos(-5.0f, 0.0f, 0.0f, 0.0f);
    sf::Vector2f rotation = sf::Vector2f(0.0, 0.0);

    sf::RenderWindow window(sf::VideoMode(w, h), "Ray tracing", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::RenderTexture emptyTexture;
    emptyTexture.create(w, h);
    sf::Sprite emptySprite = sf::Sprite(emptyTexture.getTexture());
    sf::Shader shader;
    shader.loadFromFile("/home/supsun/Documents/4D/shader/OutputShader.frag", sf::Shader::Fragment);


    std::string levelFile = "/home/supsun/Documents/4D/levels/1.txt";
    std::ifstream in(levelFile);
    int a, b, c, finishX, finishY, finishZ, startX,  startY, startZ;
    if (!in.is_open())
    {
        return 0;

    }

    in>>a;
    in>>b;
    in>>c;
    in>>startX;
    in>>startY;
    in>>startZ;
    in>>finishX;
    in>>finishY;
    in>>finishZ;

    float* mass = new float[a*b*c];
    for (int x =0; x<a*b*c; x++)
    {
        in >> mass[x];
    }

    shader.setUniform("u_resolution", sf::Vector2f(w, h));
    shader.setUniform("m_size", sf::Vector3f(a, b, c));
    shader.setUniformArray("mass", mass, a*b*c);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

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
        glm::vec4 dir(0.0f, 0.0f, 0.0f, 0.0f);
        sf::Vector3f dirTemp;

        if (rotateKeys[1]) rotation.y+=1 * cumSensitivity;
        else if (rotateKeys[0]) rotation.y-=1 * cumSensitivity;
        if (rotateKeys[2]) rotation.x+=1 * cumSensitivity;
        else if (rotateKeys[3]) rotation.x-=1 * cumSensitivity;

        if (moveKeys[0]) dir.x += 1;
        else if (moveKeys[2]) dir.x -= 1;
        if (moveKeys[3]) dir.y += 1;
        else if (moveKeys[1]) dir.y -= 1;
        if (moveKeys[5]) dir.z += 1;
        else if (moveKeys[4]) dir.z -= 1;

        glm::mat4 trans(1.0f);
        glm::mat4 rotmat(1.0f);
        rotmat[0][0] = rotmat[1][1] = cos(rotation.x);
        rotmat[0][1] = -sin(rotation.x);
        rotmat[1][0] = sin(rotation.x);
        trans *= rotmat;
        dir = trans*dir;

        pos+=dir*speed;


        shader.setUniform("u_mouse", rotation);
        shader.setUniform("u_pos", sf::Vector3f(pos.x, pos.y, pos.z));
        window.draw(emptySprite, &shader);
        window.display();
    }
    return 0;
}
