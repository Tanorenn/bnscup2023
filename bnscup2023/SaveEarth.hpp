# pragma once
# include "PetitGame.hpp"

class SaveTheEarth : public PetitGame
{
public:
	const Texture earth{ U"🌏"_emoji };
	const Texture moon{ U"🌝"_emoji };
	const Texture leftMoon{ U"🌗"_emoji };
	const Texture comet{ U"☄️_emoji" };
	const Texture soccerBall{ U"⚽"_emoji };
	const Texture sun{ U"🌞"_emoji };
	const Texture fire{ U"🔥"_emoji };
	double time = 0;
	// ボールの角度
	double ballRad = 0;
	// ボールの中心からの距離
	double ballDist = 0;
	bool isSaved = false;
	bool isBurn = false;

	Vec2 ballPos, moonPos;

	Array<Vec2> starPos;
	Array<double> starSize;

	Stopwatch stopwatch;
	double clearT;

	SaveTheEarth();
	void init() override;
	void update(double t, double gameSpeed) override;
	void draw(double t, double gameSpeed) const override;
	bool isClear() override;
	
};


