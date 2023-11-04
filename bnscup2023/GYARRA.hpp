# pragma once
# include "PetitGame.hpp"

class GYARRA : public PetitGame
{
private:
	Vec2 gyarraPos{ -50, 150 };
	bool grab = false;
	Vec2 pinPos = { 0, 0 };
	Circle pin{ pinPos, 15 };
	RectF pinBar{ Arg::topCenter(pinPos), 5, 150 };
	Line arrow{ pinPos.movedBy(25, 25), pinPos.movedBy(25, -25) };
	bool isCleared = false;
	bool isFallen = false;

public:
	GYARRA()
		:PetitGame{ U"ギャーア君",U"GYARRABGM" }
	{
	}

	void init() override
	{
		gyarraPos = Vec2{ -50, 150 };
		pinPos = Vec2{ Random(100, 150), 80 };
		pin = Circle{ pinPos, 20 };
		pinBar = RectF{ Arg::topCenter(pinPos), 10, 120 };
		arrow = Line{ pinPos.movedBy(35, 25), pinPos.movedBy(35, -25) };
		grab = false;
		isCleared = false;
		isFallen = false;
		CursorStyle = U"Release";
	}

	void update(double t, double gameSpeed) override
	{
		CursorStyle = U"Release";
		//ピンをつかんだら掴んだ判定オン
		if (pin.leftPressed())
		{
			grab = true;
		}
		//掴んでたらピンの座標更新
		if (grab and MouseL.pressed())
		{
			CursorStyle = U"Grab";
			pinPos.y = Clamp(Cursor::PosF().y, 0.0, 80.0);
		}
		else if (not MouseL.pressed())
		{
			grab = false;
		}
		//ピンにぶつかったら止まる
		if (not TextureAsset(U"ギャーア" + Format(1 + (int)Periodic::Square0_1(0.01 / gameSpeed))).mirrored().resized(50, 50).region(gyarraPos).intersects(pinBar))
		{
			gyarraPos.x += 400 * Scene::DeltaTime() * gameSpeed;
		}
		//170より先に行くとクリア
		if (gyarraPos.x > 170)
		{
			isCleared = true;
		}

		pin.setPos(pinPos);
		pinBar.setPos(Arg::topCenter(pinPos));
	}

	void draw(double t, double gameSpeed) const override
	{
		RectF{ 0, 0, SceneSize }.draw(Arg::top = Palette::Seagreen, Arg::bottom = Palette::Palegreen);

		//ゴールとギャーア
		TextureAsset(U"ゴール1").resized(100, 100).draw(175, 100);
		TextureAsset(U"ギャーア" + Format(1 + (int)Periodic::Square0_1(0.05 / gameSpeed))).mirrored().resized(50, 50).draw(gyarraPos);
		TextureAsset(U"ゴール2").resized(100, 100).draw(175, 100);
		FontAsset(U"GYARR")(U"GOAL").drawAt(25, 225, 130, HSV(360 * t * 3, 1, 1, 0.3));

		//ピンと矢印
		pinBar.drawFrame(1, Palette::Black).draw(Palette::Darkblue);
		pin.drawFrame(1, Palette::Black).draw(Palette::Peru);
		arrow.drawArrow(10, Vec2{ 20, 20 }, HSV(0, Periodic::Square0_1(0.05 / gameSpeed) * 0.2 + 0.8 , 1));

		//地面
		RectF{ 0, 200, 200, 10 }.drawFrame(2, Palette::Midnightblue).draw(Palette::Mediumpurple);
		RectF{ 200, 200, 200, 10 }.drawFrame(2, Palette::Midnightblue).draw(Palette::Gold);

		if (isCleared)
		{
			FontAsset(U"GYARR")(U"不正解者が全員ゴールしました！").drawAt(TextStyle::Outline(0, 1, Palette::Black), 20, SceneCenter, Palette::Magenta);
		}
	}

	bool isClear() override
	{
		return isCleared;
	}
};
