#ifndef _CARD_SPRITE_H_
#define _CARD_SPRITE_H_

#include "cocos2d.h"

class CardSprite:public cocos2d::Sprite
{
public:
	//卡片初始化
	static CardSprite* createCardSprite(int num,cocos2d::Size size,cocos2d::Vec2 position);
	virtual bool init();
	CREATE_FUNC(CardSprite);

	//获取 设置数字
	int getNum();
	void setNum(int num);

	//卡片添加动作
	void cardAction();

private:
	//显示的数字
	int num;
	void cardInit(int num,cocos2d::Size size,cocos2d::Vec2 position);

	//用于显示数字的控件
	cocos2d::Label *labelCardNumber;

	//卡片背景
	cocos2d::LayerColor *layerColorBG;

	//更新卡片背景及字体大小
	void updateCard();
};


#endif // !_CARD_SPRITE_H_
