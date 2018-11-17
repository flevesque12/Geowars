#pragma once
#include <cfloat>
#include <climits>

class Vector2D
{
public:
	Vector2D();
	Vector2D(double x, double y);
	~Vector2D();

	//fais les opration sur les vecteur 2d et restourne un vecteur2D
	Vector2D operator+(const Vector2D&) const;
	Vector2D operator-(const Vector2D&) const;
	Vector2D operator*(const Vector2D&) const;
	Vector2D operator/(const Vector2D&) const;

	//verifier si 2 vecteur on la meme valeur
	bool operator==(const Vector2D&) const;

	//verifier si les vecteur son plus proche ou plus loin que leur origine
	bool operator>(const Vector2D&) const;
	bool operator<(const Vector2D&) const;
	bool operator>=(const Vector2D&) const;
	bool operator<=(const Vector2D&) const;

	//mettre les valeur x et y dans le negatif
	Vector2D operator-() const;

	//opration scalaire muliplication par un scalaire ou division
	Vector2D operator*(const double&) const;
	Vector2D operator/(const double&) const;

	//produit vectoriel et produit scalaire
	static double DotProduct(const Vector2D&, const Vector2D&);
	static double CrossProduct(const Vector2D&, const Vector2D&);

	//longueur d'un vecteur
	static double Magnitude(const Vector2D&);

	//normaliser un vecteur
	static Vector2D Normal(const Vector2D&);

	//retourne un vecteur perpendiculaire a gauche
	static Vector2D Perpendicular(const Vector2D&);

	//retourne vrai si 2 segments se croisent
	static bool Intersect(const Vector2D&, const Vector2D&, const Vector2D&, const Vector2D&);

	//retourne le point ou les 2 segment se croisent
	static Vector2D GetIntersect(const Vector2D&, const Vector2D&, const Vector2D&, const Vector2D&);

	double GetVectorX();
	double GetVectorY();

private:
	double x;
	double y;
};
