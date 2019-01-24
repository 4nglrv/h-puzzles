// SFML_Game.cpp: определяет точку входа для консольного приложения.

#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "math.h"
#include "cstring"
#include "stdio.h"
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <time.h>

using namespace sf;
using namespace std;

struct Object //создаем класс для спрайтов
{
	int id;
	Sprite kSprite;
	Texture *ktexture;
	std::string type;
}; 

void clearObjects(vector <Object>& sprites) //очистка текстур и спрайтов из памяти
{
	for (int i = 0; i < sprites.size(); i++) {
		delete sprites[i].ktexture;
	}
	sprites.clear();
} 

void outSprites3x3(vector <Object>& sprites, int l){  //создание спрайтов и запихуяривание их в вектор
	sprites.clear();
	for (size_t i = 0; i < 3; i++) // 102x129
	{
		for (size_t j = 0; j < 3; j++)
		{
			char base_name[512] = {};
			sprintf_s(base_name, "pictures/puzzles/%i/0%i.jpg", l, sprites.size()); //приваиваем к base_name пусть к текстуре
			Object kTemp;
			kTemp.ktexture = new Texture; //указатель
			kTemp.ktexture->loadFromFile(base_name); //загружаем текстуру указанную в base_name		"->" - указатель
			kTemp.kSprite.setTexture(*kTemp.ktexture); //загрузаем текстуру в спрайт
			kTemp.kSprite.setPosition((j * kTemp.ktexture->getSize().x) + 100, (i * kTemp.ktexture->getSize().y) + 101);
			kTemp.id = sprites.size(); //задаем айди спрайтам
			sprites.push_back(kTemp); //запихуяриваем спрайты в вектор
		}
	}
}

void outSprites4x4(vector <Object>& sprites, int l) {  //создание спрайтов и запихуяривание их в вектор
	sprites.clear();
	for (size_t i = 0; i < 4; i++) // 102x129
	{
		for (size_t j = 0; j < 4; j++)
		{
			char base_name[512] = {};
			sprintf_s(base_name, "pictures/puzzles/%i/0%i.jpg", l, sprites.size()); //приваиваем к base_name пусть к текстуре
			Object kTemp;
			kTemp.ktexture = new Texture; //указатель
			kTemp.ktexture->loadFromFile(base_name); //загружаем текстуру указанную в base_name		"->" - указатель
			kTemp.kSprite.setTexture(*kTemp.ktexture); //загрузаем текстуру в спрайт
			kTemp.kSprite.setPosition((j * kTemp.ktexture->getSize().x) + 100, (i * kTemp.ktexture->getSize().y) + 100);
			kTemp.id = sprites.size(); //задаем айди спрайтам
			sprites.push_back(kTemp); //запихуяриваем спрайты в вектор
		}
	}
}

void mix3(vector <Object>& sprites) { //с помощью &(оперсанда) мы можем поменять передаваемое значение во всей программе
	srand(time(NULL)); 
	for (int i = 0; i < sprites.size()-1; i++)// -1 для того чтобы мы меняли пазлы попарно
	{
		Vector2i rnd(rand() % 9 + 0, rand() % 9 + 0);
		Vector2f vec1 = sprites[rnd.x].kSprite.getPosition();
		Vector2f vec2 = sprites[rnd.y].kSprite.getPosition();
		sprites[rnd.x].kSprite.setPosition(vec2);
		sprites[rnd.y].kSprite.setPosition(vec1);
		swap(sprites[rnd.x], sprites[rnd.y]);

	}

}

void mix4(vector <Object>& sprites) { //с помощью &(оперсанда) мы можем поменять передаваемое значение во всей программе
	srand(time(NULL));
	for (int i = 0; i < sprites.size() - 1; i++)// -1 для того чтобы мы меняли пазлы попарно
	{
		Vector2i rnd(rand() % 16 + 0, rand() % 16 + 0);
		Vector2f vec1 = sprites[rnd.x].kSprite.getPosition();
		Vector2f vec2 = sprites[rnd.y].kSprite.getPosition();
		sprites[rnd.x].kSprite.setPosition(vec2);
		sprites[rnd.y].kSprite.setPosition(vec1);
		swap(sprites[rnd.x], sprites[rnd.y]);

	}

}

bool check(vector <Object> sprites) {
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i].id != i)
			return false;
	}
	return true;
}

void mainMenu(vector <Object>& mMenu)
{
	mMenu.clear();
	int randY = 408;
	for (size_t i = 0; i < 4; i++)
	{
		char base_name[512] = {};
		sprintf_s(base_name, "pictures/materials/mainMenu/0%i.jpg", mMenu.size());
		Object kMain;
		if (i != 0)
		{
			kMain.type = "button";
		}
		else
		{
			kMain.type = "background";
		}

		kMain.ktexture = new Texture;
		kMain.ktexture->loadFromFile(base_name);
		kMain.kSprite.setTexture(*kMain.ktexture); 
		if (i != 0)
			kMain.kSprite.setPosition(6, (randY += 46));
		kMain.id = mMenu.size();
		mMenu.push_back(kMain);
	}
}

void aboutMenu(vector <Object>& aMenu) {
	aMenu.clear();
	for (size_t i = 0; i < 2; i++)
	{
		char base_name[512] = {};
		sprintf_s(base_name, "pictures/materials/aboutMenu/0%i.jpg", aMenu.size());
		Object kAbout;
		kAbout.ktexture = new Texture;
		kAbout.ktexture->loadFromFile(base_name);
		kAbout.kSprite.setTexture(*kAbout.ktexture);
		if (i != 0)
		{
			kAbout.type = "button";
			kAbout.kSprite.setPosition(5, 540);
		}
		else
		{
			kAbout.type = "background";
		}
		kAbout.id = aMenu.size();
		aMenu.push_back(kAbout);
	}
}

void button(vector <Object>& buttons) {
	buttons.clear();
	for (int i = 0; i < 4; i++) {
		char base_name[512] = {};
		sprintf_s(base_name, "pictures/materials/buttons/0%i.jpg", buttons.size());
		Object kButton;
		kButton.ktexture = new Texture;
		kButton.ktexture->loadFromFile(base_name);
		kButton.kSprite.setTexture(*kButton.ktexture);
		if (i == 0) {
			kButton.kSprite.setPosition(5, 540);
		}
		if (i == 1 || i == 3) {
			kButton.kSprite.setPosition(26, 271);
		}
		if (i == 2 || i == 4) {
			kButton.kSprite.setPosition(419, 271);
		}
		kButton.id = buttons.size();
		buttons.push_back(kButton);
	}

}

void startMenu(vector <Object>& sMenu) {
	sMenu.clear();
	int levelpos = 0;
	for (size_t i = 0; i < 8; i++)
	{
		char base_name[512] = {};
		sprintf_s(base_name, "pictures/materials/startMenu/0%i.jpg", sMenu.size());
		Object kStart;
		kStart.ktexture = new Texture;
		kStart.ktexture->loadFromFile(base_name);
		kStart.kSprite.setTexture(*kStart.ktexture);
		if (i == 0) {
			kStart.type = "background";
		}
		else if (i == 1) {
			kStart.type = "button";
			kStart.kSprite.setPosition(5, 540);
		}
		else if (i > 1) {
			kStart.type = "levels";
			switch (i){
			case 2:
			{
				kStart.kSprite.setPosition(103, 44);
			}break;
			case 3:
			{
				//kStart.ktexture->loadFromFile("pictures\materials\startMenu\empty.png");
				kStart.kSprite.setPosition(299, 44);
				if (levelpos > 1) {
					
				}
			}break;
			case 4:
			{
				kStart.kSprite.setPosition(103, 207);
			}break;
			case 5:
			{
				kStart.kSprite.setPosition(299, 207);
			}break;
			case 6:
			{
				kStart.kSprite.setPosition(103, 370);
			}break;
			case 7:
			{
				kStart.kSprite.setPosition(299, 370);
			}break;
			}
		}//else
		sMenu.push_back(kStart);
	}//for
}

int main()
{
	RenderWindow kWnd;
	kWnd.create(VideoMode(500, 600), "Hentai Puzzle!", Style::Titlebar | Style::Close); //настройка окна
	//ShowWindow(GetConsoleWindow(), SW_HIDE);//скрытие консоли

	//создание спрайтов и запихуяривание их в вектор
	vector <Object> Menu;
	//вектор с пазлами

	Object BackGround3;
	BackGround3.ktexture = new Texture;
	BackGround3.ktexture->loadFromFile("pictures/puzzles/Background3x3.jpg");
	BackGround3.kSprite.setTexture(*BackGround3.ktexture);
	
	Object BackGround4;
	BackGround4.ktexture = new Texture;
	BackGround4.ktexture->loadFromFile("pictures/puzzles/Background4x4.jpg");
	BackGround4.kSprite.setTexture(*BackGround4.ktexture);

	int numCase = -1;
	int iTemp = -1;
	bool wl = false; //проверка
	int location = 0; //-1 or 0 - mainMenu; 1 - startMenu; 2 - aboutMenu; 3 - exit; 4 - 1 level; 5 - 2 level

	vector<Object> sprites;
	vector<Object> buttons;

	if (location == 4){ //в зависимости от нажатого спрайта вывести нунжую функцию
	}
	while (kWnd.isOpen())
	{
		Event event;
		while (kWnd.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				kWnd.close();
			}
			else if (event.type == Event::MouseButtonPressed)
			{
				//mainMenu
				if(Menu.size() == 2){
				for (int i = 0; i < Menu.size(); i++){
					if (Mouse::isButtonPressed(Mouse::Left) &&
						Menu[i].kSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && Menu[i].type == "button")
					{
						if (numCase == 2) {
							location = 0;
						}
						else {
							location = i;
						}
					}
				}
			}//if
				//startMenu
				else{
				for (int i = 0; i < Menu.size(); i++) {
					if (Mouse::isButtonPressed(Mouse::Left) &&
						Menu[i].kSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && Menu[i].type == "button")
					{
						if (numCase == 1) {
							location = 0;
						}
						else {
							location = i;
						}
					}
					if (Mouse::isButtonPressed(Mouse::Left) &&
						Menu[i].kSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && Menu[i].type == "levels")
					{
						if (numCase == 1 && i == 2) {
							int a = 1;
							location = 4; //1 уровень
							outSprites3x3(sprites, a);
							mix3(sprites);
						}
						else if (numCase == 1 && i == 3) {
							int a = 2;
							location = 5; //2 уровень
							outSprites4x4(sprites, a);
							mix4(sprites);
						}
						else if (numCase == 1 && i == 4) {
							int a = 3;
							location = 6; //3 уровень
							outSprites3x3(sprites, a);
							mix3(sprites);
						}
						else if (numCase == 1 && i == 5) {
							int a = 4;
							location = 7; //4 уровень
							outSprites3x3(sprites, a);
							mix3(sprites);
						}
						else if (numCase == 1 && i == 6) {
							int a = 5;
							location = 8; //5 уровень
							outSprites4x4(sprites, a);
							mix4(sprites);
						}
						else if (numCase == 1 && i == 7) {
							int a = 6;
							location = 9; //6 уровень
							outSprites4x4(sprites, a);
							mix4(sprites);
						}
					}
				}//for
			}//else

				cout << location;
				//puzzles
				for (int i = 0; i < sprites.size(); i++) {
					if (Mouse::isButtonPressed(Mouse::Left) &&
						sprites[i].kSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) { //если нажата кнопка мыши и наведенна на спрайт
						if (iTemp == -1)
						{
							iTemp = i; //присваеваем к переменной позицию в векторе спрайта на который нажали
							sprites[i].kSprite.setColor(sf::Color(255, 255, 255, 128)); //закрашивание выделенного спрайта
							continue;
						}
						sf::Vector2f vecTemp = sprites[iTemp].kSprite.getPosition();
						sprites[iTemp].kSprite.setPosition(sprites[i].kSprite.getPosition());//присваеваем местоположение первого спрайта ко второму
						sprites[i].kSprite.setPosition(vecTemp);//присваеваем местоположение второго спрайта к первому
						for (int i = 0; i < sprites.size(); i++)
 							sprites[i].kSprite.setColor(sf::Color::White); //убираем закрашивание через цикл
						swap(sprites[iTemp], sprites[i]);
						iTemp = -1;
						break;
					}//if MouseButtonPressed
				}//for i
			}//MouseButtonPressed
		}//kWnd
		kWnd.clear();

		switch (location)
		{
		case -1:
		case 0: { //mainMenu
			numCase = location;
			clearObjects(Menu);
			mainMenu(Menu);
			for (int i = 0; i < Menu.size(); i++) {
				kWnd.draw(Menu[i].kSprite);
		}break;
			case 1: { //startMenu
				numCase = location;
				clearObjects(Menu);
				startMenu(Menu);
				for (int i = 0; i < Menu.size(); i++) {
					kWnd.draw(Menu[i].kSprite);
				}
					}break;
			case 2: { //aboutMenu
				numCase = location;
				clearObjects(Menu);
				aboutMenu(Menu);
				for (int i = 0; i < Menu.size(); i++) {
					kWnd.draw(Menu[i].kSprite);
				}
						}
					}break;
			case 3: {
				kWnd.close();
					}break;
			case 4: {
				numCase = location; //1 lev
				clearObjects(Menu);
				kWnd.draw(BackGround3.kSprite);
				button(buttons);
				for (int i = 0; i < buttons.size(); i++) {
					kWnd.draw(buttons[i].kSprite);
				};
				for (int i = 0; i < sprites.size(); i++) {
					kWnd.draw(sprites[i].kSprite);
				}
			}break;
			case 5: {
				numCase = location; //2 lev
				clearObjects(Menu);
				kWnd.draw(BackGround4.kSprite);
				//outSprites4x4(sprites);
				for (int i = 0; i < sprites.size(); i++) {
					kWnd.draw(sprites[i].kSprite);
				}
			}break;
			case 6: {
				numCase = location; //3 lev
				clearObjects(Menu);
				kWnd.draw(BackGround3.kSprite);
				//outSprites4x4(sprites);
				for (int i = 0; i < sprites.size(); i++) {
					kWnd.draw(sprites[i].kSprite);
				}
			}break;
			case 7: {
				numCase = location; //4 lev
				clearObjects(Menu);
				kWnd.draw(BackGround3.kSprite);
				//outSprites4x4(sprites);
				for (int i = 0; i < sprites.size(); i++) {
					kWnd.draw(sprites[i].kSprite);
				}
			}break;
			case 8: {
				numCase = location; //5 lev
				clearObjects(Menu);
				kWnd.draw(BackGround4.kSprite);
				//outSprites4x4(sprites);
				for (int i = 0; i < sprites.size(); i++) {
					kWnd.draw(sprites[i].kSprite);
				}
			}break;
			case 9: {
				numCase = location; //6 lev
				clearObjects(Menu);
				kWnd.draw(BackGround4.kSprite);
				//outSprites4x4(sprites);
				for (int i = 0; i < sprites.size(); i++) {
					kWnd.draw(sprites[i].kSprite);
				}
			}break;
		}
		//проверка
		if (check(sprites) == true && wl == false) {
			cout << "SUCCESS!!!!!!!~!!!!!!CTYA TVBLAN SDFJIOEOFJIEW\n"; 
			wl = true;
		}
		kWnd.display();
	}
	return 0;
}