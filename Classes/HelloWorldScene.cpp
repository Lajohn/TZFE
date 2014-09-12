#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bgLayer=LayerColor::create(Color4B(180,170,160,255));
	this->addChild(bgLayer,-1);

	//添加分数
	score=0;
	scoreTitleLabel=Label::createWithSystemFont("Score:","Buxton Sketch",visibleSize.width*0.1);
	scoreTitleLabel->setPosition(Vec2(visibleSize.width/4,visibleSize.height-50));
	this->addChild(scoreTitleLabel);

	scoreLabel=Label::createWithSystemFont(__String::createWithFormat("%i",score)->getCString(),"Buxton Sketch",visibleSize.width*0.1);
	scoreLabel->setPosition(Vec2(visibleSize.width*0.5,visibleSize.height-50));
	this->addChild(scoreLabel);

	//添加重置及退出菜单
	restartLabel=Label::createWithSystemFont("Restart","Buxton Sketch",visibleSize.width*0.1);
	exitLabel=Label::createWithSystemFont("Exit","Buxton Sketch",visibleSize.width*0.1);

	auto restart=MenuItemLabel::create(restartLabel,CC_CALLBACK_1(HelloWorld::menuRestartCallback,this));
	restart->setPosition(Vec2(visibleSize.width*0.35,50));
	auto exit=MenuItemLabel::create(exitLabel,CC_CALLBACK_1(HelloWorld::menuExitCallback,this));
	exit->setPosition(Vec2(visibleSize.width*0.65,50));

	auto menu=Menu::create(restart,exit,NULL);
	
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	


	//创建并注册触摸事件监听
	auto listener=EventListenerTouchOneByOne::create();
	listener->onTouchBegan=CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
	listener->onTouchEnded=CC_CALLBACK_2(HelloWorld::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//创建卡片
	createCards(visibleSize);

	//自动创建卡片
	autoCreateCard();
	autoCreateCard();

	

	

	return true;
}



//触摸事件
bool HelloWorld::onTouchBegan(cocos2d::Touch *t,cocos2d::Event *e){
	firstX=t->getLocation().x;
	firstY=t->getLocation().y;
	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *t,cocos2d::Event *e){
	lastX=firstX-t->getLocation().x;
	lastY=firstY-t->getLocation().y;
	bool isDo=false;

	//如果x轴绝对值大于y轴绝对值 则是左右滑动 否则是上下滑动
	if(abs(lastX)>abs(lastY)){
		if(lastX+20>0){
			//左边
			isDo=doLeft();
		}else{
			//右边
			isDo=doRight();
		}
	}else if((abs(lastX)<abs(lastY))){
		if(lastY+20>0){
			//下边
			isDo=doDown();
		}else{
			//上边
			isDo=doUp();
		}
	}
	if(isDo){
		autoCreateCard();
	}
	doCheckGameOver();

}

//手势移动
bool HelloWorld::doLeft(){
	bool isDo=false;

	for (int j = 0; j < 4; j++){
		for(int i=0;i<4;i++){
			for(int ii=i+1;ii<4;ii++){
				if(cards[ii][j]->getNum()>0){
					if(cards[i][j]->getNum()<=0){
						cards[i][j]->setNum(cards[ii][j]->getNum());
						cards[ii][j]->setNum(0);

						i--;
						isDo=true;
					}else if(cards[i][j]->getNum()==cards[ii][j]->getNum()){
						cards[i][j]->setNum(cards[ii][j]->getNum()*2);
						cards[ii][j]->setNum(0);

						//更新分数
						addScore(cards[i][j]->getNum());

						isDo=true;
					}
					break;
				}
			}
		}
	}

	return isDo;
}

bool HelloWorld::doRight(){
	bool isDo=false;

	for (int j = 0; j < 4; j++){
		for(int i=3;i>=0;i--){
			for(int ii=i-1;ii>=0;ii--){
				if(cards[ii][j]->getNum()>0){
					if(cards[i][j]->getNum()<=0){
						cards[i][j]->setNum(cards[ii][j]->getNum());
						cards[ii][j]->setNum(0);

						i++;
						isDo=true;
					}else if(cards[i][j]->getNum()==cards[ii][j]->getNum()){
						cards[i][j]->setNum(cards[ii][j]->getNum()*2);
						cards[ii][j]->setNum(0);

						//更新分数
						addScore(cards[i][j]->getNum());

						isDo=true;
					}
					break;
				}
			}
		}
	}

	return isDo;
}

bool HelloWorld::doUp(){
	bool isDo=false;

	for (int i = 0; i < 4; i++){
		for (int j = 3; j >= 0; j--){
			for (int jj = j-1; jj >= 0; jj--){
				if(cards[i][jj]->getNum()>0){
					if (cards[i][j]->getNum()<=0){
						cards[i][j]->setNum(cards[i][jj]->getNum());
						cards[i][jj]->setNum(0);

						j++;
						isDo=true;
					}else if (cards[i][j]->getNum()==cards[i][jj]->getNum()){
						cards[i][j]->setNum(cards[i][jj]->getNum()*2);
						cards[i][jj]->setNum(0);

						//更新分数
						addScore(cards[i][j]->getNum());

						isDo=true;
					}
					break;
				}
			}
		}
	}

	return isDo;
}

bool HelloWorld::doDown(){
	bool isDo=false;

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			for (int jj = j+1; jj < 4; jj++){
				if(cards[i][jj]->getNum()>0){
					if (cards[i][j]->getNum()<=0){
						cards[i][j]->setNum(cards[i][jj]->getNum());
						cards[i][jj]->setNum(0);

						j--;
						isDo=true;
					}else if (cards[i][j]->getNum()==cards[i][jj]->getNum()){
						cards[i][j]->setNum(cards[i][jj]->getNum()*2);
						cards[i][jj]->setNum(0);

						//更新分数
						addScore(cards[i][j]->getNum());

						isDo=true;
					}
					break;
				}
			}
		}
	}

	return isDo;
}


void HelloWorld::createCards(cocos2d::Size size){
	//求出每张卡片的大小
	int minWidth,maxWidth;
	if(size.width<size.height){
		minWidth=size.width;
		maxWidth=size.height;
	}else{
		minWidth=size.height;
		maxWidth=size.width;
	}


	int cardWidth=(minWidth-32)/4;
	Size cardSize=Size(cardWidth,cardWidth);

	int addX=16,addY=(maxWidth-cardWidth*4)/2;


	for(int i=0;i<4;i++){
		for (int j = 0; j < 4; j++)
		{
			Vec2 position=Vec2(addX+(cardWidth/2)+(i*cardWidth),addY+(cardWidth/2)+(j*cardWidth));

			auto card=CardSprite::createCardSprite(0,cardSize,position);
			card->setAnchorPoint(Vec2(0.5,0.5));
			this->addChild(card);

			cards[i][j]=card;
		}
	}

}



void HelloWorld::autoCreateCard(){
	int i=getRand(0,3);
	int j=getRand(0,3);


	if(cards[i][j]->getNum()>0){
		autoCreateCard();
	}else{
		cards[i][j]->setNum(getRand(0,100)>15?2:4);
		cards[i][j]->cardAction();
	}

}


void HelloWorld::doCheckGameOver(){
	bool isGameOver=true;

	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if((cards[i][j]->getNum()==0)||
				(i>0&&cards[i][j]->getNum()==cards[i-1][j]->getNum())||
				(i<3&&cards[i][j]->getNum()==cards[i+1][j]->getNum())||
				(j>0&&cards[i][j]->getNum()==cards[i][j-1]->getNum())||
				(j<3&&cards[i][j]->getNum()==cards[i][j+1]->getNum())){
				isGameOver=false;
			}
			if(!isGameOver)
				break;
		}
		if(!isGameOver)
			break;
	}
	if(isGameOver){
		
		auto gameOver=Label::createWithSystemFont(
			"Game Over",
			"Buxton Sketch",
			Director::getInstance()->getVisibleSize().width*0.25);
		gameOver->setColor(Color3B(39,17,14));
		gameOver->setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2,Director::getInstance()->getVisibleSize().height/2));
		this->addChild(gameOver);

		auto fadeIn=FadeIn::create(2);

		gameOver->runAction(fadeIn);
	}
}



void HelloWorld::addScore(int s){
	//更新分数
	score+=s;
	scoreLabel->setString(__String::createWithFormat("%i",score)->getCString());

	if(s>0){
		auto addScore=Label::createWithSystemFont(
			__String::createWithFormat("+%i",s)->getCString(),
			"Buxton Sketch",
			Director::getInstance()->getVisibleSize().width*0.09);
		addScore->setColor(Color3B(39,17,14));
		addScore->setPosition(scoreLabel->getPosition()+Vec2(scoreLabel->getContentSize().width/2,scoreLabel->getContentSize().height/2));
		this->addChild(addScore,20);

		auto spawn=Spawn::create(MoveBy::create(1,Vec2(0,15)),FadeOut::create(2),NULL);
		auto cf=CallFunc::create([addScore](){
			addScore->removeFromParent();
		});
		auto seq=Sequence::create(spawn,cf,NULL);
		addScore->runAction(seq);
	}
}

void HelloWorld::menuRestartCallback(cocos2d::Ref* pSender){
	Director::getInstance()->replaceScene(TransitionFade::create(2,HelloWorld::createScene()));
}

void HelloWorld::menuExitCallback(cocos2d::Ref* pSender){
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
		return;
	#endif

		Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}


//创建随机数
int HelloWorld::getRand(int start,int end){
	struct timeval psv;    
	gettimeofday(&psv,NULL);
	unsigned long int rand_seed = psv.tv_sec*1000 + psv.tv_usec/1000;    
	srand(rand_seed);   

	for(int i=0;i<100;i++){
		CCRANDOM_0_1()*(end-start+1)+start;
	}

  
	return (int)(CCRANDOM_0_1()*(end-start+1)+start);
}

