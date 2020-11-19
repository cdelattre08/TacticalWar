#pragma once

#include <vector>
#include <Environment.h>
#include <Obstacle.h>

namespace tw
{
	enum class Orientation {
		TOP_RIGHT,
		TOP_LEFT,
		BOTTOM_RIGHT,
		BOTTOM_LEFT
	};

	class Position
	{
	private:
		int x;
		int y;

	public:
		inline Position(int x, int y)
			: x(x), y(y)
		{}

		inline void setX(int x) {
			this->x = x;
		}

		inline void setY(int y) {
			this->y = y;
		}

		inline int getX() {
			return x;
		}

		inline int getY() {
			return y;
		}
	};

	
	
	class Pathfinder
	{
	private:
		Pathfinder();
		~Pathfinder();

		static Pathfinder * instance;

	public:

		static Pathfinder * getInstance();

		Orientation getOrientationFromPosition(Position p1, Position p2);
		std::vector<Position> getPath(Position startPosition, Position endPosition, Environment * environment, std::vector<Obstacle*> obstacles);
		int TotalCostFromStartToEnd();
	};
}
