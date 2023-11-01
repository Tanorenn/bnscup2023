# include "Title.hpp"

Title::Title(const InitData& init)
	: IScene{ init }
{
	bgtexts.clear();

	for (auto y : step(6))
	{
		for (auto x : step(6))
		{
			bgtexts << TitleBGText(Vec2{ x * 59 - 50, y * 59 - 50 }, 50);
		}
	}

	SelectTrianglePoint.clear();

	for (auto i : step(4))
	{
		SelectTrianglePoint << Vec2{ 0, 0 };
	}
}

void Title::update()
{
	getData().myCursor.RequestStyle(U"Release");
	if (MouseL.pressed())
	{
		getData().myCursor.RequestStyle(U"Grab");
	}

	//背景の文字更新
	for (auto& bgtext : bgtexts)
	{
		bgtext.update();
	}

	//"すくう"にマウスオーバーしたら
	if (FontAsset(U"TitleSelectFont")(U"すくう").regionAt(40, SceneCenter.movedBy(0, 60)).mouseOver())
	{
		getData().myCursor.RequestStyle(U"Point");
		//選択カーソルの座標更新
		SelectTrianglePoint[0] = SceneCenter.movedBy(-65, 70) + Vec2{0, Periodic::Jump0_1(0.5) * 8};
		SelectTrianglePoint[2] = SceneCenter.movedBy(-65, 70) - Vec2{0, Periodic::Jump0_1(0.5) * 8};
		SelectTrianglePoint[1] = SceneCenter.movedBy(-50, 70);
		SelectTrianglePoint[3] = SceneCenter.movedBy(-60, 70);
		//マウスクリックでゲームシーンに移動
		if (MouseL.down())
		{
			changeScene(State::Game);
		}
	}
	//"おわる"にマウスオーバーしたら
	else if (FontAsset(U"TitleSelectFont")(U"おわる").regionAt(40, SceneCenter.movedBy(0, 95)).mouseOver())
	{
		getData().myCursor.RequestStyle(U"Point");
		//選択カーソルの座標更新
		SelectTrianglePoint[0] = SceneCenter.movedBy(-65, 105) + Vec2{ 0, Periodic::Jump0_1(0.5) * 8 };
		SelectTrianglePoint[2] = SceneCenter.movedBy(-65, 105) - Vec2{ 0, Periodic::Jump0_1(0.5) * 8 };
		SelectTrianglePoint[1] = SceneCenter.movedBy(-50, 105);
		SelectTrianglePoint[3] = SceneCenter.movedBy(-60, 105);
		//マウスクリックで終了
		if (MouseL.down())
		{
			System::Exit();
		}
	}

	getData().myCursor.update();

	if (KeyEnter.down())
	{
		changeScene(State::Game);
	}
}

void Title::draw() const
{
	for (const auto& bgtext : bgtexts)
	{
		bgtext.draw();
	}
	TextureAsset(U"Logo").scaled(0.075).drawAt(SceneCenter);
	FontAsset(U"TitleSelectFont")(U"すくう").drawAt(40, SceneCenter.movedBy(2, 62), Palette::Black);
	FontAsset(U"TitleSelectFont")(U"すくう").drawAt(40, SceneCenter.movedBy(0, 60), Palette::White);
	FontAsset(U"TitleSelectFont")(U"おわる").drawAt(40, SceneCenter.movedBy(2, 97), Palette::Black);
	FontAsset(U"TitleSelectFont")(U"おわる").drawAt(40, SceneCenter.movedBy(0, 95), Palette::White);

	//選択カーソル描画
	if (FontAsset(U"TitleSelectFont")(U"すくう").regionAt(40, SceneCenter.movedBy(0, 60)).mouseOver() or FontAsset(U"TitleSelectFont")(U"おわる").regionAt(40, SceneCenter.movedBy(0, 95)).mouseOver())
	{
		Triangle selectTop{ SelectTrianglePoint[0], SelectTrianglePoint[1], SelectTrianglePoint[3] };
		selectTop.drawFrame(0.5, Palette::Black);
		selectTop.draw(ColorF(1 - Periodic::Jump0_1(0.5) * 0.25));
		Triangle selectBottom{ SelectTrianglePoint[3], SelectTrianglePoint[1], SelectTrianglePoint[2] };
		selectBottom.drawFrame(0.5, Palette::Black);
		selectBottom.draw(ColorF(0.5 + Periodic::Jump0_1(0.5) * 0.5));
	}

	getData().myCursor.draw();
}
