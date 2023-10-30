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

}

void Game::update()
{
	gameTime += gameSpeed * Scene::DeltaTime();
	auto& game = games[gameIndex[gameCount]];
	game->update(Clamp(gameTime,0.0,1.0), gameSpeed);
	if (KeyEnter.down() or gameTime>=2.5) {
		if (gameCount < Min(playGames, (int32)gameIndex.size()) - 1) {
			gameCount++;
			games[gameIndex[gameCount]]->init();
			if (gameCount % 5)tempo += 10.0;
			finishTime = 60.0 * 8 / tempo;
			gameSpeed = 1.0 / finishTime;
			gameTime = -0.5;
		}
		else changeScene(State::Title);
	}
}

void Game::draw() const
{
	const auto& game = getData().petitGames[gameIndex[gameCount]];
	Print << game->title;
	{
		ScopedRenderTarget2D target(gameScene.clear(Palette::White));
		game->draw(Clamp(gameTime, 0.0, 1.0), gameSpeed);
	}
	double fade = Clamp((1.0-Abs(gameTime-0.5))*10,0.0,1.0);
	drawIntermission(fade);
	if (gameTime < 0)
	{
		FontAsset(U"TitleSelectFont")(game->startCall).drawAt(60,SceneCenter.movedBy(2, 2), ColorF{ 0.0,0.4 });
		FontAsset(U"TitleSelectFont")(game->startCall).drawAt(60,SceneCenter);
	}

}

void Game::updateGame()
{

}
void Game::drawGame() const
{

}
void Game::updateIntermission()
{

}
void Game::drawIntermission(double fade) const
{
	const auto& game = getData().petitGames[gameIndex[gameCount]];
	FontAsset(U"TitleSelectFont")(game->title).drawAt(40, SceneCenter.movedBy(0, -100));
	if (gameTime > 0.5) {
		if (game->isClear())FontAsset(U"TitleSelectFont")(U"〇").drawAt(40, SceneCenter.movedBy(100, -30), Palette::Orangered);
		else FontAsset(U"TitleSelectFont")(U"×").drawAt(40, SceneCenter.movedBy(75, -30), Palette::Mediumblue);
	}
	gameScene.scaled(0.5+fade/2).drawAt(SceneCenter);
}
