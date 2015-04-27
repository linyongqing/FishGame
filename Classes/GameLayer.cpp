#include "GameLayer.h"
USING_NS_CC;

const int FishInBatchNode1[] = { 1, 2, 3, 4, 5, 6, 7, 9, 13, 14 };
const int FishInBatchNode2[] = {10, 18};

Scene* GameLayer::scene(){
	Scene *scene = Scene::create();
	Layer *layer = GameLayer::create();
	scene->addChild(layer);
	return scene;
}

GameLayer::GameLayer() :m_pBullets(NULL), m_pFishes(NULL), m_pCannon(NULL), m_pSpriteAdd(NULL){
	//初始化列表
}

GameLayer::~GameLayer(){
	CC_SAFE_RELEASE(m_pCannon);
	CC_SAFE_RELEASE(m_pBullets);
	CC_SAFE_RELEASE(m_pFishes);
	CC_SAFE_RELEASE(m_pRollNumGroup);
}

bool GameLayer::init(){
	if (!Layer::init()){
		return false;
	}

	this->initFrames();
	this->initBackground();
	this->initListeners();
	this->initFishes();
	this->initCannon();
	this->schedule(schedule_selector(GameLayer::updateFishes), 1.0f);
	this->schedule(schedule_selector(GameLayer::updateGame), 0.05f);
	return true;
}

void GameLayer::initListeners(){
	//添加一个触摸监听
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [=](Touch *pTouch, Event *pEvent){
		return this->onTouchBegan(pTouch, pEvent);
	};

	touchListener->onTouchMoved = [=](Touch *pTouch, Event *pEvent){
		this->onTouchMoved(pTouch, pEvent);
	};

	touchListener->onTouchEnded = [this](Touch *pTouch, Event *pEvent){
		this->onTouchEnded(pTouch, pEvent);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameLayer::initFrames(){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish3.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish4.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cannon.plist");
}

void GameLayer::initBackground(){
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("bj01.jpg");

	Sprite *pBackground = Sprite::createWithTexture(texture);
	pBackground->setAnchorPoint(Vec2(0.5f, 0.5f));

	Size winSize = Director::getInstance()->getWinSize();
	pBackground->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(pBackground);

	texture = Director::getInstance()->getTextureCache()->addImage("ui_box_01.png");
	Sprite *pTopBar = Sprite::createWithTexture(texture);
	pTopBar->setPosition(500, 580);
	this->addChild(pTopBar, 100);

	texture = Director::getInstance()->getTextureCache()->addImage("ui_box_02.png");
	Sprite *pBottomBar = Sprite::createWithTexture(texture);
	pBottomBar->setPosition(440, 90);
	this->addChild(pBottomBar, 100);

	this->setRollNumGroup(RollNumGroup::createWithGameLayer(this, 6));
	m_pRollNumGroup->setPosition(Vec2(351, 21));
}

void GameLayer::initFishes(){
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("fish.png");
	this->setBatchNodeFishes1(SpriteBatchNode::createWithTexture(texture));
	this->addChild(this->m_pBatchNodeFishes1);

	texture = Director::getInstance()->getTextureCache()->addImage("fish2.png");
	this->setBatchNodeFishes2AndBullets(SpriteBatchNode::createWithTexture(texture));
	this->addChild(this->m_pBatchNodeFishes2AndBullets);

	texture = Director::getInstance()->getTextureCache()->addImage("fish3.png");
	this->setBatchNodeFishes3AndNets(SpriteBatchNode::createWithTexture(texture));
	this->addChild(this->m_pBatchNodeFishes3AndNets);

	texture = Director::getInstance()->getTextureCache()->addImage("fish4.png");
	this->setBatchNodeFishes4(SpriteBatchNode::createWithTexture(texture));
	this->addChild(this->m_pBatchNodeFishes4);

	this->setFishes(Array::createWithCapacity(MAX_FISH_COUT));
	m_pFishes->removeAllObjects();
}

void GameLayer::initCannon(){
	this->setBullets(Array::create());
	Texture2D *pTexture = Director::getInstance()->getTextureCache()->addImage("cannon.png");
	SpriteBatchNode *pBatchNode = SpriteBatchNode::createWithTexture(pTexture);
	this->addChild(pBatchNode, 101, 7);

	this->setCannon(Cannon::createWithCannonType(6, this, pBatchNode));

	Texture2D *textureAdd = Director::getInstance()->getTextureCache()->addImage("button_add.png");
	SpriteFrame *spriteFrameAddNormal = SpriteFrame::createWithTexture(
		textureAdd,
		Rect(0, 0, textureAdd->getContentSize().width / 2, textureAdd->getContentSize().height));

	this->m_pSpriteAdd = Sprite::createWithSpriteFrame(spriteFrameAddNormal);
	this->m_pSpriteAdd->setPosition(Vec2(585, 28));
	this->m_pSpriteAdd->setScale(1.5f);
	this->addChild(this->m_pSpriteAdd, 101);

	Texture2D *textureReduce = Director::getInstance()->getTextureCache()->addImage("button_reduce.png");
	SpriteFrame *spriteFrameReduceNormal = SpriteFrame::createWithTexture(textureReduce, 
		Rect(0, 0, textureReduce->getContentSize().width / 2, textureReduce->getContentSize().height));
	this->m_pSpriteReduce = Sprite::createWithSpriteFrame(spriteFrameReduceNormal);
	this->m_pSpriteReduce->setPosition(Vec2(450, 28));
	this->m_pSpriteReduce->setScale(1.5f);
	this->addChild(this->m_pSpriteReduce, 101);
}

void GameLayer::addCannon(){
	int currCannonType = this->m_pCannon->getCannnType();
	if (++currCannonType > 7){
		currCannonType = 1;
	}
	CC_SAFE_DELETE(this->m_pCannon);
	this->setCannon(Cannon::createWithCannonType(currCannonType, this, (SpriteBatchNode*)this->getChildByTag(7)));
}

void GameLayer::reduceCannon(){
	int currCannonType = this->m_pCannon->getCannnType();
	if (--currCannonType < 1){
		currCannonType = 7;
	}
	CC_SAFE_DELETE(this->m_pCannon);
	this->setCannon(Cannon::createWithCannonType(currCannonType, this, (SpriteBatchNode*)this->getChildByTag(7)));
}

bool GameLayer::onTouchBegan(Touch *pTouch, Event *pEvent){
	//将当前的触摸点坐标转换为OPENGL坐标
	Vec2 pt = Director::getInstance()->convertToGL(pTouch->getLocationInView());
	if (this->m_pSpriteAdd->getBoundingBox().containsPoint(pt)){
		this->addCannon();
		return false;
	}

	if (this->m_pSpriteReduce->getBoundingBox().containsPoint(pt)){
		this->reduceCannon();
		return false;
	}
	this->m_pCannon->rotateToPoint(pt);
	return true;
}

void GameLayer::onTouchMoved(Touch *pTouch, Event *pEvent){
	Vec2 pt = Director::getInstance()->convertToGL(pTouch->getLocationInView());
	this->m_pCannon->rotateToPoint(pt);
}

void GameLayer::onTouchEnded(Touch *pTouch, Event *pEvent){
	this->m_pCannon->fire();
}

void GameLayer::addFishes(){
	SpriteBatchNode *loadFishSpriteBatchNode = NULL;
	while (1)
	{
		int type = rand() % 18 + 1;
		if (NULL == loadFishSpriteBatchNode)
		{
			for (int i = 0; i < GET_AEEAY_LEN(FishInBatchNode1); ++i)
			{
				if (type == FishInBatchNode1[i])
				{
					loadFishSpriteBatchNode = m_pBatchNodeFishes1;
					break;
				}
			}
		}

		if (NULL == loadFishSpriteBatchNode)
		{
			for (int i = 0; i < GET_AEEAY_LEN(FishInBatchNode2); ++i)
			{
				if (type == FishInBatchNode2[i])
				{
					loadFishSpriteBatchNode = m_pBatchNodeFishes2AndBullets;
					break;
				}
			}
		}

		if (loadFishSpriteBatchNode)
		{
			Fish::createWithFishType(type, this, loadFishSpriteBatchNode);
			break;
		}
		loadFishSpriteBatchNode = NULL;
	}
	
}

void GameLayer::updateFishes(float dt){
	if (m_pFishes->count() < MAX_FISH_COUT)
	{
		int n = MAX_FISH_COUT - m_pFishes->count();
		int nAdd = rand() % n + 1;
		for (int i = 0; i < nAdd; i++)
		{
			this->addFishes();
		}
	}
}

Rect sharinkReck(Rect rc, float xr, float yr)
{
	float w = rc.size.width * xr;
	float h = rc.size.height * yr;
	Vec2 pt = Vec2(rc.origin.x + rc.size.width * (1.0f - xr) / 2, rc.origin.y + rc.size.height *(1.0f - yr) / 2);
	return Rect(pt.x, pt.y, w, h);
}

void GameLayer::updateGame(float dt){
	Ref *pFishObj = NULL; //鱼的对象
	Ref *pBulletObj = NULL; //子弹的对象
	CCARRAY_FOREACH(m_pBullets, pBulletObj)
	{
		Bullet *pBullet = (Bullet*)pBulletObj;
		if (pBullet->getCaught())
		{
			continue;
		}
		bool caught = false;
		CCARRAY_FOREACH(m_pFishes, pFishObj)
		{
			Fish *pFish = (Fish*)pFishObj;
			if (pFish->getCaught())
				continue;
			Rect hittesRect = sharinkReck(pFish->getSpriteFish()->getBoundingBox(), 0.8f, 0.5f);
			if (hittesRect.containsPoint(pBullet->getSpriteBullet()->getPosition()))
			{
				caught = true;
				pFish->showCaught();
				m_nScore += 125;
				m_pRollNumGroup->setValue(m_nScore);
			}
		}
		if (caught)
		{
			pBullet->showNet();
		}
	}
}
