#include "GameGround.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"Welcome.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
//#include"cocos2d\external\win32-specific\icon\include\iconv.h"
#include"curl/include/win32/curl/curl.h"

/**
游戏玩家信息界面
*/

USING_NS_CC;
std::map<std::string, std::string>  GameGround::dict;
std::map<std::string, std::string> getMapFromResult(std::string result);
int GameGround::who = 0;
Scene* GameGround::createScene()
{
	auto layer = GameGround::create();
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
bool  GameGround::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//关闭按钮
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameGround::menuCloseCallback, this));

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

	

/*----------------------------*/
	// 添加背景
	auto bg = Sprite::create("background3.png");
	if (bg == nullptr){
		problemLoading("'background3.png'");
	}
	else{
		bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		bg->setScaleX(1.1f);
		bg->setScaleY(1.26f);
		this->addChild(bg, 0);
	}
	/*----------------------------*/
	// 添加背景top
	auto bgtop = Sprite::create("top1.png");
	if (bgtop == nullptr) {
		problemLoading("'top1.png'");
	}
	else {
		bgtop->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height  + origin.y-bgtop->getContentSize().height*0.2));
		bgtop->setScaleX(0.8f);
		bgtop->setScaleY(0.5f);
		this->addChild(bgtop, 1);
	}

	// 添加背景头像
	auto kuang1 = Sprite::create("kuang1.png");
	if (kuang1 == nullptr) {
		problemLoading("'kuang1.png'");
	}
	else {
		kuang1->setPosition(Vec2( origin.x +kuang1->getContentSize().width/10, visibleSize.height + origin.y - kuang1->getContentSize().height*0.1));
		kuang1->setScaleX(0.13f);
		kuang1->setScaleY(0.13f);
		this->addChild(kuang1, 2);
	}

	// 添加经验条
	Node *pNode = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("bar1/bar1_1.json");
	this->addChild(pNode,2);
	auto bar1 = (cocos2d::ui::LoadingBar*)(ui::Helper::seekWidgetByName((ui::Widget*)pNode, "ProgressBar_1"));
	
	bar1->setPosition(Vec2(origin.x + kuang1->getPositionX() + 175,
		origin.y + kuang1->getPositionY() - 15));
	bar1->setScaleX(0.5f);
	bar1->setScaleY(0.07f);
	bar1->setPercent(99);
	// 添加经验条lV
	auto barLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 14);
	if (barLabel == nullptr) {
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else {
		barLabel->setPosition(Vec2(origin.x + kuang1->getPositionX() + 45,
			origin.y + kuang1->getPositionY() - 15));
		this->addChild(barLabel, 2);
	}
	// 添加金币图案
	auto coin = Sprite::create("ring_blue.png");
	if (coin == nullptr) {
		problemLoading("'ring_blue.png'");
	}
	else {
		coin->setPosition(Vec2(origin.x + visibleSize.width/2.2, visibleSize.height + origin.y - coin->getContentSize().height*0.7));
		coin->setScaleX(1.0f);
		coin->setScaleY(1.0f);
		this->addChild(coin, 2);
	}
	// 添加砖石图案
	auto diam = Sprite::create("circle.png");
	if (diam == nullptr) {
		problemLoading("'circle.png'");
	}
	else {
		diam->setPosition(Vec2(origin.x + visibleSize.width/1.6, visibleSize.height + origin.y - coin->getContentSize().height*0.7));
		diam->setScaleX(1.2f);
		diam->setScaleY(1.2f);
		this->addChild(diam, 2);
	}

	// 添加设置图案
	auto setting = Sprite::create("game_setting.png");
	if (setting == nullptr) {
		problemLoading("'game_setting.png'");
	}
	else {
		setting->setPosition(Vec2(origin.x + visibleSize.width / 1.25, visibleSize.height + origin.y - coin->getContentSize().height*0.7));
		setting->setScaleX(1.0f);
		setting->setScaleY(1.0f);
		this->addChild(setting, 2);
	}

	// 添加退出图案
	auto exit = Sprite::create("game_exit.png");
	if (exit == nullptr) {
		problemLoading("'game_exit.png'");
	}
	else {
		exit->setPosition(Vec2(origin.x + visibleSize.width / 1.1, visibleSize.height + origin.y - coin->getContentSize().height*0.7));
		exit->setScaleX(1.0f);
		exit->setScaleY(1.0f);
		this->addChild(exit, 2);
	}
	// 添加屠夫选择框
	auto kuangtufu = Sprite::create("kuangtufu.png");
	if (kuangtufu == nullptr) {
		problemLoading("'kuangtufu.png'");
	}
	else {
		kuangtufu->setPosition(Vec2(origin.x + visibleSize.width / 3, visibleSize.height /2));
		kuangtufu->setScaleX(1.0f);
		kuangtufu->setScaleY(1.0f);
		this->addChild(kuangtufu, 1);
	}

	// 添加屠夫动态图
	cocostudio::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("tufuAnimation/tufuAnimation0.png", "tufuAnimation/tufuAnimation0.plist", "tufuAnimation/tufuAnimation.ExportJson");
	auto kuangtufuTu = cocostudio::Armature::create("tufuAnimation");
	kuangtufuTu->getAnimation()->playByIndex(0);
	kuangtufuTu->setScaleX(1.2f);
	kuangtufuTu->setScaleY(1.2f);
	kuangtufuTu->setPosition(Vec2(kuangtufu->getPositionX() + origin.x, kuangtufu->getPositionY() + origin.y ));
	this->addChild(kuangtufuTu, 2);

	//添加屠夫选择按钮
	auto tufuItem = MenuItemImage::create(
		"tufubutton.png",
		"tufubutton_select.png",
		CC_CALLBACK_1(GameGround::menuTufuCallback, this));

	if (tufuItem == nullptr ||
		tufuItem->getContentSize().width <= 0 ||
		tufuItem->getContentSize().height <= 0){
		problemLoading("'tufubutton.png' and 'tufubutton_select.png'");
	}
	else{
		tufuItem->setPosition(Vec2(kuangtufu->getPositionX() + origin.x, kuangtufu->getPositionY()-kuangtufu->getContentSize().height/2+50+ origin.y));
		tufuItem->setScaleX(0.95f);
		tufuItem->setScaleY(1.2f);
	}
	auto menutufuItem = Menu::create(tufuItem, NULL);
	menutufuItem->setPosition(Vec2::ZERO);
	this->addChild(menutufuItem, 3);


	// 添加人类选择框
	auto kuangpeople = Sprite::create("kuangtufu.png");
	if (kuangpeople == nullptr) {
		problemLoading("'kuangtufu.png'");
	}
	else {
		kuangpeople->setPosition(Vec2(origin.x + visibleSize.width / 1.5, visibleSize.height / 2));
		kuangpeople->setScaleX(1.0f);
		kuangpeople->setScaleY(1.0f);
		this->addChild(kuangpeople, 1);
	}

	// 添加人类动态图
	cocostudio::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("peopleAnimation/peopleAnimation0.png", "peopleAnimation/peopleAnimation0.plist", "peopleAnimation/peopleAnimation.ExportJson");
	auto kuangpeopleTu = cocostudio::Armature::create("peopleAnimation");
	kuangpeopleTu->getAnimation()->playByIndex(0);
	kuangpeopleTu->setScaleX(0.8f);
	kuangpeopleTu->setScaleY(0.67f);
	kuangpeopleTu->setPosition(Vec2(kuangpeople->getPositionX() + origin.x+10, kuangpeople->getPositionY() + origin.y-30));
	this->addChild(kuangpeopleTu, 2);

	//添加人类选择按钮
	auto peopleItem = MenuItemImage::create(
		"peoplebutton.png",
		"peoplebutton_select.png",
		CC_CALLBACK_1(GameGround::menuPeopleCallback, this));

	if (peopleItem == nullptr ||
		peopleItem->getContentSize().width <= 0 ||
		peopleItem->getContentSize().height <= 0) {
		problemLoading("'peoplebutton.png' and 'peoplebutton_select.png'");
	}
	else {
		peopleItem->setPosition(Vec2(kuangpeople->getPositionX() + origin.x, kuangpeople->getPositionY() - kuangpeople->getContentSize().height / 2 + 50 + origin.y));
		peopleItem->setScaleX(0.95f);
		peopleItem->setScaleY(1.2f);
	}
	auto menupeopleItem = Menu::create(peopleItem, NULL);
	menupeopleItem->setPosition(Vec2::ZERO);
	this->addChild(menupeopleItem, 3);


	//添加用户，若无，则分配
	if(Welcome::loginflag ==0)
	{ 
		std::string username = UserDefault::getInstance()->getStringForKey("username", "new");
		if(username.size()<10)
		{ 
			char buffer[64] = { 0 };
			GUID guid;
			if (CoCreateGuid(&guid)){
				fprintf(stderr, "create guid error\n");
			}
		else{
			_snprintf(buffer, sizeof(buffer),
				"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
				guid.Data1, guid.Data2, guid.Data3,
				guid.Data4[0], guid.Data4[1], guid.Data4[2],
				guid.Data4[3], guid.Data4[4], guid.Data4[5],
				guid.Data4[6], guid.Data4[7]);
			//printf("guid: %s\n", buffer);
			CCLOG("guid----------------->%s", buffer);
			UserDefault::getInstance()->setStringForKey("username", buffer);
			}
		}
	
	//登录	
		this->signin(UserDefault::getInstance()->getStringForKey("username", "zhuwai2"));
	}
	//scheduleUpdate();

	//id信息label
	label = Label::createWithTTF(" ", "fonts/Marker Felt.ttf", 14);
	if (label == nullptr){
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else	{
			label->setPosition(Vec2(origin.x+kuang1->getPositionX()+160,
			origin.y + kuang1->getPositionY()+15));
			this->addChild(label, 2);
	}
		label->setString("ID: "+UserDefault::getInstance()->getStringForKey("username", "gust"));
	
		//金币信息label	
		auto coinLabel = Label::createWithTTF(" ", "fonts/Marker Felt.ttf", 20);
		if (coinLabel == nullptr) {
			problemLoading("'fonts/Marker Felt.ttf'");
		}
		else {
			coinLabel->setPosition(Vec2(origin.x + coin->getPositionX() + 40,
				origin.y + coin->getPositionY() ));
			this->addChild(coinLabel, 2);
		}
		coinLabel->setString( UserDefault::getInstance()->getStringForKey("coins", "0"));

		//砖石信息label	
		auto diamLabel = Label::createWithTTF(" ", "fonts/Marker Felt.ttf", 20);
		if (diamLabel == nullptr) {
			problemLoading("'fonts/Marker Felt.ttf'");
		}
		else {
			diamLabel->setPosition(Vec2(origin.x + diam->getPositionX()+35,
				origin.y + diam->getPositionY()));
			this->addChild(diamLabel, 2);
		}
		diamLabel->setString(UserDefault::getInstance()->getStringForKey("diamonds", "0"));
		barLabel->setString("LV: "+UserDefault::getInstance()->getStringForKey("rank", "0"));
		//	+" Rank: " + UserDefault::getInstance()->getStringForKey("rank", "0") +" Coins: " + UserDefault::getInstance()->getStringForKey("coins", "0") + " Diamonds: " + UserDefault::getInstance()->getStringForKey("diamonds", "0")
		return true;
}

//进入游戏后运行
void GameGround::onEnter() {
	Layer::onEnter();

}
size_t writeFun(char*ptr, size_t size, size_t nmemb, std::string *userdata) {
	*((std::string*)(userdata)) += (char*)ptr;
	CCLOG("Data------------->%s", userdata->c_str());
	GameGround::dict = getMapFromResult(userdata->c_str());
	if (GameGround::dict["rank"] == "1") {
		cocos2d::MessageBox("sign in success", "signin");
		UserDefault::getInstance()->setStringForKey("rank", GameGround::dict["rank"]);
		UserDefault::getInstance()->setStringForKey("coins", GameGround::dict["coins"]);
		UserDefault::getInstance()->setStringForKey("diamonds", GameGround::dict["diamonds"]);
		UserDefault::getInstance()->setStringForKey("score", GameGround::dict["score"]);
	}
	else {
		cocos2d::MessageBox("sign in faile", "signin");
	}
	
	CCLOG("uid---------------->%s", UserDefault::getInstance()->getStringForKey("username").c_str());
	return nmemb;
}

//拆分字符串
std::vector<std::string> splitString(const std::string & str, char p) {
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

//gbk转化u8
std::string My_gbk_two_utf8(const std::string text)
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

//将字符串转化为key value对应的map类
std::map<std::string, std::string> getMapFromResult(std::string result) {
	std::string wresult = My_gbk_two_utf8(result.c_str());
	
	std::map<std::string, std::string> ret;
	std::vector<std::string>  vec = splitString(result, '\n');
	for (auto iter = vec.begin();iter != vec.end();++iter) {
		std::vector<std::string> vecKV = splitString(*iter, '=');
		if (vecKV.size() == 2) {
		//	ret[vecKV[0]] = atoi(vecKV[1].c_str());		
			ret[vecKV[0]] = vecKV[1].c_str();
		}
	}
	return ret;
}


//curl登录
void GameGround::signin(std::string username) {
	CURL * request = curl_easy_init();
	char buf[128];

	curl_easy_setopt(request, CURLOPT_URL, "http://localhost:8080/CocosSever/Finuser");
	snprintf(buf, sizeof(buf), "username=%s&password=lmsj",username.c_str());

	CCLOG("buf------------------------>%s", buf);

	curl_easy_setopt(request, CURLOPT_POSTFIELDS, buf);
	curl_easy_setopt(request, CURLOPT_WRITEFUNCTION, writeFun);
	//curl_easy_setopt(request, CURLOPT_WRITEDATA, &m_requestMap[request]);

	CURLcode res = curl_easy_perform(request);
	curl_easy_cleanup(request);
}

//关闭按钮回调函数
void  GameGround::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

//选择屠夫游戏按钮回调函数
void  GameGround::menuTufuCallback(Ref* pSender)
{
	GameGround::who = 1;
	auto gameScene = HelloWorld::createScene();
	auto ss = TransitionMoveInL::create(0.5, gameScene);
	//替换场景
	Director::getInstance()->replaceScene(ss);
}

//选择人类游戏按钮回调函数
void  GameGround::menuPeopleCallback(Ref* pSender)
{
	GameGround::who = 0;
	auto gameScene = HelloWorld::createScene();
	auto ss = TransitionMoveInL::create(0.5, gameScene);
	//替换场景
	Director::getInstance()->replaceScene(ss);
}

void GameGround::update(float dt) {

}
