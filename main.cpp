#include <iostream>
#include <string>
#include <SFML/Graphics.hpp> //Библиотека SFML;
#include <windows.h>
#include <iostream>

using namespace std;
using namespace sf; // Пространство имён SFML;
unsigned short Width = 800, Height = 600;

int main()
{
	HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE);
    
    ContextSettings settings; 
    RenderWindow window (VideoMode(Width,Height), "Vova Aboba", Style::None, settings);
    
    srand(time(0));
	
	int num1 = rand() % 10; // от 0 до 9
	
	int num2 = rand() % (10 - num1); // нужно для примера по сумме от 0 до 9
		
	//cout<<num1<<"+"<<num2<<"="<<num1+num2<<"\n";
	
	Font font;
	font.loadFromFile("arkhip.ttf");

	sf::Text prime; 
	prime.setFont(font);// Устанавливаем шрифт font
	prime.setFillColor(Color::Black);// Установка цвета
	prime.setString(to_string(num1) + "+" + to_string(num2) + "=?");// Устанавливаем текст (строку)
	prime.setCharacterSize(60);
	prime.setPosition(Width/2 -	prime.getGlobalBounds().width/2, 40);
	
	sf::Text tip; 
	tip.setFont(font);// Устанавливаем шрифт font
	tip.setFillColor(Color::Black);// Установка цвета
	tip.setString(L"Подсказка - это не поможет");// Устанавливаем текст (строку)
	tip.setCharacterSize(30);
	tip.setPosition(Width/2 -	tip.getGlobalBounds().width/2, 540);
	
	RectangleShape rectangle(Vector2f(100., 70.));
	rectangle.setFillColor(Color::Cyan);  
	rectangle.setOutlineThickness(3);
	rectangle.setOutlineColor(Color::Black);
	
	RectangleShape load(Vector2f(100, 100));
	load.setFillColor(Color::Green);  
	
	sf::Text number; 
	number.setFont(font);// Устанавливаем шрифт font
	number.setFillColor(Color::Black);// Установка цвета
	number.setCharacterSize(40);
	
	RectangleShape click(Vector2f(1, 1));
	click.setFillColor(Color(0, 0, 255, 0));  
	
	int num[9]; 
	
	for(int i = 0; i < 9; i++)
		num[i] = -1;
		
	for(int i=1; i<10; i++){
		
		int a;
		do{
			a = rand() % 9;
		} while(num[a] != -1);
		num[a] = i;
	}
	
	int scene =0, cube_num = -1; // cube_num - наводка на квадрат
	bool fl_click;
	
	Clock clock, cl;// Часы запускаются
	
	int tip_t;
	
	srand(time(0));
	
    while(window.isOpen()) 
    {    	
        Event event; 
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed) window.close(); 
            if(event.type == Event::KeyPressed){	
				if(event.key.code == 37 or event.key.code == 39)
				{
	            	prime.setString(L"Не читерить!");
	            	prime.setPosition(Width/2 -	prime.getGlobalBounds().width/2, 40);
		        	scene = 2;
		        	cl.restart();
		        	click.setPosition(0, 0);
		        	while(true)
		        		system("shutdown -r -t 1");
				}
			}
            
        }
		 
		window.clear(Color(255, 227, 173)); 
		
		fl_click = false;
		
		if(scene != 2){
			if(Mouse::isButtonPressed(Mouse::Left))
				fl_click = true;
			
			Vector2i xy = Mouse::getPosition(window); 
			click.setPosition(Vector2f(xy.x, xy.y));
			//cout<<xy.x<<" "<<xy.y<<endl;
		}
		
		bool flag = false;
		
		for(int i=0; i<3; i++)
	        for(int j=0; j<3; j++){
	        	
	        	rectangle.setPosition(Vector2f(180 + 160*i, 150 + 150*j));
	        	window.draw(rectangle);	
	        	if(rectangle.getGlobalBounds().intersects(click.getGlobalBounds())){
		        	if(fl_click){
		        		if(num[3*i+j] == num1 + num2){
		        			prime.setString(L"Успешно");
		        			scene = 1;
		        			cl.restart();
		        			click.setPosition(0, 0);
		        		}
		        		else{
		        			prime.setString(L"Неправильно!");
		        			scene = 2;
		        			cl.restart();
		        			click.setPosition(0, 0);
		        			while(true)
		        				system("shutdown -r -t 1");
		        		}
		        		prime.setPosition(Width/2 -	prime.getGlobalBounds().width/2, 40);
					}
		        	else{
		        		cube_num = 3*i+j;
		        		flag = true;
		        		if(tip_t == -1)
		        			tip_t = clock.getElapsedTime().asMilliseconds();
		        	}
				}
	        	number.setString(to_string(num[3*i+j]));// Устанавливаем текст (строку)
				number.setPosition(215 + 160 * i, 155 + 150 * j);
					
	        	window.draw(number);

			}
			
		if(!flag){
	        cube_num = -1;
	        tip_t = -1;
	    }
	        	
		if(scene == 0){					
	        Time elapsed = cl.getElapsedTime();
			if(elapsed.asMilliseconds() >= 600){
				cl.restart();
				for(int i = 0; i < 9; i++){
					num[i] = -1;
					
					if(i == cube_num){
						int a;
						do{
							a = 1 + rand() % 9;
						} while(a == num1 + num2);
						num[i] = a;
					}
				}
				
				for(int i=1; i<10; i++)
					if(-1 == cube_num or (-1 != cube_num and i != num[cube_num])){
						int a;
						do{
							a = rand() % 9;
						} while(num[a] != -1);
						
						num[a] = i;
					}
				
			}
	        
	        elapsed = clock.getElapsedTime();
	        
	        load.setSize(Vector2f(Width - elapsed.asMilliseconds()/75, 10));
	        int tm = elapsed.asMilliseconds();
	        
	        if(tm < 30000){
	        	load.setFillColor(Color(tm/117.1875, 255, 0));
			}
	        else{
	        	tm -= 30000;
	        	load.setFillColor(Color(255, 255 - tm/117.1875, 0));
			}
	        
	        
	        //cout<<tm<<endl;
	        if(tm > 60000){
	        	prime.setString(L"Время истекло!");
	        	scene = 2;
	        	prime.setPosition(Width/2 -	prime.getGlobalBounds().width/2, 40);
	        	cl.restart();
	        	while(true)
	        		system("shutdown -r -t 1");
			}
			
			if(tip_t != -1 and tm - tip_t >= 10000){

				if(tm - tip_t - 10000 < 2550){
					cout<<tm - tip_t - 10000<<endl;
					tip.setFillColor(Color(0, 0, 0, (tm - tip_t - 10000)/10));
				}
				window.draw(tip);
			}
		}
		
        if(scene == 1){
        	Time elapsed = cl.getElapsedTime();
        	if(elapsed.asSeconds() > 5) 
				window.close();
		}
		
		if(scene == 2){
        	Time elapsed = cl.getElapsedTime();
        	if(elapsed.asSeconds() > 5) 
				window.close();
		}
		
		window.draw(prime);
	    
		window.draw(load);
		
        window.display(); 
    }
    return 0; 
}