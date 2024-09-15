/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

 https://axmol.dev/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include <ui/UIButton.h>
#include "MainScene.h"

using namespace ax;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf(
        "Depending on how you compiled you might have to add 'Content/' in front of filenames in "
        "MainScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
        AX_CALLBACK_1(MainScene::menuCloseCallback, this));

    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = safeOrigin.x + safeArea.size.width - closeItem->getContentSize().width / 2;
        float y = safeOrigin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    scheduleUpdate();

    _basePanel = LayerColor::create(Color4B::GRAY, visibleSize.width, visibleSize.height);
    _basePanel->setPositionNormalized(Vec2(0, 0));
    addChild(_basePanel, 1);

    auto* button = ui::Button::create();
    button->setPositionNormalized(Vec2(0.5f, 0.2f));
    button->setTitleText("RESET");
    button->setTitleFontSize(50.f);
    button->addClickEventListener([this](ax::Object*) {
        scheduleOnce([this](float){
            _basePanel->removeAllChildren();

            const auto renderer = Director::getInstance()->getRenderer();

            constexpr auto panelSize = Vec2(500, 500);
            auto* renderTexture = RenderTexture::create(static_cast<int>(panelSize.width), static_cast<int>(panelSize.height), true);
            renderTexture->beginWithClear(0, 0, 0, 0);

            auto* grid = CreateGrid(Vec2(400, 400));
            grid->setPosition(panelSize / 2);
            grid->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            grid->visit();
            renderTexture->end();
            renderer->render();

            auto gridSprite = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
            gridSprite->setPositionNormalized(Vec2(0.5f, 0.5f));
            gridSprite->setFlippedY(true);
            _basePanel->addChild(gridSprite);
        }, 0.f, "__1");
    });
    addChild(button, 100);

    return true;
}


void MainScene::onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        AXLOG("onTouchesBegan detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        AXLOG("onTouchesMoved detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        AXLOG("onTouchesEnded detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onMouseDown(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseDown detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void MainScene::onMouseUp(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseUp detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void MainScene::onMouseMove(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseMove detected, X:%f  Y:%f", e->getCursorX(), e->getCursorY());
}

void MainScene::onMouseScroll(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseScroll detected, X:%f  Y:%f", e->getScrollX(), e->getScrollY());
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
    AXLOG("onKeyPressed, keycode: %d", static_cast<int>(code));
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
    AXLOG("onKeyReleased, keycode: %d", static_cast<int>(code));
}

void MainScene::update(float delta)
{
    switch (_gameState)
    {
    case GameState::init:
    {
        _gameState = GameState::update;
        break;
    }

    case GameState::update:
    {
        /////////////////////////////
        // Add your codes below...like....
        //
        // UpdateJoyStick();
        // UpdatePlayer();
        // UpdatePhysics();
        // ...
        break;
    }

    case GameState::pause:
    {
        /////////////////////////////
        // Add your codes below...like....
        //
        // anyPauseStuff()

        break;
    }

    case GameState::menu1:
    {    /////////////////////////////
        // Add your codes below...like....
        //
        // UpdateMenu1();
        break;
    }

    case GameState::menu2:
    {    /////////////////////////////
        // Add your codes below...like....
        //
        // UpdateMenu2();
        break;
    }

    case GameState::end:
    {    /////////////////////////////
        // Add your codes below...like....
        //
        // CleanUpMyCrap();
        menuCloseCallback(this);
        break;
    }

    } //switch
}

void MainScene::menuCloseCallback(ax::Object* sender)
{
    // Close the axmol game scene and quit the application
    _director->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
     * _director->end() as given above,instead trigger a custom event created in RootViewController.mm
     * as below*/

     // EventCustom customEndEvent("game_scene_close_event");
     //_eventDispatcher->dispatchEvent(&customEndEvent);
}

ax::LayerColor* MainScene::CreateGrid(const Vec2& size)
{
    const auto columns = 8;
    const auto rows = 8;
    const auto rowHeight = size.height / float(rows);
    const auto columnWidth = size.width / float(columns);

    const auto layerColor = LayerColor::create(Color4B::WHITE, size.width, size.height);
    layerColor->setIgnoreAnchorPointForPosition(false);
    const auto drawNode = DrawNode::create();

    layerColor->addChild(drawNode);

    for (size_t row = 0; row < rows; row++)
    {
        const auto rowStart = size.height - row * rowHeight;
        for (size_t col = 0; col < columns; col++)
        {
            const auto colStart = col * columnWidth;
            drawNode->drawSolidRect(Vec2(colStart, rowStart), Vec2(colStart + columnWidth, rowStart - rowHeight), Color4F::WHITE);
            if (RandomHelper::random_int(0, 2) == 1)
            {
                drawNode->drawSolidCircle(Vec2(colStart + columnWidth / 2, rowStart - rowHeight / 2),columnWidth / 2, 0, 36, 0.8f, 0.8f, Color4F::GREEN, 1.0f, Color4F::BLACK);
            }
        }
    }

    // Draw the column edge lines
    for (size_t i = 0; i < columns + 1; i++)
    {
        drawNode->drawLine(Vec2(i * columnWidth, 0), Vec2(i * columnWidth, size.height), Color4F::BLACK);
    }

    // Draw the row edge lines
    for (size_t i = 0; i < rows + 1; i++)
    {
        drawNode->drawLine(Vec2(0, i * rowHeight), Vec2(size.width, i * rowHeight), Color4F::BLACK);
    }

    return layerColor;
}

