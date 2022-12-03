#pragma once

#include <unordered_set>

struct Vector2d {
	int x, y;
};

class BoundingBox
{
public:
	BoundingBox(int x, int y, int width, int height);
	int x, y;

	void update(int x, int y);

	bool overlaps(BoundingBox& other);

	bool contains(int x, int y);

	bool isEntering(BoundingBox& other);

	Vector2d sweep(std::unordered_set<class Actor*>& actors, Vector2d& delta);	//class Actor -> forward declaration

	int width, height;
	int left, right, top, bottom;
	bool touchLeft, touchRight, touchTop, touchBottom;
};

