#include "images/crScene.h"

CranScene::CranScene()
{
    _screenArea = new Rectangle();
    _actualFrame = 0;
    //
    //addToResourceManager(CRAN_SCENE);
}

CranScene::CranScene(Rectangle* p_rectangle)
{
    _screenArea = new Rectangle(p_rectangle->_x1, p_rectangle->_y1, p_rectangle->_x2, p_rectangle->_y2);
    _actualFrame = 0;
    //
    //addToResourceManager(CRAN_SCENE);
}

CranScene::~CranScene()
{
    delete _screenArea;
    //removeFromResourceManager(CRAN_SCENE);

}
