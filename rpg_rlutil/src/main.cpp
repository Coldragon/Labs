#include <iostream>
#include <string>
#include "rlutil/rlutil.h"

class LeBob
{
	std::string nomDuJoueur = "New_Player";
	int max_vie = 100;
	int vie = max_vie;
	int max_mana = 100;
	int mana = max_mana;
	int level = 1;
	std::string arme_equipe = "Hands";
	int degats = 5;
	float attack_speed = 1.1;
	int nb_potion_vie = 2;
	int pwr_potion_vie = 75;

public:
	int posx = 5; int posy = 5;

	LeBob*cibleActuel = nullptr;

	void recevoirDegats(const int nbDegats)
	{
		vie -= nbDegats;
	}
	void attaquer() const
	{
		cibleActuel->recevoirDegats(degats);
		std::cout << monNom() << " attack " << cibleActuel->monNom() << " with " << arme_equipe << " and deal " << degats << " damages." << std::endl
			<< cibleActuel->monNom() << "'s health : " << cibleActuel->maVie() << " / " << cibleActuel->maVieMax() << std::endl;
		if (!cibleActuel->estVivant())
		{
			rlutil::setColor(rlutil::RED);
			std::cout << cibleActuel->monNom() << " is dead." << std::endl;
			rlutil::setColor(15);
			cibleActuel->changeVie();
		}
		std::cout << std::endl;
	}
	void boirePotionDeVie()
	{
		if (nb_potion_vie > 0)
		{
			--nb_potion_vie;
			vie += pwr_potion_vie; if (vie > max_vie)vie = max_vie;
			std::cout << "You drink a potion." << std::endl;
			std::cout << "You have now : " << vie << " / " << max_vie << " HP " << std::endl << std::endl;
		}
		else
		{
			std::cout << "You don't find potion on you, you probably didn't have anymore" << std::endl << std::endl;
		}
	}
	void setStats(const int newVie = 200, const int newMana = 100)
	{
		auto temp = vie;
		max_vie = newVie;
		vie = temp;
		if (vie > max_vie)
			vie = max_vie;

		temp = mana;
		max_mana = newMana;
		mana = temp;
		if (mana > max_mana)
			mana = max_mana;
	}
	void showStatus() const
	{
		std::cout << "   STATUS : " << nomDuJoueur << std::endl;
		std::cout << "   HP : " << vie << " / " << max_vie << std::endl;
		if (max_mana != 0)
			std::cout << "   MP : " << mana << " / " << max_mana << std::endl;
		std::cout << "   WP : " << arme_equipe << " :: " << degats << " damages " << std::endl << std::endl;
	}
	void nameChange(const std::string nom) { nomDuJoueur = nom; }
	void targetChange(LeBob*newcible) { cibleActuel = newcible; }
	void weaponChange(const std::string temp, const int damage) { arme_equipe = temp; degats = damage; }
	void changeVie() { vie = 0; }
	bool estVivant() const { return vie >= 1; }
	int maVie() const { return vie; }
	int maVieMax() const { return max_vie; }
	int maMana() const { return mana; }
	int maManaMax() const { return max_mana; }
	std::string monNom() const { return nomDuJoueur; }
	bool hasTarget() const
	{
		return cibleActuel && cibleActuel->estVivant();
	}
};

class Map
{
	int mur[100][50] = {};
	LeBob*persoPrincipal = nullptr;

public:

	static void afficherMap(const int x, const int y, const int w, const int h)
	{
		rlutil::locate(x, y);
		std::cout << char(201);
		for (int i = 1; i < w - 1; i++)
		{
			rlutil::locate(x + i, y);
			std::cout << char(205);
		}
		rlutil::locate(x + w - 1, y);
		std::cout << char(187);

		rlutil::setColor(rlutil::GREY);
		rlutil::setBackgroundColor(rlutil::GREEN);
		for (int i = 0; i < w; i++)
		{
			for (int j = 1; j < h - 1; j++)
			{
				rlutil::locate(x + i, y + j);
				if (i == 0)
				{
					rlutil::setBackgroundColor(rlutil::BLACK);
					rlutil::setColor(15);
					std::cout << char(186);
					rlutil::setColor(rlutil::GREY);
					rlutil::setBackgroundColor(rlutil::GREEN);
				}
				else if (i == w - 1)
				{
					rlutil::setBackgroundColor(rlutil::BLACK);
					rlutil::setColor(15);
					std::cout << char(186);
					rlutil::setColor(rlutil::GREY);
					rlutil::setBackgroundColor(rlutil::GREEN);
				}
				else
					std::cout << char(176);
			}
		}
		rlutil::setBackgroundColor(rlutil::BLACK);
		rlutil::setColor(15);

		rlutil::locate(x, y + h - 1);
		std::cout << char(200);
		for (auto i = 1; i < w - 1; i++)
		{
			rlutil::locate(x + i, y + h - 1);
			std::cout << char(205);
		}
		rlutil::locate(x + w - 1, y + h - 1);
		std::cout << char(188);
	}
	void targetChange(LeBob*newcible) { persoPrincipal = newcible; }
};

void helpCommand()
{
	std::cout << " Option : (T)arget (S)tats (E)nnemies" << std::endl;
	std::cout << " Action : (A)ttack (H)eal" << std::endl;
}

void lineCreate(const int line, const int character)
{
	for (auto i = 0; i < rlutil::tcols(); i++)
	{

		rlutil::locate(i, line);
		rlutil::setChar(character);
	}
}

void lineCreateUp(const int line)
{
	rlutil::locate(1, line);
	rlutil::setChar(201);
	for (auto i = 2; i < rlutil::tcols(); i++)
	{
		rlutil::locate(i, line);
		rlutil::setChar(205);
	}
	rlutil::locate(rlutil::tcols(), line);
	rlutil::setChar(187);
}

void lineCreateBorder(const int line)
{
	rlutil::locate(1, line);
	rlutil::setChar(186);

	rlutil::locate(rlutil::tcols(), line);
	rlutil::setChar(186);
}

void lineCreateDown(const int line)
{
	rlutil::locate(1, line);
	rlutil::setChar(200);
	for (auto i = 2; i < rlutil::tcols(); i++)
	{
		rlutil::locate(i, line);
		rlutil::setChar(205);
	}
	rlutil::locate(rlutil::tcols(), line);
	rlutil::setChar(188);
}

int main()
{
	rlutil::hidecursor();
	rlutil::setConsoleTitle("RPG TEST");
	rlutil::setColor(15);
	rlutil::cls();
	lineCreateUp(1);
	rlutil::setColor(10);
	std::cout << std::endl << " RPG COMMAND LINE TEST - ALPHA" << std::endl;
	lineCreateDown(3);
	std::cout << std::endl;
	rlutil::setColor(15);
	LeBob moi, gob1, gob2;
	Map map1;
	map1.targetChange(&moi);
	gob1.nameChange("Gobelin1"); gob2.nameChange("Gobelin2");
	gob1.setStats(50, 0); gob2.setStats(50, 0);
	gob1.targetChange(&moi); gob2.targetChange(&moi);
	std::cout << "Enter Player Name : ";
	std::string temp;
	std::cin >> temp;
	std::cout << std::endl;
	moi.nameChange(temp);

	moi.weaponChange("Short Metal Sword", 11);

	auto action_made(false);
	auto nb_turn = 1;

	while (moi.estVivant())
	{
		rlutil::cls();
		lineCreateUp(1);
		std::cout << std::endl;
		helpCommand();
		std::cout << " Current Target : ";
		if (moi.hasTarget())
			std::cout << moi.cibleActuel->monNom() << std::endl;
		else
			std::cout << "No target" << std::endl;
		lineCreateDown(5);
		std::cout << std::endl;
		rlutil::setBackgroundColor(rlutil::BLUE);
		std::cout << "Turn " << nb_turn << std::endl;
		rlutil::setBackgroundColor(0);
		int choice = tolower(rlutil::getkey());
		std::cout << std::endl;

		switch (choice)
		{
		case 116: // Target
			if (gob1.estVivant())
				std::cout << "Gobelin (1)" << std::endl;
			if (gob2.estVivant())
				std::cout << "Gobelin (2)" << std::endl;
			switch (rlutil::getkey())
			{
			case 49:
				moi.targetChange(&gob1);
				break;
			case 50:
				moi.targetChange(&gob2);
				break;
			default:
				std::cout << "Target unavaible" << std::endl;
				break;
			}
			std::cout << std::endl;
			break;
		case 97: // Attack
			if (moi.hasTarget())
			{
				moi.attaquer();
				action_made = true;
			}
			else
			{

				std::cout << "You need a target, Press (T)" << std::endl << std::endl;
				rlutil::msleep(1000);
			}
			break;
		case 104: // Health
			moi.boirePotionDeVie();
			action_made = true;
			break;
		case 115: // Show Stats
			rlutil::cls();
			lineCreateUp(1);
			std::cout << std::endl << "   Stats" << std::endl;
			lineCreateDown(3);
			std::cout << std::endl;
			moi.showStatus();
			rlutil::anykey("Press Anykey to quit status menu");
			break;
		case 101: // ENM
			rlutil::cls();
			lineCreateUp(1);
			std::cout << std::endl << "   Ennemies" << std::endl;
			lineCreateDown(3);
			lineCreateUp(4);
			std::cout << std::endl;
			if (gob1.estVivant())
				gob1.showStatus();
			lineCreateDown(8);
			lineCreateUp(9);
			std::cout << std::endl;
			if (gob2.estVivant())
				gob2.showStatus();
			lineCreateDown(13);
			std::cout << std::endl << std::endl;
			rlutil::anykey("                                         Press Anykey to quit ennemies menu");
			break;
		case 109:
			rlutil::cls();
			lineCreateUp(1);
			std::cout << std::endl << "   Map" << std::endl;
			lineCreateDown(3);
			map1.afficherMap(3, 5, 50, 20);
			std::cout << std::endl << std::endl;
			rlutil::anykey("                                         Press Anykey to quit map");
			rlutil::locate(3 + moi.posx, 5 + moi.posy);
		default:
			break;
		}
		if (action_made)
		{
			rlutil::msleep(800);
			rlutil::setBackgroundColor(rlutil::RED);
			std::cout << std::endl << "Ennemies turn." << std::endl << std::endl;
			rlutil::setBackgroundColor(0);
			if (gob1.estVivant())
			{
				gob1.attaquer();
				rlutil::msleep(800);
			}
			if (gob2.estVivant())
				gob2.attaquer();

			nb_turn++;
			rlutil::msleep(800);
			std::cout << std::endl;
			rlutil::setBackgroundColor(rlutil::GREEN);
			rlutil::anykey("Press anykey to start next Turn");
			rlutil::setBackgroundColor(0);
		}
		action_made = false;
	}
	rlutil::msleep(2000);
	rlutil::cls();
	setBackgroundColor(rlutil::RED);
	std::cout << "YOU LOOSE, YOU SUCK" << std::endl;
	rlutil::anykey("Press anykey to QUIT");
	return 0;
}
