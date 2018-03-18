#include "Welcome.h"
#include"GameGround.h"
#include"LoginVip.h"
#include"HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include"SocketTool.h"
/**
	进入游戏首界面
*/
USING_NS_CC;

int Welcome::loginflag = 0;
Scene* Welcome::createScene()
{
	auto layer = Welcome::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of	filenames in HelloWorldScene.cpp\n");
}
// on "init" you need to initialize your instance
bool Welcome::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("anbg.plist");
	
	//添加关闭游戏按钮
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Welcome::menuCloseCallback, this));
	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 5);

//添加登录游戏按钮
	auto visitsignItem = MenuItemImage::create(
		"visitsign2.png",
		"visitsign_select2.png",
		CC_CALLBACK_1(Welcome::menuStartVisi, this));
	if (visitsignItem == nullptr ||
		visitsignItem->getContentSize().width <= 0 ||
		visitsignItem->getContentSize().height <= 0)
	{
		problemLoading("'visitsign2.png' and 'visitsign_select2.png'");
	}

	auto vipsignItem = MenuItemImage::create(
		"vipsign.png",
		"vipsign_select.png",
		CC_CALLBACK_1(Welcome::menuStartVip, this));
	if (vipsignItem == nullptr ||
		vipsignItem->getContentSize().width <= 0 ||
		vipsignItem->getContentSize().height <= 0)
	{
		problemLoading("'vipsign.png' and 'vipsign_select.png'");
	}

	// create menu, it's an autorelease object
	auto menuStart = Menu::create(vipsignItem, visitsignItem, NULL);
	menuStart->setPosition(Vec2(origin.x + visibleSize.width /7, origin.y + visibleSize.height / 2.5));
	menuStart->setScale(0.8f);
	menuStart->alignItemsVertically();
	this->addChild(menuStart, 2);

	//添加Dead By DayLight标题
	label = Label::createWithTTF("Dead By DayLight", "fonts/Marker Felt.ttf", 36);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height*2));
		// add the label as a child to this layer
		this->addChild(label, 2);
	}

	//添加Version标题
	auto leftLabel = Label::createWithTTF("Version: 20171010v1.001 \nJust for Learnning and Studing ", "fonts/Marker Felt.ttf", 15);//版本：20171010v1.001\n，本游戏改编自黎明杀机游戏，纯属学习交流作用
	if (leftLabel == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		leftLabel->setPosition(Vec2(origin.x + 100,
			origin.y + visibleSize.height - leftLabel->getContentSize().height ));
		// add the label as a child to this layer
		this->addChild(leftLabel, 2);
	}

	//添加底部标题
	auto buttomLabel = Label::createWithTTF("This game is jiust for 16 year old people \n pizhunhao: 201710101272_B4380017891514 \n Zuozhe: xym xavier, DanWei :Swu  ", "fonts/Marker Felt.ttf", 12);//版本：20171010v1.001\n，本游戏改编自黎明杀机游戏，纯属学习交流作用
	if (buttomLabel == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		buttomLabel->setPosition(Vec2(origin.x + visibleSize.width/3,
			origin.y + leftLabel->getContentSize().height));
		// add the label as a child to this layer
		this->addChild(buttomLabel, 2);
	}

	//添加蓝色背景图片
	auto bgm = Sprite::create("background3.png");
	if (bgm == nullptr)
	{
		problemLoading("'background3.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		bgm->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		// add the sprite as a child to this layer
		bgm->setScaleX(1.1f);
		bgm->setScaleY(1.26f);
		this->addChild(bgm, 0);
	}

	//动态背景图2
	/*
	Sprite * runBg = Sprite::create();
	Animation * animaBgm = Animation::create();
	for (int i = 0;i < 20;i++) {
		String *frameName = String::createWithFormat("bg1%04d",i);
		SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animaBgm->addSpriteFrame(spriteFrame);
	}
	animaBgm->setDelayPerUnit(0.05f);
	animaBgm->setRestoreOriginalFrame(true);
	Animate *action = Animate::create(animaBgm);
	runBg->runAction(RepeatForever::create(action));
	this->addChild(runBg, 6);
	//runBg->stopAllActions();
	*/

	//添加例子火花
	auto* fire = ParticleSystemQuad::create("bgfire2.plist");
	this->addChild(fire, 6);
	fire->setPosition(Vec2(visibleSize.width / 1.3 + origin.x, visibleSize.height / 2 + origin.y));
	
	//添加背景动态屠夫图案
	cocostudio::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("tufubg3/tufubg0.png", "tufubg3/tufubg0.plist", "tufubg3/tufubg.ExportJson");
	auto bgtufu = cocostudio::Armature::create("tufubg");
	bgtufu->getAnimation()->playByIndex(0);
	bgtufu->setScaleX(1.3f);
	bgtufu->setScaleY(1.5f);
	bgtufu->setPosition(Vec2(visibleSize.width / 1.25 + origin.x, visibleSize.height / 2 + origin.y-20));
	this->addChild(bgtufu, 1);

	//开始连接标题
    conLabel = Sprite::create("wait.png");
	if (conLabel == nullptr)
	{
		problemLoading("'wait.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		conLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y-50));
		// add the sprite as a child to this layer
		conLabel->setScaleX(1.1f);
		conLabel->setScaleY(1.2f);
		conLabel->setVisible(false);
		this->addChild(conLabel, 5);
	}


	return true;
}
void Welcome::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void Welcome::menuStartVisi(Ref* pSender)
{
	//conLabel->setVisible(true);
	//int n = SocketTool::connectServer("127.0.0.1", 9999);
	//if (SocketTool::connectFlag) {
	  Welcome::loginflag = 0;
	   Director::getInstance()->setDepthTest(true);
		auto gameScene =GameGround::createScene();
		auto ss = TransitionMoveInL::create(0.5, gameScene);
		
		//替换场景
		Director::getInstance()->replaceScene(ss);
//	}
}

void Welcome::menuStartVip(Ref* pSender)
{
	//conLabel->setVisible(true);

	//Director::getInstance()->setDepthTest(true);
	Welcome::loginflag = 1;
	auto gameScene = LoginVip::createScene();
	auto ss = TransitionMoveInL::create(0.5, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void Welcome::update(float dt) {
}