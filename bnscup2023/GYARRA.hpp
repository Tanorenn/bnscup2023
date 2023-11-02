﻿# pragma once
# include "PetitGame.hpp"

class GYARRA : public PetitGame
{
private:
	Vec2 gyarraPos{ -50, 150 };
	bool grab = false;
	Vec2 pinPos = { 0, 0 };
	Circle pin{ pinPos, 15 };
	RectF pinBar{ Arg::topCenter(pinPos), 5, 150 };
	bool isCleared = false;
	bool isFallen = false;

public:
	GYARRA()
		:PetitGame{ U"ギャーア君" }
	{
	}

	void init() override
	{
		gyarraPos = Vec2{ -50, 150 };
		pinPos = Vec2{ Random(100, 150), 50 };
		pin = Circle{ pinPos, 15 };
		pinBar = RectF{ Arg::topCenter(pinPos), 5, 150 };
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
			pinPos.y = Clamp(Cursor::PosF().y, 0.0, 50.0);
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
		RectF{ 0, 0, SceneSize }.draw(Palette::Silver);
		TextureAsset(U"ギャーア" + Format(1 + (int)Periodic::Square0_1(0.01 / gameSpeed))).mirrored().resized(50, 50).draw(gyarraPos);
		pinBar.drawFrame(1, Palette::Black).draw(Palette::Darkblue);
		pin.drawFrame(1, Palette::Black).draw(Palette::Peru);
		if (isCleared)
		{
			//FontAsset(U"GYARR")(U"不正解者が全員ゴールしました！").drawAt(SceneCenter, Palette::Magenta);
			FontAsset(U"GYARR")(U"不正解者が全員ゴールしました！").drawAt(TextStyle::Outline(0, 1, Palette::Black), 20, SceneCenter, Palette::Magenta);
		}
	}

	bool isClear() override
	{
		return isCleared;
	}
};