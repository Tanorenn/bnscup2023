# pragma once
# include "PetitGame.hpp"

class HundredYen : public PetitGame
{
private:
	//ゲームの進行状態
	enum State
	{
		MOVE,
		GO,
		BACK,
		CLEAR
	};

	const Texture Hand{ U"🤚"_emoji };	//手
	const Texture Coin{ U"🪙"_emoji };	//コイン
	const Texture Leaf{ U"🍂"_emoji };	//葉っぱ
	const Texture Rock{ U"🪨"_emoji };	//石ころ
	Vec2 handPos{ 0, 0 };				//手の座標
	Vec2 coinPos{ 0, 0 };				//コインの座標
	Array<Vec2> leafPos;				//葉っぱの座標
	Array<Vec2> rockPos;				//石ころの座標
	Array<double> leafScale;			//葉っぱの大きさ
	Array<double> rockScale;			//石ころの大きさ
	double GoX = 0;						//手を伸ばしたときのx座標
	double handVelocity = 100.0 * 4;	//手の速度
	bool isCleared = false;				//クリアしたかどうか
	State state = MOVE;					//ゲームの進行状況
	RenderTexture Clear{ SceneSize, Palette::White };				//クリアした時に現れる演出
	double clearT = 0;					//クリアした時に現れる演出用の時間
	uint8 drinkTop = 0;					//クリアした後のドリンクの上半分
	uint8 drinkBottom = 0;				//クリアした後のドリンクの下半分
	Effect effect;						//エフェクト
	Stopwatch effectTimer;				//エフェクト発生タイマー

	//クリアした後に現れる飲み物一覧
	const Array<String> drinks
	{
		U"コーラ",
		U"コーヒー",
		U"エナジー"
	};

public:
	HundredYen()
		:PetitGame{ U"自動販売機" }
	{
		CursorStyle = U"Point";
	}

	void init() override
	{
		leafPos.clear();
		rockPos.clear();
		leafScale.clear();
		rockScale.clear();
		for (auto i : step(6))
		{
			leafPos << Vec2{ Random(0, 250), Random(0, 250) };
			rockPos << Vec2{ Random(0, 250), Random(0, 250) };
			leafScale << Random(0.1, 0.2);
			rockScale << Random(0.1, 0.2);
		}
		coinPos = Vec2{ Random(50, 200), Random(50, 150) };
		handPos = Vec2{ 50, 200 };
		handVelocity = 100.0 * 4;
		double GoX = 0;
		isCleared = false;
		state = MOVE;
		clearT = 0;
		Clear = RenderTexture{ SceneSize, Palette::White };
		drinkTop = Random(drinks.size() - 1);
		drinkBottom = Random(drinks.size() - 1);
		effectTimer.reset();
		CursorStyle = U"Point";
	}

	void update(double t, double gameSpeed) override
	{
		if (state == MOVE)
		{
			handPos.x += handVelocity * gameSpeed * Scene::DeltaTime();
			if (handPos.x > 200)
			{
				handPos.x = 200;
				handVelocity *= -1;
			}
			if (handPos.x < 50)
			{
				handPos.x = 50;
				handVelocity *= -1;
			}
			if (MouseL.down())
			{
				state = GO;
				GoX = handPos.x;
			}
			if (isCleared)
			{
				state = CLEAR;
			}
		}
		else if (state == GO)
		{
			handPos.y -= Abs(handVelocity) * gameSpeed * Scene::DeltaTime() * 3;
			if (Hand.scaled(0.5).regionAt(handPos).intersects(Coin.scaled(0.2).regionAt(coinPos)))
			{
				isCleared = true;
			}
			if (handPos.y < 50)
			{
				handPos.y = 50;
				state = BACK;
			}
		}
		else if (state == BACK)
		{
			effectTimer.start();
			if (effectTimer.sF() > 0.005 / gameSpeed)
			{
				effect.add<SmokeEffect>(handPos, gameSpeed);
				effectTimer.restart();
			}
			handPos.x = GoX + Periodic::Triangle1_1(0.01 / gameSpeed) * 2;
			handPos.y += Abs(handVelocity) * gameSpeed * Scene::DeltaTime() * 3;
			if (handPos.y > 200)
			{
				effectTimer.reset();
				handPos.y = 200;
				state = MOVE;
			}
		}
		else if (state == CLEAR)
		{
			clearT = Min(clearT + Scene::DeltaTime() * gameSpeed * 4, 1.0);
		}
	}

	void draw(double t, double gameSpeed) const override
	{
		Rect{ 0, 0, SceneSize }.draw(Palette::Gray);
		for (auto i : step(leafPos.size()))
		{
			Leaf.scaled(leafScale[i]).drawAt(leafPos[i], ColorF(1, 0.75));
			Rock.scaled(rockScale[i]).drawAt(rockPos[i], ColorF(1, 0.75));
		}
		if (not isCleared)Coin.scaled(0.25).drawAt(coinPos);
		Hand.scaled(0.5).drawAt(handPos);
		Ellipse{ 0, 0, 75, 50 }.draw(Palette::White).drawFrame(2, Palette::Black);
		TextureAsset(U"自動販売機").resized(50, 40).drawAt(25 + Periodic::Triangle1_1(0.015 / gameSpeed) * 2, 20);
		effect.update();


		{
			const ScopedRenderTarget2D target{ Clear };
			for (auto i : step(18))
			{
				Triangle{ SceneCenter, OffsetCircular(SceneCenter, SceneHeight, 20_deg * i), OffsetCircular(SceneCenter, SceneHeight, 20_deg * (i + 1)) }.draw(i % 2 ? Palette::White : Palette::Cyan);
			}
			TextureAsset(drinks[drinkTop])(0, 0, TextureAsset(drinks[drinkTop]).size().x, TextureAsset(drinks[drinkTop]).size().y / 2).resized(150, 75).draw(Arg::bottomCenter(SceneCenter));
			TextureAsset(drinks[drinkBottom])(0, TextureAsset(drinks[drinkBottom]).size().y / 2, TextureAsset(drinks[drinkBottom]).size().x, TextureAsset(drinks[drinkBottom]).size().y / 2).resized(150, 75).draw(Arg::topCenter(SceneCenter));

			FontAsset(U"GameFont")(drinks[drinkTop] + drinks[drinkBottom]).drawAt(25, SceneCenter.movedBy(0, 100), Palette::Black);
		}
		Clear.draw(0, EaseOutBounce(clearT) * SceneHeight - SceneHeight);
	}

	bool isClear() override
	{
		return isCleared;
	}
};
