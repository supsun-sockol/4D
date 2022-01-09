#include <SFML/Graphics.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <fstream>

glm::vec4 cross(glm::vec4 a, glm::vec4 b, glm::vec4 c){
    return glm::vec4(a.y*b.z*c.w+a.z*b.w*c.y+a.w*b.y*c.z-a.w*b.z*c.y-a.z*b.y*c.w-a.y*b.w*c.z,
                     a.x*b.z*c.w+a.z*b.w*c.x+a.w*b.x*c.z-a.w*b.z*c.x-a.z*b.x*c.w-a.x*b.w*c.z,
                     a.x*b.y*c.w+a.y*b.w*c.x+a.w*b.x*c.y-a.w*b.y*c.x-a.y*b.x*c.w-a.x*b.w*c.y,
                     a.x*b.y*c.z+a.y*b.z*c.x+a.z*b.x*c.y-a.z*b.y*c.x-a.y*b.x*c.z-a.x*b.z*c.y);
}

glm::vec4 ort(glm::vec4 f, glm::vec4 a, glm::vec4 b, glm::vec4 c){
    return f-(glm::dot(f, a)/glm::dot(a, a))*a
            -(glm::dot(f, b)/glm::dot(b, b))*b
            -(glm::dot(f, c)/glm::dot(c, c))*c;
}

int main()
{
    std::string levelFile = "/home/supsun/Documents/4D/levels/2.txt";
    std::ifstream in(levelFile);
    int a, b, c, finishX, finishY, finishZ, startX,  startY, startZ;
    float Rad = 3.0;
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



    int w = 800;
    int h = 600;
    int cumX = 0;
    int cumY = 0;
    float cumSensitivity = 0.03f;
    float speed = 0.1f;
<<<<<<< HEAD
    bool moveKeys[8] = {false, false, false, false, false, false, false, false};
    bool rotateKeys[12] = {false, false, false, false, false, false, false, false, false, false, false, false};
    glm::vec4 dir(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec4 Rdir(0.0f, 1.0f, 0.0f, 0.0f);
    glm::vec4 Tdir(0.0f, 0.0f, 1.0f, 0.0f);
    glm::vec4 Hdir(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 pos(startX, startY, startZ, 0.0f);
    pos = pos * (2*Rad);
=======
    bool moveKeys[6] = {false, false, false, false, false, false};
    bool rotateKeys[6] = {false, false, false, false, false, false};
    glm::vec4 pos(-5.0f, 0.0f, 0.0f, 0.0f);
    glm::vec4 dir = (glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));
    glm::vec4 Rdir(0.0f, 1.0f, 0.0f, 0.0f);
    glm::vec4 Tdir(0.0f, 0.0f, 1.0f, 0.0f);
    glm::vec4 Hdir(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 temp;
    temp =ort (dir, Rdir, Tdir, Hdir);
    std::cout << temp.x <<" " << temp.y <<" "<<temp.z <<" "<< temp.w<<"\n";
    temp =ort (Rdir, dir, Tdir, Hdir);
    std::cout << temp.x <<" " << temp.y <<" "<<temp.z <<" "<< temp.w<<"\n";
    temp =ort (Tdir, dir, Rdir, Hdir);
    std::cout << temp.x <<" " << temp.y <<" "<<temp.z <<" "<< temp.w<<"\n";
    temp =ort (Hdir, dir, Rdir, Tdir);
    std::cout << temp.x <<" " << temp.y <<" "<<temp.z <<" "<< temp.w<<"\n";
    sf::Vector2f rotation = sf::Vector2f(0.0, 0.0);
>>>>>>> parent of de47812 (add yz left and right rotate)

    sf::RenderWindow window(sf::VideoMode(w, h), "Ray tracing", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::RenderTexture emptyTexture;
    emptyTexture.create(w, h);
    sf::Sprite emptySprite = sf::Sprite(emptyTexture.getTexture());
    sf::Shader shader;
    shader.loadFromFile("/home/supsun/Documents/4D/OutputShader.frag", sf::Shader::Fragment);

    shader.setUniform("u_resolution", sf::Vector2f(w, h));
    shader.setUniform("m_size", sf::Vector3f(a, b, c));
    shader.setUniformArray("mass", mass, a*b*c);
    shader.setUniform("Rad", Rad);
    shader.setUniform("sphere", sf::Vector3f(finishX, finishY, finishZ));






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
        glm::vec4 move(0.0f, 0.0f, 0.0f, 0.0f);
        sf::Vector3f dirTemp;
        /*

        if (rotateKeys[1]) rotation.y+=1 * cumSensitivity;
        else if (rotateKeys[0]) rotation.y-=1 * cumSensitivity;
        if (rotateKeys[2]) rotation.x+=1 * cumSensitivity;
        else if (rotateKeys[3]) rotation.x-=1 * cumSensitivity;
        */
        if (rotateKeys[1]){
            dir+=Tdir * cumSensitivity;
            dir = glm::normalize(dir);
            Tdir = ort(Tdir, dir, Rdir, Hdir);

        }
        else if (rotateKeys[0]){
            dir-=Tdir * cumSensitivity;
            dir = glm::normalize(dir);
            Tdir = ort(Tdir, dir, Rdir, Hdir);
        }
        if (rotateKeys[2]) {
            dir-=Rdir * cumSensitivity;
            dir = glm::normalize(dir);
            Rdir = ort(Rdir, dir, Tdir, Hdir);
            //std::cout << Tdir.x <<" " << Tdir.y <<" "<<Tdir.z <<" "<< Tdir.w<<"\n";
        }
        else if (rotateKeys[3]) {
            dir+=Rdir * cumSensitivity;
            dir = glm::normalize(dir);
            Rdir = ort(Rdir, dir, Tdir, Hdir);
        }

<<<<<<< HEAD
        }
        else if (rotateKeys[5]){
            Tdir-=Rdir * cumSensitivity;
            Tdir = glm::normalize(Tdir);
            Rdir = ort(Rdir, dir, Tdir, Hdir);
        int x = floor(newpos.x/(2*Rad)+0.5);
        int y = floor(newpos.y/(2*Rad)+0.5);
        int z = floor(newpos.z/(2*Rad)+0.5);

        }
=======
>>>>>>> parent of de47812 (add yz left and right rotate)

        if (moveKeys[0]) move.x += 1;
        else if (moveKeys[2]) move.x -= 1;
        if (moveKeys[3]) move.y += 1;
        else if (moveKeys[1]) move.y -= 1;
        if (moveKeys[5]) move.z += 1;
        else if (moveKeys[4]) move.z -= 1;

        /*glm::mat4 trans(1.0f);
        glm::mat4 rotmat(1.0f);
        rotmat[0][0] = rotmat[1][1] = cos(rotation.x);
        rotmat[0][1] = -sin(rotation.x);
        rotmat[1][0] = sin(rotation.x);
        trans *= rotmat;
        rotmat=glm::mat4(1.0f);
        rotmat[0][0] = rotmat[2][2] = cos(-rotation.y);
        rotmat[0][2] = -sin(-rotation.y);
        rotmat[2][0] = sin(-rotation.y);
        trans *= rotmat;
        move = trans*move;*/

        newpos=pos+move*speed;
        if (x>=0 and x<3 and y>=0 and y<3 and z>=0 and z<3){
            if (mass[x*b*c+y*c+z]==0){
                pos = newpos;
            }



        shader.setUniform("u_pos", sf::Vector3f(pos.x, pos.y, pos.z));
        shader.setUniform("u_dir", sf::Vector3f(dir.x, dir.y, dir.z));
        shader.setUniform("Rdir", sf::Vector3f(Rdir.x, Rdir.y, Rdir.z));
        shader.setUniform("Tdir", sf::Vector3f(Tdir.x, Tdir.y, Tdir.z));
        window.draw(emptySprite, &shader);
        window.display();
    }
    return 0;
}
