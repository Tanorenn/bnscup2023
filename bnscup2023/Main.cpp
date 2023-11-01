# include "Common.hpp"
# include "Title.hpp"
# include "Game.hpp"
# include "PetitGames.hpp"

void Main()
{
	Window::Resize(800, 600);
	Scene::Resize(800, 600);
	Scene::SetResizeMode(ResizeMode::Keep);

	FontAsset::Register(U"GameFont", FontMethod::MSDF, 150, U"example/font/RocknRoll/RocknRollOne-Regular.ttf");
	FontAsset::Register(U"ScoreFont", 20, U"example/font/RocknRoll/RocknRollOne-Regular.ttf");
	FontAsset(U"TitleFont").setBufferThickness(4);
	FontAsset::Register(U"Menu", FontMethod::MSDF, 40, Typeface::Medium);
	FontAsset::Register(U"Ranking", 40, Typeface::Heavy);
	FontAsset::Register(U"GameScore", 30, Typeface::Light);

	FontAsset::Register(U"TitleBGFont", FontMethod::Bitmap, 13, Typeface::Bold);
	FontAsset::Register(U"TitleSelectFont", FontMethod::MSDF, 120, U"Font/Buildingsandundertherailwaytracks-Regular.otf", FontStyle::Bitmap);
	//タイトルロゴ
	TextureAsset::Register(U"Logo", U"Image/logo.png", TextureDesc::Mipped);
	//カーソル
	TextureAsset::Register(U"Cursor_Point", U"Image/Cursor_Point.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Cursor_Grab", U"Image/Cursor_Grab.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Cursor_Release", U"Image/Cursor_Release.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Cursor_Hidden", U"Image/Cursor_Hidden.png");

	//自動販売機
	TextureAsset::Register(U"コーラ", U"Image/Cola.png", TextureDesc::Mipped);
	TextureAsset::Register(U"コーヒー", U"Image/Coffee.png", TextureDesc::Mipped);
	TextureAsset::Register(U"エナジー", U"Image/Energy.png", TextureDesc::Mipped);
	TextureAsset::Register(U"まむし", U"Image/RED-VIPER.png", TextureDesc::Mipped);
	TextureAsset::Register(U"自動販売機", U"Image/zihanki.png", TextureDesc::Mipped);
	//食品ロス
	TextureAsset::Register(U"受け皿", U"Image/Catch.png", TextureDesc::Mipped);
	TextureAsset::Register(U"見せ皿", U"Image/Dish.png", TextureDesc::Mipped);

	AudioAsset::Register(U"Brick", GMInstrument::Woodblock, PianoKey::C5, 0.2s, 0.1s);

	App manager;
	manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);

	//ゲーム内で使うマウスカーソルの登録
	manager.get().get()->myCursor.Register(U"Point", CursorInfo{ U"Cursor_Point", Vec2{ 3, 15 }, 0.025 });
	manager.get().get()->myCursor.Register(U"Grab", CursorInfo{ U"Cursor_Grab", Vec2{ 3, 15 }, 0.025 });
	manager.get().get()->myCursor.Register(U"Release", CursorInfo{ U"Cursor_Release", Vec2{ 3, 15 }, 0.025 });
	manager.get().get()->myCursor.Register(U"Hidden", CursorInfo{ U"Cursor_Hidden", Vec2{ 0, 0 }, 0.025 });
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

		//RenderTextureに書き込む
		{
			if(Cursor::Pos().y>=0)Cursor::RequestStyle(CursorStyle::Hidden);

			const double scale = (double)Scene::Height() / gameScene.height();
			const Vec2 pos{ Scene::CenterF() - gameScene.size() * scale / 2 };
			const Transformer2D transformer{ Mat3x2::Identity(), Mat3x2::Scale(scale).translated(pos) };
			const ScopedRenderTarget2D target{ gameScene.clear(ColorF{ 0.6, 0.8, 0.7 }) };

			if (not manager.update())
			{
				break;
			}
		}
		//RenderTexture描画
		{
			//const ScopedRenderStates2D sampler{ SamplerState::ClampNearest };
			gameScene.resized(Scene::Width()).drawAt(Scene::Center(), ColorF{ 0.5 });
			gameScene.resized(Scene::Height()).drawAt(Scene::Center());
		}
	}
}
