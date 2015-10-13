#include <SFML/Graphics.hpp>
#include "display.h"
int disply()
{
    	sf::RenderWindow window(sf::VideoMode(900, 900), "Crossword");
	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
  			
            switch(event.type)
            {
            	 case sf::Event::Closed:		window.close();
            							break;
            	 case sf::Event::KeyPressed:	switch(event.key.code)
            	 						{
            	 							case sf::Keyboard::Num1:		window.close();
            	 													break;
            	 							case sf::Keyboard::Num2:		choice=2;
            	 													window.close();
            	 													break;
            	 							case	sf::Keyboard::Num3:		choice=3;
            	 													window.close();
            	 													break;
            	 							case sf::Keyboard::Num4:		choice=4;
            	 													window.close();
            	 						}
            }
           
            	
        }
        window.clear(sf::Color::Black);
        sf::RectangleShape rectangle(sf::Vector2f(35, 35));
        rectangle.setOutlineThickness(7);
        rectangle.setOutlineColor(sf::Color(250,150,100));
        for(int i=0;i<30;i++)
        {
        		for(int j=0;j<30;j++)
        		{
        			if(grid[i][j])
        			{
        				rectangle.setPosition(40+i*40,40+40*j);
         				window.draw(rectangle);
         			}
         		}
        }
        sf::Font font;
        font.loadFromFile("sansation.ttf");
        sf::Text txt;
        txt.setFont(font);
        txt.setColor(sf::Color(153,255,51));
	   txt.setCharacterSize(20);
	   txt.setPosition(3,2); 
        txt.setString("Enter search method");
        txt.setStyle(sf::Text::Bold);
        window.draw(txt);
        txt.setPosition(3,21);
        txt.setString("1.Linear search");
        window.draw(txt);
        txt.setPosition(3,41);
        txt.setString("2.Generalised Suffix Tree");
        window.draw(txt);
        txt.setPosition(3,61);
        txt.setString("3.Two-dimensional Matrix");
        window.draw(txt);
        txt.setPosition(3,81);
        txt.setString("4.Three-dimensional Matrix");
        window.draw(txt);
        sf::Text text;
	   text.setFont(font);
        if(check)
        {
	   	for(int i=0;i<30;i++)
	   	{
	   			for(int j=0;j<30;j++)
	   			{
	   				if(grid[i][j])
	   				{
	   					text.setString(grid[i][j]);
	   					text.setPosition(41+i*41,40+40*j);
	   					text.setCharacterSize(25); 
	   					text.setColor(sf::Color::Black);
	   					text.setStyle(sf::Text::Bold);
	   					window.draw(text);
	   				}
	   			}
	   		}
	   		text.setPosition(500,500);
	   		text.setString("Time taken:");
		   	text.setColor(sf::Color(255,102,255));
		   	window.draw(text);
		   	text.setPosition(550,550);
		   	text.setString(time_taken);
		   	window.draw(text);
		   	text.setString("microseconds");
		   	text.setPosition(550,580);
		   	window.draw(text);
		   }
        window.display();
    }

    return 0;
}
