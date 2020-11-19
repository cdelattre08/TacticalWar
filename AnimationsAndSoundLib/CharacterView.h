#pragma once

#include "pch.h"
#include "AbstractCharacterView.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Pathfinder.h>
#include <deque>
#include <map>

namespace tw
{
	enum class Animation
	{
		IDLE,
		RUN,
		ATTACK1,
		ATTACK2,
		DIE,
		TAKE_DAMAGE
	};

	class CharacterView : public AbstractCharacterView<sf::Sprite*>
	{
	private:
		static std::map<std::string, sf::Texture*> * textureCache;
		static sf::Texture* getCachedTexture(std::string path);

		Orientation orientation;
		std::map<Orientation, std::map<Animation, std::vector<sf::Sprite*> > > animationsMap;
		
		double elsetime = 0;
		
		std::vector<sf::Sprite*> loadAnimation(std::string filename);
		std::deque<std::string> positionView;

	public:
		CharacterView(BaseCharacterModel * model);
		virtual ~CharacterView();
		virtual sf::Sprite * getImageToDraw();
		virtual void update(float deltatime);

		void setOrientation(Orientation orientation)
		{
			this->orientation = orientation;
		}
	};
}