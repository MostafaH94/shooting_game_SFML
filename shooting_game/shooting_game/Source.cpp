#include<stdio.h>
#include<string>
#include<iostream>
#include<Ctime>
#include<SFML\Graphics.hpp>
#include<SFML/Audio.hpp>
#define WIDTH  800
#define HEIGHT  600
using namespace std;
using namespace sf;

//varibles 
static int mouse_color;
//static int shape_color;
sf::Vector2i enemy_pos;//enemy pos
sf::Vector2i cPos;//mouse pos

// shapes
auto circle = sf::CircleShape(10, 30); 
//auto rectangle = sf::RectangleShape(sf::Vector2f(80, 80)); // 3ayz a3rafhom fi constractor el class

static int lifes = 3;
static int score = 0;
int temp = 0;



// delay
void delay(long int time) {
	sf::Time z;
	auto x = z.asMilliseconds();
	while (time-- > 0);
}


//enemy class
class enemy
{
	sf::RectangleShape rectangle;
	int shape_color;
	sf::Vector2i enemy_pos;
public:
	enemy() {
		circle = sf::CircleShape(10, 30);
		rectangle = sf::RectangleShape(sf::Vector2f(80, 80));
	}
	//auto rectangle = sf::RectangleShape(sf::Vector2f(80, 80));//rag3o global
	void rect2(sf::RenderWindow &window) {
		window.draw(rectangle);
	}
	void rect(sf::RenderWindow &window)
	{

	     int enemy_color = rand() % 4;
		
		temp++;
		if (temp == 1)
		{
			enemy_pos.x = rand() % WIDTH - 50;
			enemy_pos.y = rand() % HEIGHT - 50;
			rectangle.setPosition(enemy_pos.x, enemy_pos.y);
			switch (enemy_color)
			{
			case 0:
				shape_color = enemy_color;
				rectangle.setFillColor(sf::Color::Yellow);
				
				break;
			case 1:
				shape_color = enemy_color;
				rectangle.setFillColor(sf::Color::Red);
				
				break;
			case 2:
				shape_color = enemy_color;
				rectangle.setFillColor(sf::Color::Blue);
				
				break;
			case 3:
				shape_color = enemy_color;
				rectangle.setFillColor(sf::Color::Green);
				
				break;
			default:
				break;
			}
			temp = 0;
		}
		window.draw(rectangle);
		/*delay(2000000);*/
	}
	bool in_range(int x , int y, int x1 , int y1)
	{
		if (((x >= x1) && (x <= (x1 + 80))) && ((y >= y1) && (y <= (y1 + 80))))
			return true;
		return false;
	
	
	}

	bool destroy_enemies(int color ,int x, int y) //cheak mouse collision
	{
		/*(0 < (cPos.x) - (enemy_pos.x) < 80)*/
		
		if (color==shape_color && in_range(x,y,cPos.x,cPos.y))
		{
        
			score += 100;
			return true;
		}
		else
		{
			return false;
			
		}

	}

};



//show score on screen
void show_score()
{
	cout << "lifes :" << lifes << endl;
	cout << "score :" << score << endl;
	if(lifes<=0)
	{
		system("CLS");
		cout << "Game Over" << endl;
		cout << "your score :" << score;
	}
}


//switch mouse color
void rand_color()
{

	int current_color = rand() % 4;
	switch (current_color)
	{
	case 0:
		circle.setFillColor(sf::Color::Yellow);
		mouse_color = current_color;
		break;
	case 1:
		circle.setFillColor(sf::Color::Red);
		mouse_color = current_color;
		break;
	case 2:
		circle.setFillColor(sf::Color::Blue);
		mouse_color = current_color;
		break;
	case 3:
		circle.setFillColor(sf::Color::Green);
		mouse_color = current_color;
		break;
	default:
		break;
	}

}


void main()
{
	//init window
	sf::RenderWindow window;
	int sizeEn=5;
	enemy *ee =new enemy[sizeEn];
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Grapher");
	/*Music music;
	music.openFromFile("Boku no Hero Academia.wav");
	music.setVolume(80);
	music.play();*/
	//data variable
	sf::Event e;

	//my cursor
	circle.setFillColor(sf::Color(255, 255, 0, 255));
	circle.setOrigin(10, 10);
	show_score();
	Clock c;
	Time el = c.getElapsedTime();
	while (window.isOpen()/*&&lifes>0*/)
	{
		window.clear();
		cPos = sf::Mouse::getPosition(window);
		
			Time ell = c.getElapsedTime() - el;
			el += ell;
			if (el.asMilliseconds() >=900) {
				el = c.restart();
				for (int i=0; i < 10; i ++);
				for (int k = 0; k < sizeEn; k++) {
					ee[k].rect(window);
				}
			}
			else{
				for (int k = 0; k < sizeEn; k++) {
					ee[k].rect2(window);
				}
			}

		
		
			bool up;


		//handle event "input"
		while (window.pollEvent(e)) {
			switch (e.type)
			{
			case sf::Event::MouseButtonPressed:
				if (e.mouseButton.button == sf::Mouse::Button::Left)
					/*circle.setFillColor(sf::Color::Red);*/
					rand_color();
				up = false;
					for (int k = 0; k < sizeEn; k++) {
						up=ee[k].destroy_enemies(mouse_color, cPos.x, cPos.y);
						if (up)
							break;
					}
					if (!up)
						lifes--;
				/*	e2.destroy_enemies(mouse_color, cPos.x, cPos.y);*/
					system("CLS");
					show_score();
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;

			}//switch

		}


		circle.setPosition(cPos.x, cPos.y);
		sf::Vector2f circlePos = circle.getPosition();

		
		//draw every thing
		window.draw(circle);
		window.display();
	

	}//while

}//main

