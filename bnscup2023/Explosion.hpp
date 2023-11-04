# pragma once
# include "PetitGame.hpp"

class Explosion : public PetitGame
{
public:
	const Texture bomb{ U"💣"_emoji };
	const Texture button1{ U"🔲"_emoji };
	const Texture button2{ U"🔳"_emoji };
	const Texture collision{ U"💥"_emoji };
	const Font boldFont{ FontMethod::MSDF, 48, Typeface::Bold };
	Point correctPos;
	Point clicked;
	int16 size = 120;
	int16 width = 2;
	int16 height = 2;
	bool isSaved;
	const Array<String> correct = { U"STOP", U"停止", U"とめる", U"阻止", U"中止" };
	const Array<String> wrong = { U"STEP", U"SPOT", U"停学", U"とまと" ,U"注視", U"素子", U"とぬる", U"停正", U"下止",U"上止", U"中上", U"阻上", U"停上"};
	Grid<String> words;
	Font font{24, Typeface::Bold};

	Explosion();
	void init() override;
	void update(double t, double gameSpeed) override;
	void draw(double t, double gameSpeed) const override;
	Point getPos(const Point p) const;
	bool isClear() override;
	bool isNearEnd(const double& t) const;
};


