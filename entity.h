//
//  entity.h
//  InstallingSFML
//
//  Created by Blank Blank on 2015-08-11.
//  Copyright (c) 2015 Blank Blank. All rights reserved.
//

#ifndef __InstallingSFML__entity__
#define __InstallingSFML__entity__

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cmath>
//#include "ResourcePath.hpp"
#include <cstdlib>
#include <functional>
#include <deque>
#include <list>
#include <vector>
using namespace std;
//#include "randomFunction.h"

class entity
{
public:
    sf::RectangleShape rect;
    sf::Sprite sprite;
    sf::Text text;
    
private:
protected:
};

#endif /* defined(__InstallingSFML__entity__) */
