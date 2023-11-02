# pragma once
# include "Common.hpp"
# include "Mountain.hpp"

// ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;

	void drawIntermission(double fade) const;
	void drawShutter(double fade) const;
	void drawTime() const;

	void updateGameOver();
	void drawGameOver() const;

private:
	const int32 playGames = 50;
	int32 totalGameCount = 0;
	int32 gameCount = 0;
	int32 clearCount = 0;
	const Array<PetitGame*>& games;
	Array<size_t> gameIndex;
	RenderTexture gameScene;
	double gameTime = 0;
	double gameSpeed = 1.0;
	double tempo = 120.0;
	double finishTime = 0;

	Mountain mountain;
	bool gameOver = false;
	bool restart = false;
	Array<Vec2> SelectTrianglePoint;
};
