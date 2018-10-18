/** @file MaxRectsBinPack.cpp
	@author Jukka Jylänki

	@brief Implements different bin packer algorithms that use the MAXRECTS data structure.

	This work is released to Public Domain, do whatever you want with it.
*/
#include <algorithm>
#include <utility>
#include <iostream>
#include <limits>

#include <cassert>
#include <cstring>
#include <cmath>

#include "MaxRectsBinPack.h"

namespace rbp {

using namespace std;

MaxRectsBinPack::MaxRectsBinPack()
:binWidth(0),
binHeight(0), heuristic(Uncertain)
{
}

MaxRectsBinPack::MaxRectsBinPack(int width, int height, bool allowFlip) : heuristic(Uncertain)
{
	Init(width, height, allowFlip);
}

void MaxRectsBinPack::Init(int width, int height, bool allowFlip)
{
	binAllowFlip = allowFlip;
	binWidth = width;
	binHeight = height;

	Rect n(width,height,0,0);

	usedRectangles.clear();

	freeRectangles.clear();
	freeRectangles.push_back(n);
}

Rect MaxRectsBinPack::Insert(int width, int height, FreeRectChoiceHeuristic method)
{
	Rect newNode;
	// Unused in this function. We don't need to know the score after finding the position.
	int score1 = std::numeric_limits<int>::max();
	int score2 = std::numeric_limits<int>::max();
	switch(method)
	{
	    case Uncertain:  //force to use RectBestShortSideFit
		case RectBestShortSideFit: newNode = FindPositionForNewNodeBestShortSideFit(width, height, score1, score2); break;
		case RectBottomLeftRule: newNode = FindPositionForNewNodeBottomLeft(width, height, score1, score2); break;
		case RectContactPointRule: newNode = FindPositionForNewNodeContactPoint(width, height, score1); break;
		case RectBestLongSideFit: newNode = FindPositionForNewNodeBestLongSideFit(width, height, score2, score1); break;
		case RectBestAreaFit: newNode = FindPositionForNewNodeBestAreaFit(width, height, score1, score2); break;
	}
		
	if (newNode.height() == 0)
		return newNode;

	size_t numRectanglesToProcess = freeRectangles.size();
	for(size_t i = 0; i < numRectanglesToProcess; ++i)
	{
		if (SplitFreeNode(freeRectangles[i], newNode))
		{
			freeRectangles.erase(freeRectangles.begin() + i);
			--i;
			--numRectanglesToProcess;
		}
	}

	PruneFreeList();

	usedRectangles.push_back(newNode);
	return newNode;
}

void MaxRectsBinPack::Insert(std::vector<Rect> &rects, std::vector<Rect> &dst, FreeRectChoiceHeuristic method)
{
	heuristic = method;
	dst.clear();

	while(!rects.empty())
	{
		int bestScore1 = std::numeric_limits<int>::max();
		int bestScore2 = std::numeric_limits<int>::max();
		int bestRectIndex = -1;
		Rect bestNode;

		for(size_t i = 0; i < rects.size(); ++i)
		{
			int score1;
			int score2;
			Rect newNode = ScoreRect(rects[i].width(), rects[i].height(), method, score1, score2);

			if (score1 < bestScore1 || (score1 == bestScore1 && score2 < bestScore2))
			{
				bestScore1 = score1;
				bestScore2 = score2;
				bestNode = newNode;
				bestRectIndex = static_cast<int>(i);
			}
		}

		if (bestRectIndex == -1)
			return;

		PlaceRect(bestNode);
		dst.push_back(bestNode);
		rects.erase(rects.begin() + bestRectIndex);
	}
}

void MaxRectsBinPack::PlaceRect(const Rect &node)
{
	size_t numRectanglesToProcess = freeRectangles.size();
	for(size_t i = 0; i < numRectanglesToProcess; ++i)
	{
		if (SplitFreeNode(freeRectangles[i], node))
		{
			freeRectangles.erase(freeRectangles.begin() + i);
			--i;
			--numRectanglesToProcess;
		}
	}

	PruneFreeList();

	usedRectangles.push_back(node);
}

Rect MaxRectsBinPack::ScoreRect(int width, int height, FreeRectChoiceHeuristic method, int &score1, int &score2) const
{
	Rect newNode;
	score1 = std::numeric_limits<int>::max();
	score2 = std::numeric_limits<int>::max();
	switch(method)
	{
        case Uncertain:  //force to use RectBestShortSideFit
        case RectBestShortSideFit:
            newNode = FindPositionForNewNodeBestShortSideFit(width, height, score1, score2);
            break;
        case RectBottomLeftRule:
            newNode = FindPositionForNewNodeBottomLeft(width, height, score1, score2);
            break;
        case RectContactPointRule:
            newNode = FindPositionForNewNodeContactPoint(width, height, score1);
            score1 = -score1; // Reverse since we are minimizing, but for contact point score bigger is better.
            break;
        case RectBestLongSideFit:
            newNode = FindPositionForNewNodeBestLongSideFit(width, height, score2, score1);
            break;
        case RectBestAreaFit:
            newNode = FindPositionForNewNodeBestAreaFit(width, height, score1, score2);
            break;
	}

	// Cannot fit the current rectangle.
	if (newNode.height() == 0)
	{
		score1 = std::numeric_limits<int>::max();
		score2 = std::numeric_limits<int>::max();
	}

	return newNode;
}

/// Computes the ratio of used surface area.
float MaxRectsBinPack::Occupancy() const
{
	unsigned long usedSurfaceArea = 0;
	for(size_t i = 0; i < usedRectangles.size(); ++i)
		usedSurfaceArea += usedRectangles[i].area();

	return (float)usedSurfaceArea / (binWidth * binHeight);
}

std::vector<Rect> MaxRectsBinPack::GetUsedRectangles() {
	return usedRectangles;
}


Rect MaxRectsBinPack::FindPositionForNewNodeBottomLeft(int width, int height, int &bestY, int &bestX) const
{
	Rect bestNode;

	bestY = std::numeric_limits<int>::max();
	bestX = std::numeric_limits<int>::max();

	for(size_t i = 0; i < freeRectangles.size(); ++i)
	{
		// Try to place the rectangle in upright (non-flipped) orientation.
		if (freeRectangles[i].width() >= width && freeRectangles[i].height() >= height)
		{
			int topSideY = freeRectangles[i].y() + height;
			if (topSideY < bestY || (topSideY == bestY && freeRectangles[i].x() < bestX))
			{
			    bestNode.reset(width, height, freeRectangles[i].x(), freeRectangles[i].y());
				bestY = topSideY;
				bestX = freeRectangles[i].x();
			}
		}
		if (binAllowFlip && freeRectangles[i].width() >= height && freeRectangles[i].height() >= width)
		{
			int topSideY = freeRectangles[i].y() + width;
			if (topSideY < bestY || (topSideY == bestY && freeRectangles[i].x() < bestX))
			{
                bestNode.reset(width, height, freeRectangles[i].x(), freeRectangles[i].y());
				bestY = topSideY;
				bestX = freeRectangles[i].x();
			}
		}
	}
	return bestNode;
}

Rect MaxRectsBinPack::FindPositionForNewNodeBestShortSideFit(int width, int height, 
	int &bestShortSideFit, int &bestLongSideFit) const
{
	Rect bestNode;

	bestShortSideFit = std::numeric_limits<int>::max();
	bestLongSideFit = std::numeric_limits<int>::max();

	for(size_t i = 0; i < freeRectangles.size(); ++i)
	{
		// Try to place the rectangle in upright (non-flipped) orientation.
		if (freeRectangles[i].width() >= width && freeRectangles[i].height() >= height)
		{
			int leftoverHoriz = abs(freeRectangles[i].width() - width);
			int leftoverVert = abs(freeRectangles[i].height() - height);
			int shortSideFit = min(leftoverHoriz, leftoverVert);
			int longSideFit = max(leftoverHoriz, leftoverVert);

			if (shortSideFit < bestShortSideFit || (shortSideFit == bestShortSideFit && longSideFit < bestLongSideFit))
			{
                bestNode.reset(width, height, freeRectangles[i].x(), freeRectangles[i].y());
				bestShortSideFit = shortSideFit;
				bestLongSideFit = longSideFit;
			}
		}

		if (binAllowFlip && freeRectangles[i].width() >= height && freeRectangles[i].height() >= width)
		{
			int flippedLeftoverHoriz = abs(freeRectangles[i].width() - height);
			int flippedLeftoverVert = abs(freeRectangles[i].height() - width);
			int flippedShortSideFit = min(flippedLeftoverHoriz, flippedLeftoverVert);
			int flippedLongSideFit = max(flippedLeftoverHoriz, flippedLeftoverVert);

			if (flippedShortSideFit < bestShortSideFit || (flippedShortSideFit == bestShortSideFit && flippedLongSideFit < bestLongSideFit))
			{
                bestNode.reset(height, width, freeRectangles[i].x(), freeRectangles[i].y());
				bestShortSideFit = flippedShortSideFit;
				bestLongSideFit = flippedLongSideFit;
			}
		}
	}
	return bestNode;
}

Rect MaxRectsBinPack::FindPositionForNewNodeBestLongSideFit(int width, int height, 
	int &bestShortSideFit, int &bestLongSideFit) const
{
	Rect bestNode;

	bestShortSideFit = std::numeric_limits<int>::max();
	bestLongSideFit = std::numeric_limits<int>::max();

	for(size_t i = 0; i < freeRectangles.size(); ++i)
	{
		// Try to place the rectangle in upright (non-flipped) orientation.
		if (freeRectangles[i].width() >= width && freeRectangles[i].height() >= height)
		{
			int leftoverHoriz = abs(freeRectangles[i].width() - width);
			int leftoverVert = abs(freeRectangles[i].height() - height);
			int shortSideFit = min(leftoverHoriz, leftoverVert);
			int longSideFit = max(leftoverHoriz, leftoverVert);

			if (longSideFit < bestLongSideFit || (longSideFit == bestLongSideFit && shortSideFit < bestShortSideFit))
			{
                bestNode.reset(width, height, freeRectangles[i].x(), freeRectangles[i].y());
				bestShortSideFit = shortSideFit;
				bestLongSideFit = longSideFit;
			}
		}

		if (binAllowFlip && freeRectangles[i].width() >= height && freeRectangles[i].height() >= width)
		{
			int leftoverHoriz = abs(freeRectangles[i].width() - height);
			int leftoverVert = abs(freeRectangles[i].height() - width);
			int shortSideFit = min(leftoverHoriz, leftoverVert);
			int longSideFit = max(leftoverHoriz, leftoverVert);

			if (longSideFit < bestLongSideFit || (longSideFit == bestLongSideFit && shortSideFit < bestShortSideFit))
			{
                bestNode.reset(width, height, freeRectangles[i].x(), freeRectangles[i].y());
				bestShortSideFit = shortSideFit;
				bestLongSideFit = longSideFit;
			}
		}
	}
	return bestNode;
}

Rect MaxRectsBinPack::FindPositionForNewNodeBestAreaFit(int width, int height, 
	int &bestAreaFit, int &bestShortSideFit) const
{
	Rect bestNode;

	bestAreaFit = std::numeric_limits<int>::max();
	bestShortSideFit = std::numeric_limits<int>::max();

	for(size_t i = 0; i < freeRectangles.size(); ++i)
	{
		int areaFit = freeRectangles[i].width() * freeRectangles[i].height() - width * height;

		// Try to place the rectangle in upright (non-flipped) orientation.
		if (freeRectangles[i].width() >= width && freeRectangles[i].height() >= height)
		{
			int leftoverHoriz = abs(freeRectangles[i].width() - width);
			int leftoverVert = abs(freeRectangles[i].height() - height);
			int shortSideFit = min(leftoverHoriz, leftoverVert);

			if (areaFit < bestAreaFit || (areaFit == bestAreaFit && shortSideFit < bestShortSideFit))
			{
                bestNode.reset(width, height, freeRectangles[i].x(), freeRectangles[i].y());
				bestShortSideFit = shortSideFit;
				bestAreaFit = areaFit;
			}
		}

		if (binAllowFlip && freeRectangles[i].width() >= height && freeRectangles[i].height() >= width)
		{
			int leftoverHoriz = abs(freeRectangles[i].width() - height);
			int leftoverVert = abs(freeRectangles[i].height() - width);
			int shortSideFit = min(leftoverHoriz, leftoverVert);

			if (areaFit < bestAreaFit || (areaFit == bestAreaFit && shortSideFit < bestShortSideFit))
			{
                bestNode.reset(width, height, freeRectangles[i].x(), freeRectangles[i].y());
				bestShortSideFit = shortSideFit;
				bestAreaFit = areaFit;
			}
		}
	}
	return bestNode;
}


/// Returns 0 if the two intervals i1 and i2 are disjoint, or the length of their overlap otherwise.
int CommonIntervalLength(int i1start, int i1end, int i2start, int i2end)
{
	if (i1end < i2start || i2end < i1start)
		return 0;
	return min(i1end, i2end) - max(i1start, i2start);
}


int MaxRectsBinPack::ContactPointScoreNode(int x, int y, int width, int height) const
{
	int score = 0;

	if (x == 0 || x + width == binWidth)
		score += height;
	if (y == 0 || y + height == binHeight)
		score += width;

	for(size_t i = 0; i < usedRectangles.size(); ++i)
	{
		if (usedRectangles[i].x() == x + width || usedRectangles[i].x() + usedRectangles[i].width() == x)
			score += CommonIntervalLength(usedRectangles[i].y(), usedRectangles[i].y() + usedRectangles[i].height(), y, y + height);
		if (usedRectangles[i].y() == y + height || usedRectangles[i].y() + usedRectangles[i].height() == y)
			score += CommonIntervalLength(usedRectangles[i].x(), usedRectangles[i].x() + usedRectangles[i].width(), x, x + width);
	}
	return score;
}


Rect MaxRectsBinPack::FindPositionForNewNodeContactPoint(int width, int height, int &bestContactScore) const
{
	Rect bestNode;

	bestContactScore = -1;

	for(size_t i = 0; i < freeRectangles.size(); ++i)
	{
		// Try to place the rectangle in upright (non-flipped) orientation.
		if (freeRectangles[i].width() >= width && freeRectangles[i].height() >= height)
		{
			int score = ContactPointScoreNode(freeRectangles[i].x(), freeRectangles[i].y(), width, height);
			if (score > bestContactScore)
			{
                bestNode.reset(width, height, freeRectangles[i].x(), freeRectangles[i].y());
				bestContactScore = score;
			}
		}
		if (freeRectangles[i].width() >= height && freeRectangles[i].height() >= width)
		{
			int score = ContactPointScoreNode(freeRectangles[i].x(), freeRectangles[i].y(), height, width);
			if (score > bestContactScore)
			{
                bestNode.reset(width, height, freeRectangles[i].x(), freeRectangles[i].y());
				bestContactScore = score;
			}
		}
	}
	return bestNode;
}

bool MaxRectsBinPack::SplitFreeNode(Rect freeNode, const Rect &usedNode)
{
	// Test with SAT if the rectangles even intersect.
	if(!usedNode.overlaps(freeNode))
	    return false;

	if (usedNode.x() < freeNode.x() + freeNode.width() && usedNode.x() + usedNode.width() > freeNode.x())
	{
		// New node at the top side of the used node.
		if (usedNode.y() > freeNode.y() && usedNode.y() < freeNode.y() + freeNode.height())
		{
		    Rect newNode = freeNode;
		    newNode.set_height(usedNode.y() - newNode.y());
			freeRectangles.push_back(newNode);
		}

		// New node at the bottom side of the used node.
		if (usedNode.y() + usedNode.height() < freeNode.y() + freeNode.height())
		{
            Rect newNode = freeNode;
            newNode.set_height(freeNode.y_bottom() - usedNode.y_bottom());
            newNode.set_y(usedNode.y_bottom());
			freeRectangles.push_back(newNode);
		}
	}

	if (usedNode.y() < freeNode.y() + freeNode.height() && usedNode.y() + usedNode.height() > freeNode.y())
	{
		// New node at the left side of the used node.
		if (usedNode.x() > freeNode.x() && usedNode.x() < freeNode.x() + freeNode.width())
		{
            Rect newNode = freeNode;
            newNode.set_width(usedNode.x() - newNode.x());
            newNode.set_y(usedNode.y_bottom());
			freeRectangles.push_back(newNode);
		}

		// New node at the right side of the used node.
		if (usedNode.x() + usedNode.width() < freeNode.x() + freeNode.width())
		{
            Rect newNode = freeNode;
            newNode.set_width(freeNode.x_right() - usedNode.x_right());
            newNode.set_x(usedNode.x_right());
			freeRectangles.push_back(newNode);
		}
	}

	return true;
}

void MaxRectsBinPack::PruneFreeList()
{
	/* 
	///  Would be nice to do something like this, to avoid a Theta(n^2) loop through each pair.
	///  But unfortunately it doesn't quite cut it, since we also want to detect containment. 
	///  Perhaps there's another way to do this faster than Theta(n^2).

	if (freeRectangles.size() > 0)
		clb::sort::QuickSort(&freeRectangles[0], freeRectangles.size(), NodeSortCmp);

	for(size_t i = 0; i < freeRectangles.size()-1; ++i)
		if (freeRectangles[i].x == freeRectangles[i+1].x &&
		    freeRectangles[i].y == freeRectangles[i+1].y &&
		    freeRectangles[i].width == freeRectangles[i+1].width &&
		    freeRectangles[i].height == freeRectangles[i+1].height)
		{
			freeRectangles.erase(freeRectangles.begin() + i);
			--i;
		}
	*/

	/// Go through each pair and remove any rectangle that is redundant.
	for(size_t i = 0; i < freeRectangles.size(); ++i)
		for(size_t j = i+1; j < freeRectangles.size(); ++j)
		{
			if (is_contained(freeRectangles[i], freeRectangles[j]))
			{
				freeRectangles.erase(freeRectangles.begin()+i);
				--i;
				break;
			}
			if (is_contained(freeRectangles[j], freeRectangles[i]))
			{
				freeRectangles.erase(freeRectangles.begin()+j);
				--j;
			}
		}
}

MaxRectsBinPack::FreeRectChoiceHeuristic MaxRectsBinPack::UsedHeuristic() {
	return RectBestAreaFit;
}

}
