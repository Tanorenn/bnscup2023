# pragma once
# include "PetitGame.hpp"
# include "Effect.hpp"

class RendaHero : public PetitGame
{
private:
	Vec2 roboPos{ SceneCenter.x, SceneHeight };
	double roboAngle = 0;
	double roboScale = 1.0;
	bool roboinit = false;
	Vec2 kaijuuPos{ SceneCenter.x, 145 };
	int8 kaijuuNumber = 0;
	int8 kaijuuHP = 5;
	Effect effect;
	Stopwatch stopwatch;
	double clearT = 0;
	bool isCleared = false;

public:
	RendaHero()
		:PetitGame{ U"連打ロボ",U"連打ロボBGM" }
	{
	}

	void init() override
	{
		roboPos = Vec2{ SceneCenter.x, SceneHeight };
		roboAngle = 0;
		roboScale = 1.0;
		roboinit = false;
		kaijuuPos = Vec2{ SceneCenter.x, 145 };
		kaijuuNumber = Random(1, 3);
		kaijuuHP = 5;
		stopwatch.reset();
		clearT = 0;
		isCleared = false;
		CursorStyle = U"Grab";
	}

	void update(double t, double gameSpeed) override
	{
		if (TextureAsset(U"連打怪獣" + Format(kaijuuNumber)).resized(150, 150).regionAt(kaijuuPos).leftClicked() and kaijuuHP > 0)
		{
			effect.add<RendaAttack>(Cursor::PosF(), gameSpeed);
			kaijuuHP--;
		}

		if (kaijuuHP <= 0)
		{
			isCleared = true;
		}

		if (isCleared)
		{
			kaijuuPos.y += Scene::DeltaTime() * gameSpeed * 8 * 50;
			stopwatch.start();
			clearT = stopwatch.sF() * gameSpeed * 8;

			if (0 <= clearT and clearT <= 1.5)
			{
				roboPos.y -= Scene::DeltaTime() * gameSpeed * 4 * (SceneHeight + 200);
			}
			else if (1.5 <= clearT)
			{
				if (not roboinit)
				{
					roboinit = true;
					roboAngle = 60_deg;
					roboPos = Vec2{ -30, 150 };
					roboScale = 0.15;
				}
				roboPos.x += Scene::DeltaTime() * gameSpeed * 4 * 100;
				roboPos.y -= Scene::DeltaTime() * gameSpeed * 4 * 50;
			}

		}
	}

	void draw(double t, double gameSpeed) const override
	{
		if (not isCleared)
		{
			RectF{ 0, 0, SceneWidth, 200 }.draw(Arg::top = Palette::Indigo, Arg::bottom = Palette::Darkred);
		}
		else if (isCleared)
		{
			RectF{ 0, 0, SceneWidth, 200 }.draw(Arg::top = Palette::Paleturquoise, Arg::bottom = Palette::Deepskyblue);
		}
		RectF{ 10, 175, 20, 25 }.draw(Palette::Gray);
		RectF{ 40, 165, 20, 35 }.draw(Palette::Gray.withAlpha(200));
		RectF{ 60, 175, 25, 50 }.draw(Palette::Gray.withAlpha(240));

		TextureAsset(U"連打怪獣" + Format(kaijuuNumber)).resized(150, 150).drawAt(kaijuuPos.x + Periodic::Triangle1_1(0.03 / gameSpeed) * 5, kaijuuPos.y + Periodic::Triangle1_1(0.02 / gameSpeed) * 5, ColorF(1, 1 - clearT));

		RectF{ 70, 165, 50, 35 }.draw(Palette::Gray);
		RectF{ 140, 145, 50, 75 }.draw(Palette::Gray);
		RectF{ 200, 115, 60, 85 }.draw(Palette::Gray);
		RectF{ 230, 165, 30, 35 }.draw(Palette::Gray);

		Circle{ kaijuuPos, 20 }.drawFrame(3, ColorF(1, 0, 0, 1 - clearT));
		Line{ kaijuuPos.movedBy(0, -25), kaijuuPos.movedBy(0, 25) }.draw(3, ColorF(1, 0, 0, 1 - clearT));
		Line{ kaijuuPos.movedBy(-25, 0), kaijuuPos.movedBy(25, 0) }.draw(3, ColorF(1, 0, 0, 1 - clearT));

		RectF{ 103, 75, 50, 5 }.draw(ColorF(1, 0, 0, 1 - clearT));
		RectF{ 103, 75, kaijuuHP * 10, 5 }.draw(ColorF(0, 1, 0, 1 - clearT));

		RectF{ 0, 200, SceneWidth, 200 }.draw(Palette::Gray);

		effect.update();

		TextureAsset(U"連打ロボ").resized(150 * roboScale, 150 * roboScale).rotated(roboAngle).drawAt(roboPos);
	}

	bool isClear() override
	{
		return isCleared;
	}

};
