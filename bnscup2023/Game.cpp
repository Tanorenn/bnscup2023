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
	gameTime = -1.0;

}

void Game::update()
{
	gameTime += gameSpeed * Scene::DeltaTime();
	auto& game = games[gameIndex[gameCount]];
	game->update(Clamp(gameTime,0.0,1.0), gameSpeed);
	if (KeyEnter.down() or gameTime>=2.0) {
		if (gameCount < Min(playGames, (int32)gameIndex.size()) - 1) {
			gameCount++;
			games[gameIndex[gameCount]]->init();
			if (gameCount % 3)tempo += 10.0;
			finishTime = 60.0 * 8 / tempo;
			gameSpeed = 1.0 / finishTime;
			gameTime = -1.0;
		}
		else changeScene(State::Title);
	}
}

void Game::draw() const
{
	const auto& game = getData().petitGames[gameIndex[gameCount]];
	{
		ScopedRenderTarget2D target(gameScene.clear(Palette::White));
		game->draw(Clamp(gameTime, 0.0, 1.0), gameSpeed);
		if(gameTime>=0)drawTime();

	}
	double fade = 0;
	if (gameTime < 0)fade = Clamp((0.5 + gameTime) * 8, 0.0, 1.0);
	else if (gameTime > 1.0)fade = Clamp(1.0 - (gameTime - 1.0) * 8, 0.0, 1.0);
	else fade = 1.0;
	drawIntermission(fade);
	if (gameTime < 0)
	{
		FontAsset(U"TitleSelectFont")(game->startCall).drawAt(60,SceneCenter.movedBy(2, 2), ColorF{ 0.0,0.4 });
		FontAsset(U"TitleSelectFont")(game->startCall).drawAt(60,SceneCenter);
	}

}

void Game::drawIntermission(double fade) const
{
	const auto& game = getData().petitGames[gameIndex[gameCount]];
	FontAsset(U"GameFont")(game->title).drawAt(40, SceneCenter.movedBy(0, -100));
	gameScene.scaled(0.5 + fade / 2).drawAt(SceneCenter);
	if (gameTime > 1.1) {
		if (game->isClear())FontAsset(U"GameFont")(U"〇").drawAt(150, SceneCenter.movedBy(0,-10), Palette::Orangered);
		else FontAsset(U"GameFont")(U"×").drawAt(230, SceneCenter.movedBy(0,-36), Palette::Mediumblue);
	}
}

void Game::drawTime() const {
	int32 time = (1.0 - Clamp(gameTime, 0.0, 1.0)) * 8;
	Rect{ 20,220,time * 220/8,20 }.draw();
	if(time<=3)FontAsset(U"GameFont")(Format(time)).drawAt(40, 20,210, Palette::Yellow);
}
