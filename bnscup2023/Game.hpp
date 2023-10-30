# pragma once
# include "Common.hpp"
// ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;

private:
	const int32 playGames = 5;
	bool m_isLoaded = false;
	int32 m_gameCount = 0;
	const Array<PetitGame*>& m_games;
	Array<size_t> m_gameIndex;
	RenderTexture gameScene;
	double gameTime=0;
	double gameSpeed = 1.0;
};
