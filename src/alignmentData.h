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
#ifndef __ALIGNMENTDATA_H__
#define __ALIGNMENTDATA_H__

#include "tools.h"


using namespace std;
using namespace Tools;

class alignmentData
{
    private:
      vector< vector < int > > targets;
      vector<float> distances;
      vector<float> probas;
    public:
      alignmentData();
      alignmentData(int n);
      void addAlignmentData(float distance, float proba);
      void addAlignmentData(vector < int > target, float distance, float proba);
      void setAlignmentData(float distance, float proba, int pos);
      vector< vector < int > > getTargets();
      vector<float> getDistances();
      vector<float> getProbas();
      vector < int > getTargetsAt(int pos);
      float getDistancesAt(int pos);
      float getProbasAt(int pos);
      

};


#endif
