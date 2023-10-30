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
}

void Title::update()
{
	for (auto& bgtext : bgtexts)
	{
		bgtext.update();
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
}
