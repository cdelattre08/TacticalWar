#include "pch.h"
#include "CharacterView.h"

using namespace tw;

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
	testCharacterTexture = getCachedTexture("./assets/Warrior/bottomright-sheet.png");
	//testCharacterTexture = new sf::Texture();
	//testCharacterTexture->loadFromFile("../assets/Warrior/bottomright-sheet.png");
	testCharacterTexture->setSmooth(true);
	testSprite.setTexture(*testCharacterTexture);
	testSprite.setTextureRect(sf::IntRect(0, 288, 173, 224));
	testOffsetX = 78;
	testOffsetY = 48;
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

	return &testSprite;
}

void CharacterView::update(float deltatime)
{

}