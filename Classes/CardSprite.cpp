#include "CardSprite.h"

USING_NS_CC;

//卡片初始化
CardSprite* CardSprite::createCardSprite(int num,Size size,Vec2 position){
	CardSprite *card=new CardSprite();
	if(card&&card->init()){
		card->autorelease();
		card->cardInit(num,size,position);
		return card;
	}

	CC_SAFE_DELETE(card);

	return NULL;
}

bool CardSprite::init(){
	if(!Sprite::init()){
		return false;
	}
	return true;
}


//获取 设置数字
int CardSprite::getNum(){
	return this->num;
}

void CardSprite::setNum(int num){
	this->num=num;

	char str[10];
	memchr(str,0,10);
	if(num>0){
		sprintf(str,"%d",num);
	}else{
		sprintf(str,"");
	}
	labelCardNumber->setString(str);

	updateCard();
}

void CardSprite::cardInit(int num,cocos2d::Size size,cocos2d::Vec2 position){
	this->num=num;
	this->setContentSize(size);
	this->setPosition(position);

	layerColorBG=LayerColor::create(Color4B(200,190,180,255),size.width-10,size.height-10);
	layerColorBG->ignoreAnchorPointForPosition(false);
	layerColorBG->setAnchorPoint(Vec2(0.5,0.5));
	layerColorBG->setPosition(Vec2(size.width/2,size.height/2));

	char str[10];
	memchr(str,0,10);
	if(num>0){
		sprintf(str,"%d",num);
	}else{
		sprintf(str,"");
	}

	labelCardNumber=Label::createWithSystemFont(str,"Buxton Sketch",size.width*0.4);
	labelCardNumber->setPosition(Vec2((size.width-10)/2,(size.height-10)/2));
	layerColorBG->addChild(labelCardNumber);


	this->addChild(layerColorBG);
}

void CardSprite::updateCard(){
	int fontSize=this->getContentSize().width*0.4;
	Color3B bg=Color3B(200,190,180);

	if(num>=1024){
		fontSize=this->getContentSize().width*0.55;
	}else if(num>=128){
		fontSize=this->getContentSize().width*0.6;
	}else if(num>=16){
		fontSize=this->getContentSize().width*0.65;
	}else if(num>=0){
		fontSize=this->getContentSize().width*0.7;
	}

	switch (num)
	{
	case 0:
		bg=Color3B(200,190,180);
		break;
	case 2:
		bg=Color3B(240,230,220);
		break;
	case 4:
		bg=Color3B(240,215,205);
		break;
	case 8:
		bg=Color3B(240,200,190);
		break;
	case 16:
		bg=Color3B(240,185,175);
		break;
	case 32:
		bg=Color3B(240,170,160);
		break;
	case 64:
		bg=Color3B(240,155,145);
		break;
	case 128:
		bg=Color3B(240,140,130);
		break;
	case 512:
		bg=Color3B(240,125,115);
		break;
	case 1024:
		bg=Color3B(240,110,100);
		break;
	case 2048:
	default:
		bg=Color3B(240,95,85);
		break;
	}

	labelCardNumber->setSystemFontSize(fontSize);
	layerColorBG->setColor(bg);
}


//卡片添加动作
void CardSprite::cardAction(){
	layerColorBG->setScale(0.0f);
	auto scaleTo=ScaleTo::create(0.3f,1.0f);
	layerColorBG->runAction(scaleTo);
}



