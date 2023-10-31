# pragma once
# include "Common.hpp"
// ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;

	void updateGame();
	void drawGame() const;
	void updateIntermission();
	void drawIntermission(double fade) const;
	void drawTime() const;
private:
	const int32 playGames = 5;
	int32 gameCount = 0;
	const Array<PetitGame*>& games;
	Array<size_t> gameIndex;
	RenderTexture gameScene;
	double gameTime=0;
	double gameSpeed = 1.0;
	double tempo = 120.0;
	double finishTime = 0;
};
