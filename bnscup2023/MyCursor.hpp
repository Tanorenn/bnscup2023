# pragma once
# include <Siv3D.hpp>


//カーソルの情報
struct CursorInfo
{
	String assetName = U"";			//使用するTextureAssetの名前
	Vec2 offset = Vec2{ 0, 0 };		//描画位置のオフセット
	double scale = 1.0;				//描画の拡大率
};


//オリジナルのカーソル
class MyCursor
{
private:
	//登録された名前と情報
	HashTable<String, CursorInfo> infos;
	//現在のカーソルの名前
	String nowCursorName = U"";
	//現在のカーソルの情報
	CursorInfo nowCursorInfo;

public:
	MyCursor()
		:infos{},
		nowCursorName{ U"" },
		nowCursorInfo{} {}

	void Register(String name, CursorInfo info)
	{
		infos.emplace(name, info);
	}

	void RequestStyle(String styleName)
	{
		nowCursorName = styleName;
	}

	void update()
	{
		nowCursorInfo = infos[nowCursorName];
	}

	void draw() const
	{
		TextureAsset(nowCursorInfo.assetName).scaled(nowCursorInfo.scale).drawAt(Cursor::PosF().movedBy(nowCursorInfo.offset));
	}
};
