# pragma once
# include "PetitGame.hpp"

class SaveFood : public PetitGame
{
private:
	double foodBasePosX = -100.0;
	Vec2 foodPos{ -100, 0 };
	uint8 foodNum = 0;
	RectF fallenFood{ foodPos, 30, 5 };
	bool isCleared = false;
	Stopwatch stopwatch;
	double clearT = 0;

	Array<Texture> foods
	{
		Texture{ Emoji{ U"🍔" } },
		Texture{ Emoji{ U"🍣" } },
		Texture{ Emoji{ U"🌭" } },
		Texture{ Emoji{ U"🥪" } },
		Texture{ Emoji{ U"🦀" } },
		Texture{ Emoji{ U"🧇" } },
		Texture{ Emoji{ U"🥩" } },
		Texture{ Emoji{ U"🍕" } },
		Texture{ Emoji{ U"🥗" } },
		Texture{ Emoji{ U"🦞" } },
		Texture{ Emoji{ U"🦐" } },
		Texture{ Emoji{ U"🍩" } }
	};

	const Texture scream{ U"😱"_emoji };

public:
	SaveFood()
		:PetitGame{ U"食品ロス" }
	{
		CursorStyle = U"Hidden";
	}

	void init() override
	{
		foodBasePosX = Random(25, 225);
		foodPos = Vec2{ foodBasePosX, -50 };
		foodNum = Random(foods.size() - 1);
		fallenFood = RectF{ foodPos, 30, 5 };
		isCleared = false;
		stopwatch.reset();
		clearT = 0;
	}

	void update(double t, double gameSpeed) override
	{
		fallenFood.setPos(foodPos);

		if (not isCleared)
		{
			foodPos.y += gameSpeed * 100 * 4 * Scene::DeltaTime();
			foodPos.x = foodBasePosX + Periodic::Sine1_1(0.25 / gameSpeed) * 25;
			if (foodPos.y > 200 and TextureAsset(U"受け皿").resized(80, 60).regionAt(Vec2{ Cursor::PosF().x, 225 }).intersects(fallenFood) and foodPos.y < 220)
			{
				isCleared = true;
				stopwatch.start();
			}
			else if (foodPos.y > 220)
			{
				stopwatch.start();
			}

		}
		else if (isCleared)
		{
			foodPos.y = 210;
			foodPos.x = Cursor::PosF().x - fallenFood.w / 2.0;
		}
		clearT = Min(stopwatch.sF() * 4 * gameSpeed, 1.0);
	}

	void draw(double t, double gameSpeed) const override
	{
		RectF{ 0, 0, SceneSize }.draw(Arg::top = ColorF{ 0.5, 0.7, 0.9 }, Arg::bottom = ColorF{ 0.5, 0.9, 0.7 });

		if (not isCleared)
		{
			scream.scaled(2).drawAt(SceneCenter.movedBy(0, 200 - EaseOutCubic(clearT) * 200), ColorF(1, EaseOutCubic(clearT) * 0.5));
			fallenFood.rotated(t * 1080_deg * 6).drawFrame(2, Palette::Black).draw(Palette::Darkgoldenrod);
		}
		else if (isCleared)
		{
			TextureAsset(U"見せ皿").resized(350, 200).drawAt(SceneCenter.movedBy(-10, -70 + EaseOutCubic(clearT) * 30), ColorF(1, EaseOutCubic(clearT) * 0.5));
			foods[foodNum].drawAt(SceneCenter.movedBy(0, -70 + EaseOutCubic(clearT) * 30), ColorF(1, EaseOutCubic(clearT) * 0.5));
			fallenFood.drawFrame(2, Palette::Black).draw(Palette::Darkgoldenrod);
		}
		TextureAsset(U"受け皿").resized(80, 60).drawAt(Vec2{ Cursor::PosF().x, 225 });
	}

	bool isClear() override
	{
		return isCleared;
	}
};
