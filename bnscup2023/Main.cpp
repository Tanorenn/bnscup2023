# include "Common.hpp"
# include "Title.hpp"
# include "Game.hpp"
# include "PetitGames.hpp"

void Main()
{
	Window::Resize(800, 600);
	Scene::Resize(800, 600);
	Scene::SetResizeMode(ResizeMode::Keep);

	FontAsset::Register(U"TitleFont", FontMethod::MSDF, 50, U"example/font/RocknRoll/RocknRollOne-Regular.ttf");
	FontAsset(U"TitleFont").setBufferThickness(4);
	FontAsset::Register(U"Menu", FontMethod::MSDF, 40, Typeface::Medium);
	FontAsset::Register(U"Ranking", 40, Typeface::Heavy);
	FontAsset::Register(U"GameScore", 30, Typeface::Light);

	FontAsset::Register(U"TitleBGFont", FontMethod::Bitmap, 13, Typeface::Bold);
	FontAsset::Register(U"TitleSelectFont", FontMethod::SDF, 120, U"Font/Buildingsandundertherailwaytracks-Regular.otf", FontStyle::Bitmap);
	TextureAsset::Register(U"Logo", U"Image/logo.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Cursor_Point", U"Image/Cursor_Point.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Cursor_Grab", U"Image/Cursor_Grab.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Cursor_Release", U"Image/Cursor_Release.png", TextureDesc::Mipped);
	TextureAsset::Load(U"Cursor_Point");
	TextureAsset::Load(U"Cursor_Grab");
	TextureAsset::Load(U"Cursor_Release");

	AudioAsset::Register(U"Brick", GMInstrument::Woodblock, PianoKey::C5, 0.2s, 0.1s);

	App manager;
	manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);

	//ゲーム内で使うマウスカーソルの登録
	manager.get().get()->myCursor.Register(U"Point", CursorInfo{ U"Cursor_Point", Vec2{ 0, 0 }, 0.025 });
	manager.get().get()->myCursor.Register(U"Grab", CursorInfo{ U"Cursor_Grab", Vec2{ 0, 0 }, 0.025 });
	manager.get().get()->myCursor.Register(U"Release", CursorInfo{ U"Cursor_Release", Vec2{ 0, 0 }, 0.025 });
	manager.get().get()->myCursor.RequestStyle(U"Release");
	manager.get().get()->myCursor.update();


	// ゲームシーンから開始したい場合はこのコメントを外す
	//manager.init(State::Game);
	
	// RenderTextureの拡大縮小時にぼやけないようにする
	const ScopedRenderStates2D state(SamplerState::ClampNearest);
	RenderTexture gameScene{ SceneSize };

	while (System::Update())
	{
		ClearPrint();

		{
			Cursor::RequestStyle(CursorStyle::Hidden);

			const double scale = (double)Scene::Height() / gameScene.height();
			const Vec2 pos{ Scene::CenterF() - gameScene.size() * scale / 2 };
			const Transformer2D transformer{ Mat3x2::Identity(), Mat3x2::Scale(scale).translated(pos) };
			const ScopedRenderTarget2D target{ gameScene.clear(ColorF{ 0.6, 0.8, 0.7 }) };

			if (not manager.update())
			{
				break;
			}
		}

		{
			//const ScopedRenderStates2D sampler{ SamplerState::ClampNearest };
			gameScene.resized(Scene::Width()).drawAt(Scene::Center(), ColorF{ 0.5 });
			gameScene.resized(Scene::Height()).drawAt(Scene::Center());
		}
	}
}
