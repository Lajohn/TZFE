#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(HelloWorld);
	//触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *t,cocos2d::Event *e);
	virtual void onTouchEnded(cocos2d::Touch *t,cocos2d::Event *e);
	//手势移动
	bool doLeft();
	bool doRight();
	bool doUp();
	bool doDown();
	//检查是否游戏结束
	void doCheckGameOver();

	//重置及退出事件
    void menuRestartCallback(cocos2d::Ref* pSender);
    void menuExitCallback(cocos2d::Ref* pSender);

	//创建随机数
	int getRand(int start,int end);

private:
	int firstX,firstY,lastX,lastY;

	void createCards(cocos2d::Size size);

	void autoCreateCard();

	CardSprite* cards[4][4];

	int score;
	cocos2d::Label *scoreTitleLabel;
	cocos2d::Label *scoreLabel;
	cocos2d::Label *restartLabel;
	cocos2d::Label *exitLabel;


	void addScore(int s);


};

#endif // __HELLOWORLD_SCENE_H__
