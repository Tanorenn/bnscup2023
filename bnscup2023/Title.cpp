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
	for (auto& bgtext : bgtexts)
	{
		bgtext.update();
	}

	if (FontAsset(U"TitleSelectFont")(U"すくう").regionAt(40, SceneCenter.movedBy(0, 60)).mouseOver())
	{
		SelectTrianglePoint[0] = SceneCenter.movedBy(-65, 70) + Vec2{0, Periodic::Jump0_1(0.5) * 8};
		SelectTrianglePoint[2] = SceneCenter.movedBy(-65, 70) - Vec2{0, Periodic::Jump0_1(0.5) * 8};
		SelectTrianglePoint[1] = SceneCenter.movedBy(-50, 70);
		SelectTrianglePoint[3] = SceneCenter.movedBy(-60, 70);

		if (MouseL.down())
		{
			changeScene(State::Game);
		}
	}
	else if (FontAsset(U"TitleSelectFont")(U"おわる").regionAt(40, SceneCenter.movedBy(0, 95)).mouseOver())
	{
		SelectTrianglePoint[0] = SceneCenter.movedBy(-65, 105) + Vec2{ 0, Periodic::Jump0_1(0.5) * 8 };
		SelectTrianglePoint[2] = SceneCenter.movedBy(-65, 105) - Vec2{ 0, Periodic::Jump0_1(0.5) * 8 };
		SelectTrianglePoint[1] = SceneCenter.movedBy(-50, 105);
		SelectTrianglePoint[3] = SceneCenter.movedBy(-60, 105);

		if (MouseL.down())
		{
			System::Exit();
		}
	}

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

	if (FontAsset(U"TitleSelectFont")(U"すくう").regionAt(40, SceneCenter.movedBy(0, 60)).mouseOver() or FontAsset(U"TitleSelectFont")(U"おわる").regionAt(40, SceneCenter.movedBy(0, 95)).mouseOver())
	{
		Triangle{ SelectTrianglePoint[0], SelectTrianglePoint[1], SelectTrianglePoint[3] }.draw(ColorF(1 - Periodic::Jump0_1(0.5) * 0.25)).drawFrame(0.7, Palette::Black);
		Triangle{ SelectTrianglePoint[3], SelectTrianglePoint[1], SelectTrianglePoint[2] }.draw(ColorF(0.5 + Periodic::Jump0_1(0.5) * 0.5)).drawFrame(0.7, Palette::Black);
	}
}
