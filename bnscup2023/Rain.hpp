# pragma once
# include "PetitGame.hpp"

class DreamyRainy : public PetitGame
{
private:
	const Texture drop{ U"💧"_emoji };
	const Texture cloudRain{ U"🌧️"_emoji };
	const Texture cloud{ U"☁️"_emoji };
	const Texture umbrella{ U"☂️"_emoji };
	const Texture reaju{ U"👫"_emoji };
	const Texture rainbow{ U"🌈"_emoji };
	const Texture love{ U"❤️"_emoji };
	const Texture brokenLove{ U"💔"_emoji };
	const Texture man{ U"🧍‍♂️"_emoji };
	const Texture woman{ U"🧍‍♀️"_emoji };
	Vec2 reajuPos;
	int32 reajuSize;
	Size cloudSize;
	int32 umbrellaSize;
	int32 dropSize;
	int32 dropX;
	Array<Vec2> dropPos;
	Vec2 umbrellaPos;
	double dropTime;
	bool isSaved;
	Vec2 manPos;
public:
	DreamyRainy();
	void init() override;
	void update(double t, double gameSpeed) override;
	void draw(double t, double gameSpeed) const override;
	bool isClear() override;
};
