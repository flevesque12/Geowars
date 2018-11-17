#pragma once
#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D() {
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2D::Vector2D(double x, double y) {
	this->x = x;
	this->x = x;
}

Vector2D::~Vector2D() {
}

//fais les opration sur les vecteur 2d et restourne un vecteur2D
Vector2D Vector2D::operator+(const Vector2D &v) const {
	return Vector2D(this->x + v.x, this->y + v.y);
}

Vector2D Vector2D::operator-(const Vector2D &v) const {
	return Vector2D(this->x - v.x, this->y - v.y);
}

Vector2D Vector2D::operator*(const Vector2D &v) const {
	return Vector2D(this->x * v.x, this->y * v.y);
}

Vector2D Vector2D::operator/(const Vector2D &v) const {
	return Vector2D(this->x / v.x, this->y / v.y);
}

//verifier si 2 vecteur on la meme valeur
bool Vector2D::operator==(const Vector2D &v) const {
	return ((this->x == v.x) && (this->y == v.y));
}

//verifier si les vecteur son plus proche ou plus loin que leur origine
bool Vector2D::operator>(const Vector2D &v) const {
	return (x*x + y*y) > (v.x*v.x + v.y*v.y);
}

bool Vector2D::operator<(const Vector2D &v) const {
	return (x*x + y*y) < (v.x*v.x + v.y*v.y);
}

bool Vector2D::operator>=(const Vector2D &v) const {
	return (x*x + y*y) > (v.x*v.x + v.y*v.y) || (x*x + y*y) == (v.x*v.x + v.y*v.y);
}

bool Vector2D::operator<=(const Vector2D &v) const {
	return (x*x + y*y) < (v.x*v.x + v.y*v.y) || (x*x + y*y) == (v.x*v.x + v.y*v.y);
}

//mettre les valeur x et y dans le negatif
Vector2D Vector2D::operator-() const {
	return Vector2D(-x, -y);
}

//opration scalaire muliplication par un scalaire ou division
Vector2D Vector2D::operator*(const double &scalar) const {
	return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(const double &scalar) const {
	return Vector2D(x / scalar, y / scalar);
}

//produit vectoriel et produit scalaire
double Vector2D::DotProduct(const Vector2D &a, const Vector2D &b) {
	return ((a.x * b.x) + (a.y * b.y));
}

double Vector2D::CrossProduct(const Vector2D &a, const Vector2D &b) {
	return ((a.x * b.y) - (a.y * b.x));
}

//longueur d'un vecteur
double Vector2D::Magnitude(const Vector2D &v) {
	return sqrt((v.x * v.x) + (v.y * v.y));
}

//normaliser un vecteur
Vector2D Vector2D::Normal(const Vector2D &v) {
	double magnitude = Magnitude(v);
	return Vector2D(v.x / magnitude, v.y / magnitude);
}

//retourne un vecteur perpendiculaire a gauche
Vector2D Vector2D::Perpendicular(const Vector2D &v) {
	return Vector2D(v.y, -v.x);
}

//retourne vrai si 2 segments se croisent
bool Vector2D::Intersect(const Vector2D &aa, const Vector2D &ab, const Vector2D &ba, const Vector2D &bb) {
	Vector2D p = aa;
	Vector2D r = ab - aa;
	Vector2D q = ba;
	Vector2D s = bb - ba;

	double t = CrossProduct((q - p), s) / CrossProduct(r, s);
	double u = CrossProduct((q - p), r) / CrossProduct(r, s);

	return (0.0 <= t && t <= 1.0) &&
		(0.0 <= u && u <= 1.0);
}

//retourne le point ou les 2 segment se croisent
Vector2D Vector2D::GetIntersect(const Vector2D &aa, const Vector2D &ab, const Vector2D &ba, const Vector2D &bb) {
	float pX = (float)((aa.x*ab.y - aa.y*ab.x)*(ba.x - bb.x) -
		(ba.x*bb.y - ba.y*bb.x)*(aa.x - ab.x));
	float pY = (float)((aa.x*ab.y - aa.y*ab.x)*(ba.y - bb.y) -
		(ba.x*bb.y - ba.y*bb.x)*(aa.y - ab.y));
	float denominator = (float)((aa.x - ab.x)*(ba.y - bb.y) -
		(aa.y - ab.y)*(ba.x - bb.x));

	return Vector2D(pX / denominator, pY / denominator);
}

double Vector2D::GetVectorX() {
	return this->x;
}

double Vector2D::GetVectorY() {
	return this->y;
}