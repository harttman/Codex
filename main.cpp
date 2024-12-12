#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1280, 720), L"Codex");
    Font font;
    Text text;

    if (!font.loadFromFile("Fonts/ARIAL.TTF"))
    {
        return 11;
    }

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setPosition(10, 10);

    string inputText;
   
    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode == 8 && !inputText.empty())
                {
                    inputText.pop_back();
                }
                else if (event.text.unicode < 128 && !event.text.unicode != 8)
                {
                    inputText += static_cast<char>(event.text.unicode);
                }
                text.setString(inputText);
            }
        }


        window.clear(Color::Black);
        window.draw(text);
        window.display();
    }

    return 0;
}
