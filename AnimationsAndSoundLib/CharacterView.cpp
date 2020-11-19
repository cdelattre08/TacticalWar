#include "pch.h"
#include "CharacterView.h"
#include <iostream>
#include <string>
#include <StringUtils.h>
#include <SFML/System/FileInputStream.hpp>

using namespace tw;
using namespace std;
std::map<std::string, sf::Texture*> * CharacterView::textureCache = NULL;

sf::Texture* CharacterView::getCachedTexture(std::string path)
{
	if (textureCache == NULL)
		textureCache = new std::map<std::string, sf::Texture*>();

	sf::Texture *texture;
	if (textureCache->find(path) != textureCache->end())
	{
		texture = (*textureCache)[path];
	}
	else
	{
		texture = new sf::Texture();
		texture->loadFromFile(path);
		(*textureCache)[path] = texture;
	}

	return texture;
}

CharacterView::CharacterView(BaseCharacterModel * model)
	: AbstractCharacterView<sf::Sprite*>(model)
{
	orientation = Orientation::BOTTOM_RIGHT;
	animationsMap[Orientation::BOTTOM_RIGHT][Animation::RUN] = loadAnimation(model->getGraphicsPath() + "bottomright-sheet");

}

std::vector<sf::Sprite*> CharacterView::loadAnimation(std::string filename)
{
	std::vector<sf::Sprite *> anim;
	sf::Texture *testCharacterTexture = getCachedTexture(filename + ".png");
	sf::FileInputStream stream;
	string str;
	double NbImg = -1;
	int testOffsetX, testOffsetY;

	if (stream.open(filename + ".anim.exode")){
		int length = stream.getSize();
		char * data = new char[length + 1];
		stream.read(data, length);
		data[length] = '\0';
		std::vector<std::string> lines = StringUtils::explode(data, '\n');
		delete data;
		for(int i = 0; i < lines.size(); i++)
			positionView.push_back(lines[i]);	// tant que l'on peut mettre la ligne dans "positionView"	
	} 	
	else
	{
		std::cout << "Echec de l'ouverture du fichier " << filename.c_str() << ".anim.exode" << std::endl;
	}
	for (int y = 0; y < positionView.size(); y++) {		// compte le nombre d'imagne dans le fichier
		if (positionView[y][0] != '\0')
			NbImg++;	
	}

	testCharacterTexture->setSmooth(true);

	for (int i = 0; i < NbImg; i++)
	{
		std::vector<std::string> result = StringUtils::explode(positionView[i],';');
		sf::Sprite * s = new sf::Sprite(*testCharacterTexture, sf::IntRect(atoi(result[0].c_str()), atoi(result[1].c_str()), atoi(result[2].c_str()), atoi(result[3].c_str())));
		/*testOffsetX = std::atof(result[4].c_str());
		testOffsetY = std::atof(result[5].c_str());*/
		//s->setScale(-1, 1);
		//s->setOrigin(atoi(result[4].c_str()), atoi(result[5].c_str()));
		anim.push_back(s);
		result.clear();
	}
	return anim;
}

CharacterView::~CharacterView()
{
	//delete testCharacterTexture;
}

sf::Sprite* CharacterView::getImageToDraw()
{
	// TODO : (team "Animation personnage") : Réaliser le code d'animation du personnage dans cette classe.
	// Cette méthode (getImageToDraw) doit retourner l'image qui devra être dessinée à l'écran (en fonction de où en est l'animation)
	// Vous devrez également utiliser les services de la team "Colorisation" pour obtenir un personnage coloré (personnalisation des couleurs en fonction de l'équipe).
	
	double p = 1, time = elsetime;

	int nbImg = animationsMap[orientation][Animation::RUN].size();
	p /= nbImg;
	int index;
	index = fmod(time / p, nbImg);
	return animationsMap[orientation][Animation::RUN][index];
}

void CharacterView::update(float deltatime)
{
	elsetime += deltatime;
}