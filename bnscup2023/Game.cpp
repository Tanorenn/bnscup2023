# include "Game.hpp"

Game::Game(const InitData& init)
	: IScene{ init },
	games{ getData().petitGames },
	gameIndex{getData().petitGames.size()},
	gameScene{ SceneSize, Palette::White }
{
	gameIndex = Array<size_t>(getData().petitGames.size(), 0);
	for (int i = 0; i < gameIndex.size(); i++)gameIndex[i] = i;
	gameIndex.shuffle();
	games[gameIndex[0]]->init();
	finishTime = 60.0 * 8 / tempo;
	gameSpeed = 1.0 / finishTime;
	gameTime = -0.5;

	mountain = Mountain{ 20, 20 }
		._setYStart(SceneHeight + 50)
		._setYEnd(SceneCenter.y + 70)
		._setXStart(SceneWidth * 3)
		._setXEnd(SceneWidth + 10)
		._setOctave(2)
		._setScale(20.0)
		._setVariation(40.0)
		._setEasingFunc(EaseOutSine);

	mountain.update();
}

void Game::update()
{
	gameTime += gameSpeed * Scene::DeltaTime();
	auto& game = games[gameIndex[gameCount]];
	if (0.0 <= gameTime and gameTime <= 1.0)game->update(Clamp(gameTime, 0.0, 1.0), gameSpeed);
	getData().myCursor.RequestStyle(game->CursorStyle);
	getData().myCursor.update();
	if (gameOver) {

	}


	if (KeyEnter.down() or gameTime>=1.5) {
		totalGameCount++;
		if (game->isClear())clearCount++;
		if(not game->isClear() and clearCount - totalGameCount <= -4) {
			gameTime = 999;
			gameOver = true;
			changeScene(State::Title);
		}
		else if (totalGameCount < playGames) {
			if (gameCount == gameIndex.size() - Clamp((int)gameIndex.size() - 5, 1, 3)) {
				gameIndex.shuffle();
				gameCount = 0;
			}
			else gameCount++;
			games[gameIndex[gameCount]]->init();
			if (totalGameCount % 3 == 0)tempo += 10.0;
			finishTime = 60.0 * 8 / tempo;
			gameSpeed = 1.0 / finishTime;
			gameTime = -0.5;
		}
		else changeScene(State::Title);
	}
}

void Game::draw() const
{
	Rect{ 0, 0, SceneSize }.draw(ColorF(0.1, 0.1, 0.2));
	mountain.drawLine(1, Palette::Azure.withAlpha(100));

	if (gameOver) {
		drawGameOver();
		return;
	}
	const auto& game = getData().petitGames[gameIndex[gameCount]];
	double fade = 0;
	fade = 1;
	if (gameTime < 0)fade = Clamp((0.2 + gameTime) * 8, 0.0, 1.0);
	else if (gameTime > 1.0)fade = Clamp(1.0 - (gameTime - 1.0) * 8, 0.0, 1.0);
	else fade = 1.0;
	{
		ScopedRenderTarget2D target(gameScene.clear(Palette::White));
		game->draw(Clamp(gameTime, 0.0, 1.0), gameSpeed);
		if(gameTime>=0)drawTime();
		drawShutter(fade);

	}

	if (gameTime > 1.0 and totalGameCount - clearCount >= 3 and not game->isClear()) {
		drawIntermission(1);
	}
	else {
		drawIntermission(fade);
	}

	if (gameTime < 0 and totalGameCount - clearCount < 4)
	{
		if (not totalGameCount == 0 and totalGameCount % 3 == 0) FontAsset(U"ScoreFont")(U"Speed UP!").drawAt(20, SceneCenter.movedBy(0, -30), Palette::Yellow);
		FontAsset(U"TitleSelectFont")(game->startCall).drawAt(60,SceneCenter.movedBy(2, 2), ColorF{ 0.0,0.4 });
		FontAsset(U"TitleSelectFont")(game->startCall).drawAt(60,SceneCenter);
	}

	getData().myCursor.draw();
}

void Game::drawIntermission(double fade) const
{
	const auto& game = getData().petitGames[gameIndex[gameCount]];
	FontAsset(U"GameFont")(game->title).drawAt(40, SceneCenter.movedBy(0, -100));
	if (gameTime > 1.0 and game->isClear()) {
		FontAsset(U"ScoreFont")(999).regionAt(20, 30, 80).stretched(5, 5).drawFrame(3, ColorF{ 0.9,0.9,0.6 });
		if ((int32)(gameTime * 16) % 2 == 1)FontAsset(U"ScoreFont")(U"{:03}"_fmt(clearCount + 1)).drawAt(20, 30, 80);

	}
	else {
		FontAsset(U"ScoreFont")(999).regionAt(20, 30, 80).stretched(5, 5).drawFrame(3, ColorF{ 0.9,0.9,0.6 });
		FontAsset(U"ScoreFont")(U"{:03}"_fmt(clearCount)).drawAt(20, 30, 80);
	}

	if (gameTime > 1.0 and not game->isClear()) {
		Vec2 heartPos{ 50,225 };
		for (int i : step(Max(0,clearCount - totalGameCount + 3))) {
			Shape2D::Heart(15, heartPos).draw(Palette::Red);
			heartPos.x += 40;
		}
		Shape2D::Heart(15, heartPos).draw(ColorF{ Palette::Mediumblue,EaseInOutSine(Clamp(3.0 - gameTime*2,0.0,1.0)) });
	}
	else {
		for (int i : step(clearCount - totalGameCount + 4)) {
			Shape2D::Heart(15, Vec2{ 50 + i * 40,225 }).draw(Palette::Red);
		}
	}


	gameScene.scaled(0.5 + fade / 2).drawAt(SceneCenter);
	//if (gameTime < 0 or gameTime > 1) {
	//	RectF rec = gameScene.scaled(0.5 + fade / 2).regionAt(SceneCenter);
	//	rec.h *= EaseOutSine(1.0 - fade);
	//	rec.draw(ColorF{ 0.5 }).drawFrame(4, ColorF{ 0.3 });
	//	double kankaku = 32 * (0.5 + fade / 2);
	//	for (double y = rec.bottomY() - kankaku; y > rec.topY(); y -= kankaku) {
	//		Line(rec.leftX(), y, rec.rightX(), y).draw(2, ColorF{ 0.3 });
	//	}
	//}
	if (gameTime > 1.0) {
		if (game->isClear())FontAsset(U"GameFont")(U"〇").drawAt(150, SceneCenter.movedBy(0,-10), Palette::Orangered);
		else FontAsset(U"GameFont")(U"×").drawAt(230, SceneCenter.movedBy(0,-36), Palette::Mediumblue);
	}
}

void Game::drawShutter(double fade) const {
	const double height = SceneHeight * EaseOutSine(1.0 - fade);
	const RectF rect{ 0,0,SceneWidth,height };
	rect.draw(ColorF{ 0.5 }).drawFrame(4, ColorF{ 0.3 });
	for (double y = rect.bottomY() - 32; y > rect.topY(); y -= 32) {
		Line(rect.leftX(), y, rect.rightX(), y).draw(2, ColorF{ 0.3 });
	}
}

void Game::drawTime() const {
	int32 time = (1.0 - Clamp(gameTime, 0.0, 1.0)) * 8;
	for (auto i : step(8))
	{
		Rect{ 20 + i * 25, 240, 25, 5 }.draw(HSV(10 + 100 - (8 - i) * 12.5, 0.5, 1.0, 0.5 + (time - i - 1) * 0.5));
	}
	//Rect{ 20,220,time * 220/8,20 }.draw();
	if(time<=3)FontAsset(U"GameFont")(Format(time)).drawAt(40, 20,210, Palette::Yellow);
}

void Game::updateGameOver() {
	
}

void Game::drawGameOver() const {
	FontAsset(U"TitleFont")(U"GAME OVER").drawAt(SceneCenter.movedBy(0, -60), Palette::Red);
	FontAsset(U"GameFont")(U"SCORE {:03}"_fmt(clearCount)).drawAt(SceneCenter.movedBy(0, -10), Palette::Yellow);
	FontAsset(U"TitleSelectFont")(U"もういちど すくう").drawAt(SceneCenter.movedBy(2, 62), Palette::Black);
	FontAsset(U"TitleSelectFont")(U"もういちど すくう").drawAt(SceneCenter.movedBy(0, 60));
	FontAsset(U"TitleSelectFont")(U"タイトルへ　もどる").drawAt(SceneCenter.movedBy(0, 97), Palette::Black);
	FontAsset(U"TitleSelectFont")(U"タイトルへ　もどる").drawAt(SceneCenter.movedBy(0, 95));

}
