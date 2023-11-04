# include "Common.hpp"
# include "Title.hpp"
# include "Game.hpp"
# include "PetitGames.hpp"

void Main()
{
	Window::Resize(800, 600);
	Scene::Resize(800, 600);
	Scene::SetResizeMode(ResizeMode::Keep);

	FontAsset::Register(U"GameFont", FontMethod::MSDF, 150, Resource(U"Font/RocknRollOne-Regular.ttf"));
	FontAsset::Register(U"ScoreFont", 20, Resource(U"Font/RocknRollOne-Regular.ttf"));
	FontAsset::Register(U"GameOverFont", 35, Resource(U"Font/RocknRollOne-Regular.ttf"));
	FontAsset::Register(U"Menu", FontMethod::MSDF, 40, Typeface::Medium);
	FontAsset::Register(U"Ranking", 40, Typeface::Heavy);
	FontAsset::Register(U"GameScore", 30, Typeface::Light);

	FontAsset::Register(U"TitleBGFont", FontMethod::Bitmap, 13, Typeface::Bold);
	FontAsset::Register(U"TitleSelectFont", FontMethod::MSDF, 120, Resource(U"Font/Buildingsandundertherailwaytracks-Regular.otf"), FontStyle::Bitmap);
	//タイトルロゴ
	TextureAsset::Register(U"Logo", Resource(U"Image/logo.png"), TextureDesc::Mipped);
	//カーソル
	TextureAsset::Register(U"Cursor_Point", Resource(U"Image/Cursor_Point.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"Cursor_Grab", Resource(U"Image/Cursor_Grab.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"Cursor_Release", Resource(U"Image/Cursor_Release.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"Cursor_Hidden", Resource(U"Image/Cursor_Hidden.png"));

	//自動販売機
	TextureAsset::Register(U"コーラ", Resource(U"Image/Cola.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"コーヒー", Resource(U"Image/Coffee.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"エナジー", Resource(U"Image/Energy.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"まむし", Resource(U"Image/RED-VIPER.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"自動販売機", Resource(U"Image/zihanki.png"), TextureDesc::Mipped);
	TextureAsset::Load(U"コーラ");
	TextureAsset::Load(U"コーヒー");
	TextureAsset::Load(U"エナジー");
	TextureAsset::Load(U"まむし");
	TextureAsset::Load(U"自動販売機");
	//食品ロス
	TextureAsset::Register(U"受け皿", Resource(U"Image/Catch.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"見せ皿", Resource(U"Image/Dish.png"), TextureDesc::Mipped);
	AudioAsset::Register(U"SaveFoodBGM", Resource(U"Audio/SaveFood.mp3"));
	TextureAsset::Load(U"受け皿");
	TextureAsset::Load(U"見せ皿");
	AudioAsset::Load(U"SaveFoodBGM");
	//ギャーア君
	TextureAsset::Register(U"ギャーア1", Resource(U"Image/GYARR1.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"ギャーア2", Resource(U"Image/GYARR2.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"ゴール1", Resource(U"Image/Goal1.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"ゴール2", Resource(U"Image/Goal2.png"), TextureDesc::Mipped);
	TextureAsset::Load(U"ギャーア1");
	TextureAsset::Load(U"ギャーア2");
	TextureAsset::Load(U"ゴール1");
	TextureAsset::Load(U"ゴール2");
	FontAsset::Register(U"GYARR", FontMethod::SDF, 120, Resource(U"Font/Corporate-Logo-Rounded-Bold-ver3.otf"));
	FontAsset(U"GYARR").preload(U"不正解者が全員ゴールしました！");
	AudioAsset::Register(U"GYARRABGM", Resource(U"Audio/GYARRBGM.mp3"));

	//連打ロボ
	TextureAsset::Register(U"連打ロボ", Resource(U"Image/RendaRobo.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"連打怪獣1", Resource(U"Image/Kaijuu1.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"連打怪獣2", Resource(U"Image/Kaijuu2.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"連打怪獣3", Resource(U"Image/Kaijuu3.png"), TextureDesc::Mipped);
	TextureAsset::Register(U"連打攻撃", U"💥"_emoji, TextureDesc::Mipped);
	AudioAsset::Register(U"連打ロボBGM", Resource(U"Audio/RendaHero.mp3"), Loop::No);
	TextureAsset::Load(U"連打ロボ");
	TextureAsset::Load(U"連打怪獣1");
	TextureAsset::Load(U"連打怪獣2");
	TextureAsset::Load(U"連打怪獣3");
	TextureAsset::Load(U"連打攻撃");
	AudioAsset::Load(U"連打ロボBGM");

	//金魚すくい
	TextureAsset::Register(U"金魚", Resource(U"Image/kingyo2.png"));
	TextureAsset::Register(U"ポイ", Resource(U"Image/poi.png"));
	TextureAsset::Register(U"コップ上", Resource(U"Image/paper_cup.png"));
	TextureAsset::Register(U"コップ下", Resource(U"Image/paper_cup2.png"));
	TextureAsset::Register(U"Siv3dくん", Resource(U"Image/siv3D-gift.png"), TextureDesc::Mipped);
	TextureAsset::Load(U"金魚");
	TextureAsset::Load(U"ポイ");
	TextureAsset::Load(U"コップ上");
	TextureAsset::Load(U"コップ下");
	TextureAsset::Load(U"Siv3dくん");

	AudioAsset::Register(U"SaveTheEarthBGM", Resource(U"Audio/SaveTheEarth.mp3"), Loop::No);
	AudioAsset::Load(U"SaveTheEarthBGM");

	AudioAsset::Register(U"FireFightBGM", Resource(U"Audio/FireFight.mp3"), Loop::No);
	AudioAsset::Load(U"FireFightBGM");

	AudioAsset::Register(U"DreamyRainyBGM", Resource(U"Audio/DreamyRainy.mp3"), Loop::No);
	AudioAsset::Load(U"DreamyRainyBGM");

	AudioAsset::Register(U"Brick", GMInstrument::Woodblock, PianoKey::C5, 0.2s, 0.1s);

	AudioAsset::Register(U"Miss", Resource(U"Audio/やられた2.mp3"));
	AudioAsset::Load(U"Miss");
	AudioAsset::Register(U"やった", Resource(U"Audio/やった！.mp3"));
	AudioAsset::Load(U"やった");

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
