#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include"map"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{


public:
	
    static cocos2d::Scene* createScene();
	static int eney1RunFlag;
	static int eney2RunFlag;
	cocostudio::Armature*  player, *eney2;
	Sprite * map;
	Sprite * stop1,*cover;
	CCNode * nodef;
	CCDrawNode * font,*font2;
	int statePlayer = 0;
	int eney2state = 0;
	int eney1state = 0;
	int AbsPositionx = 50;
	int AbsPositiony = 50;
	bool isPlayAttack = false;
	bool keyIsPress_w=false;
	bool keyIsPress_s = false;
	bool keyIsPress_a = false;
	bool keyIsPress_d = false;
	bool keyIsPress_f = false;

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	virtual void update(float dt);
	virtual void updatePosition(float dt);
	virtual void onEnter();
	virtual void onExit();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
