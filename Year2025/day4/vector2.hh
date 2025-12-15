#ifndef VECTOR2_HH
#define VECTOR2_HH

class Vector2 {
public:
	Vector2(int x, int y);

	int x() const;
	int y() const;

private:
	int x_;
	int y_;
};

#endif // VECTOR2_HH
