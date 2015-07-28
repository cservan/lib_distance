/*********************************
 * tercpp: an open-source Translation Edit Rate (TER) scorer tool for Machine Translation.
 *
 * Copyright 2010-2013, Christophe Servan, LIUM, University of Le Mans, France
 * Copyright 2015, Christophe Servan, GETALP-LIG, University of Grenoble, France
 * Contact: christophe.servan@gmail.com
 *
 * The tercpp tool and library are free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by 
 * the Free Software Foundation, either version 3 of the licence, or
 * (at your option) any later version.
 *
 * This program and library are distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * **********************************/

#include "alignmentData.h"
#include <iostream>
#include <fstream>
#include <boost/thread/thread.hpp>

// #include <thread>
// #include <boost/lockfree/queue.hpp>

using namespace std;
using namespace Tools;

alignmentData::alignmentData()
{
    distances = vector< float >(0);
    probas = vector< float >(0);
}
alignmentData::alignmentData(int n)
{
    distances = vector< float >(n,0.0);
    probas = vector< float >(n,0.0);
}


void alignmentData::addAlignmentData(float distance, float proba)
{
    vector<int> target(1,(int)targets.size());
    targets.push_back(target);
    distances.push_back(distance);
    probas.push_back(proba);
}
void alignmentData::addAlignmentData(vector< int > target, float distance, float proba)
{
    targets.push_back(target);
    distances.push_back(distance);
    probas.push_back(proba);
}
vector< float > alignmentData::getDistances()
{
    return distances;
}
vector< float > alignmentData::getProbas()
{
    return probas;
}
void alignmentData::setAlignmentData(float distance, float proba, int pos)
{
    distances.at(pos) = distance;
    probas.at(pos) = proba;
}
float alignmentData::getDistancesAt(int pos)
{
    return distances.at(pos);
}
float alignmentData::getProbasAt(int pos)
{
    return probas.at(pos);
}
vector< vector< int > > alignmentData::getTargets()
{
    return targets;
}
vector< int > alignmentData::getTargetsAt(int pos)
{
    return targets.at(pos);
}



