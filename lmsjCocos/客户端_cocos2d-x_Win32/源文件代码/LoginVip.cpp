#include "LoginVip.h"
#include"GameGround.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include"curl/include/win32/curl/curl.h"

/**
注册玩家登录
*/

USING_NS_CC;

std::map<std::string, std::string>  LoginVip::dict;
std::map<std::string, std::string> getMapFromResult2(std::string result);

Scene* LoginVip::createScene()
{
	auto layer = LoginVip::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoginVip::init()
{
	if (!Layer::init())
	{
		return false;
	}

	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(LoginVip::menuCloseCallback, this));

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
	this->addChild(menu, 1);

	label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	//输入框
	inputname = TextFieldTTF::textFieldWithPlaceHolder("Input  Name", "宋体", 40);
	inputpassw = TextFieldTTF::textFieldWithPlaceHolder("Input  Password", "宋体", 40);

	inputname->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.5));
	inputpassw->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.7));
	this->addChild(inputname);
	this->addChild(inputpassw);

	//添加监听
	auto lisenterinput1 = EventListenerTouchOneByOne::create();
	lisenterinput1->onTouchBegan = [=](Touch * touch, Event *e) {
		if (inputname->getBoundingBox().containsPoint(touch->getLocation())) {
			inputname->attachWithIME();
		}
		else {
			inputname->detachWithIME();
		}
		return false;
	};

	auto lisenterinput2 = EventListenerTouchOneByOne::create();
	lisenterinput2->onTouchBegan = [=](Touch * touch, Event *e) {
		if (inputpassw->getBoundingBox().containsPoint(touch->getLocation())) {
			inputpassw->attachWithIME();
		}
		else {
			inputpassw->detachWithIME();
		}
		return false;
	};

	//注册监听器
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lisenterinput1, inputname);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lisenterinput2, inputpassw);

	//添加开始按钮
	auto beginconnect = MenuItemImage::create(
		"onePlayer.png",
		"onePlayer2.png",
		CC_CALLBACK_1(LoginVip::menucCallback, this));

	if (beginconnect == nullptr ||
		beginconnect->getContentSize().width <= 0 ||
		beginconnect->getContentSize().height <= 0)
	{
		problemLoading("'  'onePlayer.png' and 'onePlayer2.png' ");
	}
	else
	{
		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + visibleSize.height / 4;
		beginconnect->setScale(1.2f);
		beginconnect->setPosition(Vec2(x, y));
	}

	auto menuc = Menu::create(beginconnect, NULL);
	menuc->setPosition(Vec2::ZERO);
	this->addChild(menuc, 1);



	return true;
}


void LoginVip::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void LoginVip::menucCallback(Ref* pSender)
{
	CCLOG("inputname------------>%s",inputname->getString().c_str());
	CCLOG("inputpassw------------>%s", inputpassw->getString().c_str());
	signin(inputname->getString().c_str(), inputpassw->getString().c_str());
	if (LoginVip::dict["haveuser"] == "1") {
		//Director::getInstance()->setDepthTest(true);
		auto gameScene = GameGround::createScene();
		auto ss = TransitionMoveInL::create(0.5, gameScene);
		Director::getInstance()->replaceScene(ss);
	}
	//cc.Application.getInstance().openURL("www.baidu.com");
}

void LoginVip::update(float dt) {

}


//获取网页返回的登录信息

size_t writeFun2(char*ptr, size_t size, size_t nmemb, std::string *userdata) {
	*((std::string*)(userdata)) += (char*)ptr;
	CCLOG("Data------------->%s", userdata->c_str());
	LoginVip::dict = getMapFromResult2(userdata->c_str());
	if (LoginVip::dict["haveuser"] == "1") {
		cocos2d::MessageBox("sign in success", "signin");
		UserDefault::getInstance()->setStringForKey("username", LoginVip::dict["username"]);
		UserDefault::getInstance()->setStringForKey("rank", LoginVip::dict["rank"]);
		UserDefault::getInstance()->setStringForKey("coins", LoginVip::dict["coins"]);
		UserDefault::getInstance()->setStringForKey("diamonds", LoginVip::dict["diamonds"]);
		UserDefault::getInstance()->setStringForKey("score", LoginVip::dict["score"]);
	}
	else if (LoginVip::dict["haveuser"] == "0") {
		cocos2d::MessageBox("have No User,Place sign!", "signin");
	}
	else {
		cocos2d::MessageBox("sign error!", "signin");
	}

	CCLOG("uid---------------->%s", UserDefault::getInstance()->getStringForKey("username").c_str());
	return nmemb;
}

std::vector<std::string> splitString2(const std::string & str, char p) {
	size_t offset = 0;
	std::vector < std::string > vec;
	do {
		size_t pos = str.find(p, offset);
		if (pos == std::string::npos) {
			vec.push_back(str.substr(offset, str.length() - offset));
			break;
		}
		else
		{
			vec.push_back(str.substr(offset, pos - offset));
			offset = pos + 1;
		}
	} while (true);
	return vec;
}

std::string My_gbk_two_utf82(const std::string text)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	std::wstring tes = [=]()
	{
		setlocale(LC_ALL, "chs");
		const char* _tsur = text.c_str();
		size_t _tsize = text.size() + 1;
		wchar_t* _tdest = new wchar_t[_tsize];
		wmemset(_tdest, 0, _tsize);
		mbstowcs(_tdest, _tsur, _tsize);
		std::wstring result = _tdest;
		delete[] _tdest;
		setlocale(LC_ALL, "C");
		return result;

	}();

	int asciSize = WideCharToMultiByte(CP_UTF8, 0, tes.c_str(), tes.size(), NULL, 0, NULL, NULL);
	if (asciSize == ERROR_NO_UNICODE_TRANSLATION || asciSize == 0)
	{
		return std::string();
	}

	char* resultString = new char[asciSize];
	int conveResult = WideCharToMultiByte(CP_UTF8, 0, tes.c_str(), tes.size(), resultString, asciSize, NULL, NULL);
	if (conveResult != asciSize)
	{
		return std::string();
	}

	std::string buffer = "";
	buffer.append(resultString, asciSize);

	delete[] resultString;
	return buffer;

#else 
	return text;
#endif
}

std::map<std::string, std::string> getMapFromResult2(std::string result) {
	std::string wresult = My_gbk_two_utf82(result.c_str());

	std::map<std::string, std::string> ret;
	std::vector<std::string>  vec = splitString2(result, '\n');
	for (auto iter = vec.begin();iter != vec.end();++iter) {
		std::vector<std::string> vecKV = splitString2(*iter, '=');
		if (vecKV.size() == 2) {
			//	ret[vecKV[0]] = atoi(vecKV[1].c_str());		
			ret[vecKV[0]] = vecKV[1].c_str();
		}
	}
	return ret;
}

void LoginVip::signin(std::string username, std::string password) {
	CURL * request = curl_easy_init();
	char buf[128];

	curl_easy_setopt(request, CURLOPT_URL, "http://localhost:8080/CocosSever/FinVipuser");
	snprintf(buf, sizeof(buf), "username=%s&password=%s", username.c_str(),password.c_str());

	CCLOG("buf------------------------>%s", buf);

	curl_easy_setopt(request, CURLOPT_POSTFIELDS, buf);
	curl_easy_setopt(request, CURLOPT_WRITEFUNCTION, writeFun2);
	//curl_easy_setopt(request, CURLOPT_WRITEDATA, &m_requestMap[request]);

	CURLcode res = curl_easy_perform(request);
	curl_easy_cleanup(request);
}