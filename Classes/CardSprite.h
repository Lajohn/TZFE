#ifndef _CARD_SPRITE_H_
#define _CARD_SPRITE_H_

#include "cocos2d.h"

class CardSprite:public cocos2d::Sprite
{
public:
	//��Ƭ��ʼ��
	static CardSprite* createCardSprite(int num,cocos2d::Size size,cocos2d::Vec2 position);
	virtual bool init();
	CREATE_FUNC(CardSprite);

	//��ȡ ��������
	int getNum();
	void setNum(int num);

	//��Ƭ��Ӷ���
	void cardAction();

private:
	//��ʾ������
	int num;
	void cardInit(int num,cocos2d::Size size,cocos2d::Vec2 position);

	//������ʾ���ֵĿؼ�
	cocos2d::Label *labelCardNumber;

	//��Ƭ����
	cocos2d::LayerColor *layerColorBG;

	//���¿�Ƭ�����������С
	void updateCard();
};


#endif // !_CARD_SPRITE_H_
