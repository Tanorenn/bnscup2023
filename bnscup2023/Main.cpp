# include "Common.hpp"
# include "Title.hpp"
# include "Game.hpp"
# include "PetitGames.hpp"

void Main()
{
	FontAsset::Register(U"TitleFont", FontMethod::MSDF, 50, U"example/font/RocknRoll/RocknRollOne-Regular.ttf");
	FontAsset(U"TitleFont").setBufferThickness(4);
	FontAsset::Register(U"Menu", FontMethod::MSDF, 40, Typeface::Medium);
	FontAsset::Register(U"Ranking", 40, Typeface::Heavy);
	FontAsset::Register(U"GameScore", 30, Typeface::Light);
	AudioAsset::Register(U"Brick", GMInstrument::Woodblock, PianoKey::C5, 0.2s, 0.1s);

	App manager;
	manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);

	// ゲームシーンから開始したい場合はこのコメントを外す
	//manager.init(State::Game);
	RenderTexture gameScene{ 256,256 };

	while (System::Update())
	{
		ClearPrint();
		{
			const double scale = (double)Scene::Height() / gameScene.height();
			const Vec2 pos{ Scene::CenterF() - gameScene.size() * scale / 2 };
			const Transformer2D transformer{ Mat3x2::Identity(), Mat3x2::Scale(scale).translated(pos) };
			const ScopedRenderTarget2D target{ gameScene.clear(Palette::White) };
			if (not manager.update())
			{
				break;
			}
		}
		gameScene.resized(Scene::Width()).drawAt(Scene::Center(), ColorF{ 0.5 });
		gameScene.resized(Scene::Height()).drawAt(Scene::Center());

	}
}
