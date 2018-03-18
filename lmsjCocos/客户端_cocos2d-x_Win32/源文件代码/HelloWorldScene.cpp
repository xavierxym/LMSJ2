#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include"SocketTool.h"
#include"GameGround.h"

/**
游戏运行场景层
*/

USING_NS_CC;

int HelloWorld::eney1RunFlag = 0;   //玩家运行标识
int HelloWorld::eney2RunFlag = 0;

Scene* HelloWorld::createScene()   //创建层
{
	auto layer = HelloWorld::create();
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0,0));
	scene->addChild(layer);
	return scene;
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


void HelloWorld::onExit() {  //游戏退出时运行
	Layer::onExit();
	log("on Exit");
	SocketTool::closeSocket();
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

void HelloWorld::onEnter() {    //进入游戏运行
	Layer::onEnter();
	//log("-------------------------------->onEnter");

	auto  listenerPc = EventListenerPhysicsContact::create();
	if (listenerPc == nullptr) {
	//	log("listenerPc ==null");
	}
	//监听碰撞四种情形
	listenerPc->onContactBegin = [=] (PhysicsContact & contact){
		auto spriteA = (cocostudio::Armature*)contact.getShapeA()->getBody()->getNode();
		auto spriteB= (Sprite *)contact.getShapeB()->getBody()->getNode();

		if (spriteA &&spriteA->getTag() == 81 && spriteB&&spriteB->getTag() == 71) {
			log("------------------------>onContactBegin");
			spriteA->setColor(Color3B::YELLOW);
			spriteB->setColor(Color3B::YELLOW);
		}
		
		return false;
	};
	listenerPc->onContactPreSolve = [](PhysicsContact& contact , PhysicsContactPreSolve& solve) {
		log("------------------->onContactPreSolve");
		return true;
	};
	listenerPc->onContactPostSolve = [](PhysicsContact& contact, const PhysicsContactPostSolve& solve) {
		log("-------------------------------->onContactPreSolve");
	};
	listenerPc->onContactSeparate = [=](PhysicsContact & contact) {

		auto spriteA = (cocostudio::Armature*)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite *)contact.getShapeB()->getBody()->getNode();
		if (spriteA &&spriteA->getTag() == 81 && spriteB&&spriteB->getTag() == 71) {
			spriteA->setColor(Color3B::WHITE);
			spriteB->setColor(Color3B::WHITE);
			log("-------------------------------->onContactSeparate");
		}
	

	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listenerPc,1);
}

// on "init" you need to initialize your instance

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//游戏结束按钮
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


	//标题
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

	/*---------------------------------*/


	//添加地图
	map = Sprite::create("testbg.png");
	map->setAnchorPoint(Vec2(0.5,0.5));
	map->setPosition(0,0);
	this->addChild(map,0);
	//添加障碍物1
	stop1 = Sprite::create("HelloWorld.png");
	stop1->setPosition(Vec2(map->getPosition().x+200, map->getPosition().y - 100));
	this->addChild(stop1,5,71);
	//stop1->setTag(71);
	
	//添加遮蔽物cover
	cover = Sprite::create("HelloWorld.png");
	cover->setPosition(Vec2(map->getPosition().x +100, map->getPosition().y - 100));
	this->addChild(cover, 20);

	auto bodystop1 = PhysicsBody::createBox(stop1->getContentSize());
	//bodystop1->setContactTestBitmask(0x01);
	bodystop1->setCollisionBitmask(0x01);
	bodystop1->setDynamic(false);

	bodystop1->getShape(0)->setRestitution(1);
	//bodystop1->setCategoryBitmask(0x01);
	stop1->setPhysicsBody(bodystop1);
	

	//加载cocostudio 屠夫文件
	cocostudio::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("lmsjTufu/lmsjTufu0.png", "lmsjTufu/lmsjTufu0.plist", "lmsjTufu/lmsjTufu.ExportJson");
	player = cocostudio::Armature::create("lmsjTufu");
	//player->getAnimation()->playByIndex(0);

	player->setScale(0.3f);
	player->setPosition(50,50);
	AbsPositionx = 50;
	AbsPositiony = 50;
	this->addChild(player,5,81);

	
	eney2 = cocostudio::Armature::create("lmsjTufu");
	//player->getAnimation()->playByIndex(0);
	eney2->setScale(0.3f);
	eney2->setPosition(50, 50);
	this->addChild(eney2, 5, 81);

	//auto shapeplayer = PhysicsShapeBox::create(player->getContentSize());
	//shapeplayer->setTag(21);
	
	//添加屠夫碰撞
	auto bodyplayer = PhysicsBody::createCircle(150,PHYSICSBODY_MATERIAL_DEFAULT,Vec2(player->getPosition().x-150, player->getPosition().y -150));
	//bodyplayer->setContactTestBitmask(0x01);
	bodyplayer->setCollisionBitmask(0x01);
	bodyplayer->setRotationEnable(false);
    //bodyplayer->getShape(0)->setMass(0);
	//bodyplayer->getShape(0)->setRestitution(1);
	//bodyplayer->setCategoryBitmask(0x01);
	player->setPhysicsBody(bodyplayer);

	auto bodyplayer2 = PhysicsBody::createCircle(150, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(eney2->getPosition().x - 150, eney2->getPosition().y - 150));
	bodyplayer2->setCollisionBitmask(0x01);
	bodyplayer2->setRotationEnable(false);
	eney2->setPhysicsBody(bodyplayer2);
	

	//键盘按键
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed=[=](EventKeyboard::KeyCode code, Event *e) {
	//	log("key code: %d", code);
		switch (code) {
		case EventKeyboard::KeyCode::KEY_W:
//			log("you put a w");
			keyIsPress_w = true;
			break;

		case EventKeyboard::KeyCode::KEY_S:
//			log("you put a s");
			keyIsPress_s = true;
			break;

		case EventKeyboard::KeyCode::KEY_A:
//			log("you put a a");
			keyIsPress_a = true;
			break;
		case EventKeyboard::KeyCode::KEY_D:
//			log("you put a d");
			keyIsPress_d = true;
			break;
		case EventKeyboard::KeyCode::KEY_F:
//			log("you put a f");
			keyIsPress_f = true;
			statePlayer = 10;
			break;
		default:break;
		}
	};

	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event *e) {
	//		log("key code: %d", code);
					switch (code) {
					case EventKeyboard::KeyCode::KEY_W:
	//					log("you release a w");
						keyIsPress_w = false;
						break;

					case EventKeyboard::KeyCode::KEY_S:
	//					log("you relase a s");
						keyIsPress_s = false;
						break;

					case EventKeyboard::KeyCode::KEY_A:
	//					log("you relase a a");
						keyIsPress_a = false;
						break;

					case EventKeyboard::KeyCode::KEY_D:
	//					log("you release a d");
						keyIsPress_d = false;
						break;

					case EventKeyboard::KeyCode::KEY_F:
	//					log("you put a f");
						keyIsPress_f = false;
						break;
		default:break;
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	/*---------------------------------*/
	//可视范围遮蔽圈
	auto clip = CCClippingNode::create();
	clip->setInverted(true);
	clip->setAlphaThreshold(0.1f);
	this->addChild(clip,10);

	CCLayerColor * back = CCLayerColor::create(ccc4(0,0,0,255));
	CCLayerColor * back2 = CCLayerColor::create(ccc4(0, 0, 0, 200));
	clip->addChild(back);
	clip->addChild(back2);
 
	font = CCDrawNode::create();
	ccColor4F yellow = {1,1,0,1};

	font->drawSolidCircle(player->getPosition(),250.0,CC_DEGREES_TO_RADIANS(90),200,yellow);
	font->setPosition(Vec2(player->getPosition().x-100, player->getPosition().y - 100));

	
	clip->setStencil(font);

	//连接服务器
	int n=SocketTool::connectServer("127.0.0.1",9999);
	if (SocketTool::connectFlag) {

			if (GameGround::who == 0) { //判断角色
				SocketTool::sendInt(666);
			}
			else {
				SocketTool::sendInt(667);
			}

			//发送自己的位置
		SocketTool::sendInt(10000);
		SocketTool::sendInt(player->getPosition().x - map->getPosition().x);
		SocketTool::sendInt(player->getPosition().y - map->getPosition().y);
	}
	scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::updatePosition),0.04f); //0.004秒更新
    return true;
}


//更新位置函数
void HelloWorld::updatePosition(float dt) {
	SocketTool::sendInt(10000);
	SocketTool::sendInt(player->getPosition().x - map->getPosition().x);
	SocketTool::sendInt(player->getPosition().y - map->getPosition().y);
	auto  actionTo = CCMoveTo::create(0.04, Vec2(SocketTool::arr[0]+map->getPosition().x, SocketTool::arr[1] + map->getPosition().y));
	eney2->runAction(actionTo);
}


//更新位置、按键
void HelloWorld::update(float dt) {
	
	if (statePlayer == 10)
	{
		if (!isPlayAttack) {
			player->getAnimation()->playByIndex(1);
			isPlayAttack = true;
		}
		statePlayer = 0;
	}
	
	if (keyIsPress_a&&!isPlayAttack) {
		if(statePlayer != 1)
		{ 
			player->getAnimation()->playByIndex(0);
			statePlayer = 1;
		}
		
		if (player->getPosition().x>50) {
			player->setPosition(player->getPosition().x-5,player->getPosition().y);
		}
		else {
			if(map->getPosition().x<880)
			map->setPosition(map->getPosition().x + 5, map->getPosition().y);
			stop1->setPosition(Vec2(map->getPosition().x + 200, map->getPosition().y - 100));
			cover->setPosition(Vec2(map->getPosition().x + 100, map->getPosition().y - 100));
		}
	}
	
	if (keyIsPress_w && !isPlayAttack) {
		if (statePlayer != 1)
		{
			player->getAnimation()->playByIndex(0);
			statePlayer = 1;
		}
		if (player->getPosition().y<500) {
			player->setPosition(player->getPosition().x, player->getPosition().y + 5);
			
		}
		else {
			if (map->getPosition().y>-280)
				map->setPosition(map->getPosition().x , map->getPosition().y-5);
				stop1->setPosition(Vec2(map->getPosition().x + 200, map->getPosition().y - 100));
				cover->setPosition(Vec2(map->getPosition().x + 100, map->getPosition().y - 100));
		}
	}
	
	if (keyIsPress_d && !isPlayAttack) {
		if (statePlayer != 1)
		{
			player->getAnimation()->playByIndex(0);
			statePlayer = 1;
		}
		if (player->getPosition().x < 800) {
			player->setPosition(player->getPosition().x + 5, player->getPosition().y);
		}
		else {
			if (map->getPosition().x>20)
				map->setPosition(map->getPosition().x - 5, map->getPosition().y);
				stop1->setPosition(Vec2(map->getPosition().x + 200, map->getPosition().y - 100));
				cover->setPosition(Vec2(map->getPosition().x + 100, map->getPosition().y - 100));
		}
	}
	
	if (keyIsPress_s && !isPlayAttack) {
		if (statePlayer != 1)
		{
			player->getAnimation()->playByIndex(0);
			statePlayer = 1;
		}
		if (player->getPosition().y > 50) {
			player->setPosition(player->getPosition().x, player->getPosition().y - 5);
		}
		else {
			if (map->getPosition().y<880)
				map->setPosition(map->getPosition().x, map->getPosition().y +5);
				stop1->setPosition(Vec2(map->getPosition().x + 200, map->getPosition().y - 100));
				cover->setPosition(Vec2(map->getPosition().x + 100, map->getPosition().y - 100));
		}
	}
	
	if(!keyIsPress_s && !keyIsPress_a &&!keyIsPress_w&&!keyIsPress_d&&!keyIsPress_f && !isPlayAttack) {
		if (statePlayer!=0)
		{
			player->getAnimation()->playByIndex(0);
			statePlayer = 0;
		}
	}

		if (!player->getAnimation()->isPlaying()) {
			isPlayAttack=false;
		}


		if (eney2RunFlag == 0) {
			if(eney2state!=0|| !eney2->getAnimation()->isPlaying())
			{
				eney2->getAnimation()->playByIndex(0);
				eney2state = 0;
			}
		}
		else if (eney2RunFlag == 1) {
			if (eney2state != 1 )
			{
				eney2->getAnimation()->playByIndex(0);
				eney2state = 1;
			}
		}
		else if (eney2RunFlag == 2) {
			if (eney2state != 2)
			{
				eney2->getAnimation()->playByIndex(0);
				eney2state = 2;
			}
		}

		//nodef->setPosition(player->getPosition().x+player->getContentSize().width/2, player->getPosition().y + player->getContentSize().height / 2);
		font->setPosition(player->getPosition().x , player->getPosition().y );
}

//退出回调函数
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
	SocketTool::closeSocket();
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}
