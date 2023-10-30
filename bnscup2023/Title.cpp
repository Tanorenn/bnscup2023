# include "Title.hpp"

Title::Title(const InitData& init)
	: IScene{ init } {}

void Title::update()
{
	if (KeyEnter.down())
	{
		changeScene(State::Game);
	}
}

void Title::draw() const
{
	FontAsset(U"TitleFont")(U"Title").drawAt(SceneCenter, Palette::Black);
}
