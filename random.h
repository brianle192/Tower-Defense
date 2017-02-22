//
//  random.h
//  InstallingSFML
//
//  Created by Blank Blank on 2015-08-11.
//  Copyright (c) 2015 Blank Blank. All rights reserved.
//

#ifndef __InstallingSFML__random__
#define __InstallingSFML__random__

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cmath>

#include <cstdlib>
#include <functional>

#include <deque>
#include <list>
#include <vector>

using namespace std;

int generateRandom(int max);
int generateRandom0(int max);
bool generateRandomBool();

#endif /* defined(__InstallingSFML__random__) */